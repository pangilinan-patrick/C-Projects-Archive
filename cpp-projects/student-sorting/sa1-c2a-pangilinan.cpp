#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int floatcomp(const void *elem1, const void *elem2) {
  if (*(const float *)elem1 > *(const float *)elem2)
    return -1;
  return *(const float *)elem1 < *(const float *)elem2;
}

// Output functions to text files
void saveUnsortedData(string dataSet[18][3]) {
  ofstream unsortedData;
  unsortedData.open("unsortedStudentData.txt", ios::out);

  unsortedData << "FIRST NAME\tLAST NAME\tGRADES\n";
  for (int i = 0; i < 18; i++) {
    unsortedData << dataSet[i][0] << "\t\t";
    unsortedData << dataSet[i][1] << "\t\t";
    unsortedData << dataSet[i][2] << endl;
  }

  unsortedData.close();
}

void saveLastNames(string dataSet[18][3]) {
  ofstream sortedLastNames;
  sortedLastNames.open("sortedLastName.txt", ios::out);

  sortedLastNames << "FIRST NAME\tLAST NAME\tGRADES\n";
  for (int i = 0; i < 18; i++) {
    sortedLastNames << dataSet[i][0] << "\t\t";
    sortedLastNames << dataSet[i][1] << "\t\t";
    sortedLastNames << dataSet[i][2] << endl;
  }

  sortedLastNames.close();
}

void saveFirstNames(string dataSet[18][3]) {
  ofstream sortedFirstNames;
  sortedFirstNames.open("sortedFirstName.txt", ios::out);

  sortedFirstNames << "FIRST NAME\tLAST NAME\tGRADES\n";
  for (int i = 0; i < 18; i++) {
    sortedFirstNames << dataSet[i][0] << "\t\t";
    sortedFirstNames << dataSet[i][1] << "\t\t";
    sortedFirstNames << dataSet[i][2] << endl;
  }

  sortedFirstNames.close();
}

void saveGrades(string dataSet[18][3], float gradeArray[18]) {
  ofstream sortedGrades;
  sortedGrades.open("sortedGrade.txt", ios::out);

  sortedGrades << "FIRST NAME\tLAST NAME\tGRADES\n";

  for (int i = 0; i < 18; i++) {
    for (int j = 0; j < 18; j++) {
      if (stof(dataSet[j][2]) == gradeArray[i]) {
        sortedGrades << dataSet[j][0] << "\t\t";
        sortedGrades << dataSet[j][1] << "\t\t";
        sortedGrades << dataSet[j][2] << endl;
      }
    }
  }

  sortedGrades.close();
}

void saveDLGrades(string dataSet[18][3], float gradeArray[18]) {
  ofstream sortedGrades;
  sortedGrades.open("deanslist.txt", ios::out);

  sortedGrades << "FIRST NAME\tLAST NAME\tGRADES\n";
  for (int i = 0; i < 18; i++) {
    for (int j = 0; j < 18; j++) {
      if (stof(dataSet[j][2]) == gradeArray[i] && gradeArray[i] >= 90.15) {
        sortedGrades << dataSet[j][0] << "\t\t";
        sortedGrades << dataSet[j][1] << "\t\t";
        sortedGrades << stof(dataSet[j][2]) << endl;
      }
    }
  }

  sortedGrades.close();
}

void saveLowGrades(string dataSet[18][3]) {
  ofstream sortedGrades;
  sortedGrades.open("sortedLowGrade.txt", ios::out);

  sortedGrades << "FIRST NAME\tLAST NAME\tGRADES\n";
  for (int i = 0; i < 18; i++) {
    if (stof(dataSet[i][2]) <= 75.25) {
      sortedGrades << dataSet[i][0] << "\t\t";
      sortedGrades << dataSet[i][1] << "\t\t";
      sortedGrades << dataSet[i][2] << endl;
    }
  }
  sortedGrades.close();
}

