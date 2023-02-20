#define _CRT_SECURE_NO_WARNINGS		//for date functionality
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class Inventory {
	int pID, id, qty, invQty, price, restockPrice;
	char choice;
	string invMaster[16][8];
	string outOfStockMaster[16][8];

	public:
		void menu();

	private:
		void loadInventory();
		void loadOutofStock();
		void showSales();
		void showPurchases();
		void updatePurchases();
		void adminMenu();
		void customerMenu();
		string getTime();

		void showInventory();

		void buyItems();
		bool retry();
		void updateSales();
		void updateInventory();

		void checkOutofStock();
		void showOutofStock();
		void restockItems();
};

int main()
{
	Inventory WSInventory;

	WSInventory.menu();

	return 0;
}

void Inventory::menu() {
	system("CLS");
	loadInventory();
	loadOutofStock();
	checkOutofStock();
	
	cout << "Welcome to the ABC Trading Wholesale Inventory Management System." << endl;
	cout << "A: Admin Menu" << endl;
	cout << "B: Customer Menu" << endl;
	cout << "X: Exit" << endl << endl;
	cout << "Enter choice: ";
	cin >> choice;
	choice = toupper(choice);

	switch (choice) {
		case 'A':
			adminMenu();
			break;

		case 'B':
			customerMenu();
			break;

		case 'X':
			exit(0);
			break;

		default:
			cout << "Invalid input!" << endl;
			system("pause");
			menu();
			break;
	}
}

void Inventory::adminMenu() {
	system("CLS");

	cout << "ADMIN MENU" << endl;
	cout << "A: Show Inventory" << endl;
	cout << "B: Show Sales" << endl;
	cout << "C: Show Purchases" << endl;
	cout << "D: Show Out of Stock Items" << endl;
	cout << "X: Go back" << endl << endl;
	cout << "Enter choice: ";
	cin >> choice;
	choice = toupper(choice);

	switch (choice) {
	case 'A':
		showInventory();
		cout << "\nPress any key to go back to the admin menu." << endl;
		system("pause");
		adminMenu();
		break;

	case 'B':
		showSales();
		break;

	case 'C':
		showPurchases();
		break;

	case 'D':
		showOutofStock();
		break;

	case 'X':
		menu();
		break;

	default:
		cout << "Invalid input!" << endl;
		system("pause");
		menu();
		break;
	}
}

void Inventory::customerMenu() {
	system("CLS");

	cout << "CUSTOMER MENU" << endl;
	cout << "A: Check Items" << endl;
	cout << "B: Buy Items" << endl;
	cout << "X: Go Back" << endl << endl;
	cout << "Enter choice: ";
	cin >> choice;
	choice = toupper(choice);

	switch (choice) {
	case 'A':
		showInventory();
		cout << "\nPress any key to go back to the customer menu." << endl;
		system("pause");
		customerMenu();
		break;

	case 'B':
		buyItems();
		break;

	case 'X':
		menu();
		break;

	default:
		cout << "Invalid input!" << endl;
		system("pause");
		menu();
		break;
	}
}

void Inventory::showInventory() {
	system("CLS");
	for (int i = 0; i < 16; i++) {		//loops through the entire array and prints it
		for (int j = 0; j < 8; j++) {
			if (i == 0 && j == 2)		//Design stuff
				cout << "\t";	
										
			if (i > 0 && j < 3)
				cout << "\t";

			if (i > 0 && j > 3)
				cout << "\t";

			cout << invMaster[i][j] << "\t";
		}
	}
}

void Inventory::buyItems() {
	system("CLS");
	string line;

	showInventory();

	cout << "\n\nBUY ITEMS" << endl << endl;

	cout << "Choose product ID: " << endl;
	while (true)
	{
		cin >> pID;
		if (!cin || pID < 1 || pID > 15) {
			cout << "Invalid input! Input must be between 1 - 15. Try again: " << endl;		//validation of input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else break;
	}

	cout << "Choose quantity: " << endl;
	while (true)
	{
		cin >> qty;
		if (!cin || qty < 1 || qty > stoi(invMaster[pID][4])) {
			cout << "Invalid input! Input quantity must not be below 1 or exceed the available quantity of the item. Try again: " << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else break;
	}

	invQty = stoi(invMaster[pID][4]);				//take the inventory quantity (column 4 is qty)
	invMaster[pID][4] = to_string(invQty - qty);	//compute the quantity after purchase

	price = stoi(invMaster[pID][3]) * qty;		//compute for price (column 3 is price)

	showInventory();
	cout << "\nPurchased: " << qty << " " << invMaster[pID][7] << " of " << invMaster[pID][1] << " for " << price << " pesos." << endl;
	//Format of feedback examples -> Purchased: 500 pack(s) of strawberries for 5000 pesos.
	updateInventory();
	updateSales();
	checkOutofStock();

	cout << "Would you like to buy more items? [Y/N]: ";
	cin >> choice;
	choice = toupper(choice);
	
	if (retry() == true)
		buyItems();

	else
		menu();
}

void Inventory::updateInventory() {
	ofstream inv;
	inv.open("invMasterFile.txt", ios::out);

	if (inv.is_open()) {						//puts all of the contents of the array into the inventory master file
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 8; j++) {
				inv << invMaster[i][j] << ",";
			}
		}
	}
	inv.close();
}

void Inventory::loadInventory() {
	ifstream inv;
	string line;
	inv.open("invMasterFile.txt", ios::in);

	if (inv.is_open()) {						//intializes the inventory array by taking the data from the inventory master file
		int i = 0, j = 0;
		while (getline(inv, line, ',')) {
			if (j == 8) {		//if loop reaches the end of the row, go to the next row
				i++;
				j = 0;
			}

			invMaster[i][j] = line;
			j++;
		}
	}
	inv.close();
}

void Inventory::updateSales() {
	ofstream sales;
	string line;
	sales.open("salesFile.txt", ios::app);		//appends the data of a new sale using information from the buyItems() method

	if (sales.is_open()) {
		//Format: Item, Qty, Sales, Date
		sales << endl;
		sales << invMaster[pID][1] << "," << invMaster[pID][4] << " " << invMaster[pID][7] << "," << price << " pesos," << getTime() << ",";
	}
	sales.close();
}

void Inventory::showSales() {
	system("CLS");

	ifstream sales;
	string line;
	sales.open("salesFile.txt", ios::in);

	if (sales.is_open()) {
		int i = 0;
		while (getline(sales, line, ',')) {		
			cout << line << "\t";

			if (i < 4)
				cout << "\t";

			i++;
		}
	}
	sales.close();

	cout << "\n\n\nPress any key to go back to the menu." << endl;
	system("pause");
	adminMenu();
}

bool Inventory::retry() {
	switch (choice) {
	case 'Y':
		return true;
		break;

	case 'N':
		return false;
		break;

	default:
		cout << "Invalid input!" << endl;
		system("pause");
		retry();
		break;
	}
}

string Inventory::getTime() {
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
	string str(buffer);

	return str;
}

void Inventory::loadOutofStock() {
	ifstream stock;
	string line;
	stock.open("outOfStockFile.txt", ios::in);

	if (stock.is_open()) {
		int i = 0, j = 0;
		while (getline(stock, line, ',')) {
			if (j == 8) {
				i++;
				j = 0;
			}

			outOfStockMaster[i][j] = line;
			j++;
		}
	}
	stock.close();
}