int main() {
  string studentDataSet[18][3]; // COLUMN 1 = FIRST NAMES	COLUMN 2 = LAST
                                // NAMES	COLUMN 3 = GRADES
  string unsortedStudentDataSet[18][3]; // unsorted dataset
  char choice, choice2 = 'Y';

  // Reads data from the text files and inputs them into the studentDataSet
  // array
  ifstream firstName; // opens the firstNames.txt file
  int i = 0;
  firstName.open("firstNames.txt", ios::in);

  if (firstName.is_open()) {
    while (getline(firstName, studentDataSet[i][0])) {
      firstName >> studentDataSet[i][0];
      i++;
    }
  }
  firstName.close();
  i = 0;
  cout << endl;

  ifstream lastName; // opens the lastNames.txt file
  lastName.open("lastNames.txt", ios::in);

  if (lastName.is_open()) {
    while (getline(lastName, studentDataSet[i][1])) {
      lastName >> studentDataSet[i][1];
      i++;
    }
  }
  lastName.close();
  i = 0;
  cout << endl;

  ifstream grade; // opens the grades.txt file
  grade.open("grades.txt", ios::in);

  if (grade.is_open()) {
    while (getline(grade, studentDataSet[i][2])) {
      grade >> studentDataSet[i][2];
      i++;
    }
  }
  grade.close();

  for (i = 0; i < 3; i++) {
    for (int j = 0; j < 18; j++) {
      unsortedStudentDataSet[j][i] = studentDataSet[j][i];
      unsortedStudentDataSet[j][i] = studentDataSet[j][i];
      unsortedStudentDataSet[j][i] = studentDataSet[j][i];
    }
  }

  while (choice2 == 'Y') {
    system("CLS");
    cout << "A] Display All Records" << endl;
    cout << "B] Sort Data" << endl;
    cout << "C] Display Dean's List" << endl;
    cout << "D] Display Students with Poor Performance" << endl;
    cout << "Your choice: ";
    cin >> choice;
    choice = toupper(choice);
    system("CLS");

    switch (choice) {
    case 'A': // display data records
      cout << "FIRST NAME\tLAST NAME\tGRADES\n";
      for (i = 0; i < 18; i++) {
        cout << unsortedStudentDataSet[i][0] << "\t\t";
        cout << unsortedStudentDataSet[i][1] << "\t\t";
        cout << unsortedStudentDataSet[i][2] << endl;
      }

      saveUnsortedData(unsortedStudentDataSet);

      cout << "Go back? [Y/N]: ";
      cin >> choice2;
      choice2 = toupper(choice2);
      break;

    case 'B':
      // sort by lastname, firstname, grade
      cout << "A] Sort by last name" << endl;
      cout << "B] Sort by first name" << endl;
      cout << "C] Sort by grade" << endl;
      cout << "D] Back" << endl;
      cout << "Your choice: ";
      cin >> choice;
      choice = toupper(choice);
      system("CLS");

      switch (choice) {
      case 'A':
        for (i = 0; i < 18; i++) { // sorts by last name
          for (unsigned int j = 0; j < 18; j++) {
            if (studentDataSet[i][1].at(0) < studentDataSet[j][1].at(0)) {
              string tmp = studentDataSet[i][1];
              studentDataSet[i][1] = studentDataSet[j][1];
              studentDataSet[j][1] = tmp;

              string tmp2 = studentDataSet[i][0];
              studentDataSet[i][0] = studentDataSet[j][0];
              studentDataSet[j][0] = tmp2;

              string tmp3 = studentDataSet[i][2];
              studentDataSet[i][2] = studentDataSet[j][2];
              studentDataSet[j][2] = tmp3;
            }
          }
        }

        cout << "FIRST NAME\tLAST NAME\tGRADES\n";
        for (i = 0; i < 18; i++) {
          cout << studentDataSet[i][0] << "\t\t";
          cout << studentDataSet[i][1] << "\t\t";
          cout << studentDataSet[i][2] << endl;
        }

        saveLastNames(studentDataSet);

        cout << "Go back? [Y/N]: ";
        cin >> choice2;
        choice2 = toupper(choice2);
        break;

      case 'B':
        for (i = 0; i < 18; i++) { // sorts by first name
          for (unsigned int j = 0; j < 18; j++) {
            if (studentDataSet[i][0].at(0) < studentDataSet[j][0].at(0)) {
              string tmp = studentDataSet[i][0];
              studentDataSet[i][0] = studentDataSet[j][0];
              studentDataSet[j][0] = tmp;

              string tmp2 = studentDataSet[i][1];
              studentDataSet[i][1] = studentDataSet[j][1];
              studentDataSet[j][1] = tmp2;

              string tmp3 = studentDataSet[i][2];
              studentDataSet[i][2] = studentDataSet[j][2];
              studentDataSet[j][2] = tmp3;
            }
          }
        }

        cout << "FIRST NAME\tLAST NAME\tGRADES\n";
        for (i = 0; i < 18; i++) {
          cout << studentDataSet[i][0] << "\t\t";
          cout << studentDataSet[i][1] << "\t\t";
          cout << studentDataSet[i][2] << endl;
        }

        saveFirstNames(studentDataSet);

        cout << "Go back? [Y/N]: ";
        cin >> choice2;
        choice2 = toupper(choice2);
        break;

      case 'C':
        float sortedGrade[18];

        for (i = 0; i < 18; i++) {
          sortedGrade[i] =
              stof(studentDataSet[i][2]); // inputs the 3rd column into a
                                          // temporary array for sorting
        }
        qsort(sortedGrade, 18, sizeof(float), floatcomp); // sorts by grade

        cout << "FIRST NAME\tLAST NAME\tGRADES\n";

        for (i = 0; i < 18; i++) {
          sortedGrade[i] = stof(studentDataSet[i][2]);
        }
        qsort(sortedGrade, 18, sizeof(float), floatcomp);

        for (i = 0; i < 18; i++) {
          for (int j = 0; j < 18; j++) {
            if (stof(studentDataSet[j][2]) == sortedGrade[i]) {
              cout << studentDataSet[j][0] << "\t\t";
              cout << studentDataSet[j][1] << "\t\t";
              cout << studentDataSet[j][2] << endl;
            }
          }
        }

        saveGrades(studentDataSet, sortedGrade);

        cout << "Go back? [Y/N]: ";
        cin >> choice2;
        choice2 = toupper(choice2);
        break;

      case 'D':
        break;
      }
      break;

    case 'C':
      // Display all students with an average grade of 90.15 or higher. The
      // record should be sorted from highest to lowest
      float deansList[18];
      for (i = 0; i < 18; i++) {
        deansList[i] = stof(studentDataSet[i][2]);
      }
      qsort(deansList, 18, sizeof(float), floatcomp);

      cout << "FIRST NAME\tLAST NAME\tGRADES\n";
      for (i = 0; i < 18; i++) {
        for (int j = 0; j < 18; j++) {
          if (stof(studentDataSet[j][2]) == deansList[i] &&
              deansList[i] >= 90.15) {
            cout << studentDataSet[j][0] << "\t\t";
            cout << studentDataSet[j][1] << "\t\t";
            cout << stof(studentDataSet[j][2]) << endl;
          }
        }
      }

      saveDLGrades(studentDataSet, deansList);

      cout << "Go back? [Y/N]: ";
      cin >> choice2;
      choice2 = toupper(choice2);
      break;

    case 'D':
      // Display Students With Poor Performance – Display students with an
      // average grade of 75.25 or lower.
      cout << "FIRST NAME\tLAST NAME\tGRADES\n";
      for (i = 0; i < 18; i++) {
        if (stof(studentDataSet[i][2]) <= 75.25) {
          cout << studentDataSet[i][0] << "\t\t";
          cout << studentDataSet[i][1] << "\t\t";
          cout << studentDataSet[i][2] << endl;
        }
      }
      saveLowGrades(studentDataSet);

      cout << "Go back? [Y/N]: ";
      cin >> choice2;
      choice2 = toupper(choice2);
      break;

    default:
      system("CLS");
      cout << "Invalid Input!";
      break;
    }
  }
}