void Inventory::checkOutofStock() {
	//check if inventory has out of stock items below ROP and not already in the out of stock file
	//take those items to the out of stock master array and update the file
	int j = 1;
	for (int i = 1; i < 16; i++) {	//loop through the invMaster array to check for out of stock items
		int sQty, rop;
		bool stop = false;
		sQty = stoi(invMaster[i][4]);
		rop = stoi(invMaster[i][5]);

		if (sQty <= rop) {	//if qty is lower or equal than the reorder point, put the item into the out of stock list
			for (int k = 0; k < 8; k++) {
				outOfStockMaster[j][k] = invMaster[i][k];
			}
			j++;
		}
	}

	for (j;  j < 16; j++) {					//the rest of the array gets deleted if none is found to delete potential dupe or outdated items
		for (int k = 0; k < 8; k++) {
			outOfStockMaster[j][k] = " ";
		}
	}

	ofstream stock;
	stock.open("outOfStockFile.txt", ios::out);

	if (stock.is_open()) {
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 8; j++) {
				stock << outOfStockMaster[i][j] << ",";		//updates the out of stock file
			}
		}
	}
	stock.close();
}

void Inventory::showOutofStock() {
	system("CLS");
	for (int i = 0; i < 16; i++) {		//prints the out of stock list
		for (int j = 0; j < 8; j++) {
			if (i == 0 && j == 2)
				cout << "\t";

			if (i > 0 && j < 3)
				cout << "\t";

			if (i > 0 && j > 3)
				cout << "\t";

			cout << outOfStockMaster[i][j] << "\t";
		}
	}

	cout << "\n\nA: Restock Out of Stock Item" << endl;
	cout << "X: Go back to menu" << endl;
	cout << "Enter choice: ";
	cin >> choice;
	choice = toupper(choice);

	switch (choice) {
		case 'A':
			restockItems();
			break;

		case 'X':
			adminMenu();
			break;

		default:
			cout << "Invalid input!" << endl;
			system("pause");
			menu();
			break;
	}
}

void Inventory::restockItems() {
	int restockQty, newQty;
	cout << "\nChoose ID of out of stock item: ";
	while (true)
	{
		cin >> id;
		if (!cin || id < 1 || id > 15) {
			cout << "Invalid input! Input must be between 1 - 15. Try again: " << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else break;
	}


	cout << "How much would you like to order?: ";
	while (true)
	{
		cin >> restockQty;
		if (!cin || restockQty < stoi(invMaster[id][5])) {
			cout << "Invalid input! Reorder can't be below ROP! Try again: " << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else break;
	}

	newQty = restockQty + stoi(invMaster[id][4]);		//computes the new quantity after reorder
	invMaster[id][4] = to_string(newQty);

	restockPrice = stoi(invMaster[id][3]) * restockQty;	//computes the price of reorder

	updateInventory();
	updatePurchases();
	checkOutofStock();
	showOutofStock();
	cout << "Item ID " << id << " restocked for " << restockQty << " units at the price of " << restockPrice << " pesos!" << endl;
	cout << "Would you like to restock more items? [Y/N]: ";
	cin >> choice;
	choice = toupper(choice);
	if (retry() == true)
		restockItems();

	else
		menu();
}

void Inventory::showPurchases() {
	system("CLS");

	ifstream purchases;
	string line;
	purchases.open("purchasesFile.txt", ios::in);

	if (purchases.is_open()) {
		int i = 0;
		while (getline(purchases, line, ',')) {
			cout << line << "\t";

			if (i < 4)
				cout << "\t";

			i++;
		}
	}
	purchases.close();

	cout << "\n\n\nPress any key to go back to the menu." << endl;
	system("pause");
	adminMenu();
}

void Inventory::updatePurchases() {
	ofstream purchases;
	string line;
	purchases.open("purchasesFile.txt", ios::app);

	if (purchases.is_open()) {
		//Format: Item, Qty, Expenses, Date,
		purchases << endl;
		purchases << invMaster[id][1] << "," << invMaster[id][4] << " " << invMaster[id][7] << "," << restockPrice << " pesos," << getTime() << ",";
	}
	purchases.close();
}