/*
 *Patrick A. Pangilinan	C2A - BSCS
 *Answers:
 *1.	I used most of the predefined functiosn in the fstream header, but most
 *importantly, I used stoi(), to_string() and getline() from the string library
 *for string manipulation. 2.	I used the stoi() function to turn the score
 *from the leaderboard which is stored as an int so that I can use it to compare
 *with the int that is the concurrent score of the player. I also used
 *to_string() which turns the int to a string so that I can store the score as a
 *string in the leaderboard. 3.	I used scoring, and multilevels. I noticed that
 *it added quite a bit of fun to the game seeing as you can learn all sorts of
 *different things seeing as my game has numerous question from general trivia.
 *4.	I was able to apply constructors in a way that I was able to allocate
 *memory and deconstructors in a way that I was able to delete certain bits of
 *data that I do not need. 5.	I understood abstraction in a way that letters
 *represent a specific answer for each question and encapsulation in a way that
 *I know where all my functions are stored where I know they will be stored.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;

  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class GameModule {
  int score = 0;
  char answer = 0, choice = 0;
  string leaderboard[10]
                    [2] = {},
     playerName; // leaderboard: first column = names, second column = scores

public:
  void menuScreen();

private:
  void updateLeaderboard();
  void showLeaderboard();
  void loadLeaderboard();
  void showQuestions();
};

int main() {
  GameModule game1;
  game1.menuScreen();
}

void GameModule::menuScreen() {
  system("CLS");
  cout << "Who Wants to Be a Millionaire?" << endl;
  cout << "A Text Game By Patrick Pangilinan" << endl << endl;
  cout << "Enter 'A' to input your name." << endl;
  cout << "Enter 'B' to show the leaderboard." << endl;
  cout << "Enter 'X' to exit." << endl << endl;
  cout << "Input: ";
  cin >> choice;
  choice = toupper(choice);
  loadLeaderboard();

  switch (choice) {
  case 'A':
    system("CLS");
    cout << "Welcome dear contestant, to... Who Wants to Be A Millionaire!"
         << endl;
    cout << "We would like to ask, what is your name?: ";
    cin >> playerName;
    showQuestions();
    break;

  case 'B':
    showLeaderboard(); // shows top 10
    break;

  case 'X':
    exit(0);
    break;

  default:
    cout << "Invalid input!" << endl;
    menuScreen();
    system("pause");
    break;
  }
}

void GameModule::updateLeaderboard() {
  for (int i = 0; i < 10; i++) {
    if (leaderboard[i][1] == "" || score > stoi(leaderboard[i][1])) {
      string temp[10][2];

      for (int j = i; j < 9; j++) {
        temp[i][0] = leaderboard[i][0];
        temp[i][1] = leaderboard[i][1];
      }

      leaderboard[i][0] = playerName;
      leaderboard[i][1] = to_string(score);

      for (int j = i; j < 9; j++) {
        leaderboard[i + 1][0] = temp[i][0];
        leaderboard[i + 1][1] = temp[i][1];
      }

      ofstream lbName;
      lbName.open("leaderboardNames.txt", ios::out);

      if (lbName.is_open()) {
        for (int j = 0; j < 10; j++) {
          if (j == 9)
            lbName << leaderboard[j][0];

          else
            lbName << leaderboard[j][0] << endl;
        }
      }
      lbName.close();

      ofstream lbScore;
      lbScore.open("leaderboardScores.txt", ios::out);

      if (lbScore.is_open()) {
        for (int j = 0; j < 10; j++) {
          if (j == 9)
            lbScore << leaderboard[j][1];

          else
            lbScore << leaderboard[j][1] << endl;
        }
      }
      lbScore.close();
      break;
    }
  }
}

void GameModule::loadLeaderboard() {
  int i = 0;
  ifstream lbName;
  lbName.open("leaderboardNames.txt", ios::in);

  if (lbName.is_open()) {
    lbName >> leaderboard[i][0];
    while (getline(lbName, leaderboard[i + 1][0])) {
      lbName >> leaderboard[i + 1][0];

      i++;
      if (i == 10)
        break;
    }
  }
  lbName.close();
  i = 0;

  ifstream lbScore;
  lbScore.open("leaderboardScores.txt", ios::in);

  if (lbScore.is_open()) {
    lbScore >> leaderboard[i][1];
    while (getline(lbScore, leaderboard[i + 1][1])) {
      lbScore >> leaderboard[i + 1][1];

      i++;
      if (i == 10)
        break;
    }
  }
  lbScore.close();
}

void GameModule::showLeaderboard() {
  system("cls");
  cout << "Place\t\tNames\t\tScore" << endl;
  for (int i = 0; i < 10; i++) {
    cout << i + 1 << "\t\t";
    cout << leaderboard[i][0] << "\t\t";
    cout << leaderboard[i][1];
    cout << endl << endl;
  }
  cout << endl;
  system("pause");
  menuScreen();
}

void GameModule::showQuestions() {
  system("CLS");
  score = 0;

  // question 1
  cout << "For 10$..." << endl << endl;
  cout << "Who is the patron saint of Spain?" << endl;
  cout << "A. Saint James" << endl;
  cout << "B. Saint Peter" << endl;
  cout << "C. Saint John" << endl;
  cout << "D. Saint Jean Baptiste" << endl;

  cout << "Answer [ ]" << endl;
  gotoxy(8, 7);
  cin >> answer;
  answer = toupper(answer);

  if (answer == 'A') {
    cout << "Congratulations! Moving on to the 100$ question." << endl << endl;
    score = 10;
    system("pause");
    // question = 2;
  }

  else {
    cout << "Oof! I'm very sorry, but you will have to go home with 0$! Tough "
            "luck!"
         << endl;
    updateLeaderboard();
    system("pause");
    // question = 1;
    showLeaderboard();
  }

  // question 2
  system("CLS");
  cout << "For 100$..." << endl << endl;
  cout << "Who discovered penicillin?" << endl;
  cout << "A. Isaac Newton" << endl;
  cout << "B. Albert Einstein" << endl;
  cout << "C. Marie Curie" << endl;
  cout << "D. Alexander Fleming" << endl;

  cout << "Answer [ ]" << endl;
  gotoxy(8, 7);
  cin >> answer;
  answer = toupper(answer);

  if (answer == 'D') {
    cout << "Congratulations! Moving on to the 1,000$ question." << endl
         << endl;
    score = 100;
    system("pause");
    // question = 3;
  }

  else {
    cout << "Oof! I'm very sorry, but you will have to go home with 10$"
         << endl;
    updateLeaderboard();
    system("pause");
    // question = 1;
    showLeaderboard();
  }

  system("CLS");
  cout << "For 1000$..." << endl << endl;
  cout << "What name does deer meat go by?" << endl;
  cout << "A. Steak" << endl;
  cout << "B. Veal" << endl;
  cout << "C. Venison" << endl;
  cout << "D. Pork" << endl;

  cout << "Answer [ ]" << endl;
  gotoxy(8, 7);
  cin >> answer;
  answer = toupper(answer);

  if (answer == 'C') {
    cout << "Congratulations! Moving on to the 10,000$ question." << endl
         << endl;
    score = 1000;
    system("pause");
    // question = 4;
  }

  else {
    cout << "Oof! I'm very sorry, but you will have to go home with 100$"
         << endl;
    updateLeaderboard();
    system("pause");
    // question = 1;
    showLeaderboard();
  }

  system("CLS");
  cout << "For 10,000$..." << endl << endl;
  cout << "Which country invented tea?" << endl;
  cout << "A. India" << endl;
  cout << "B. China" << endl;
  cout << "C. Philippines" << endl;
  cout << "D. United Kingdom" << endl;

  cout << "Answer [ ]" << endl;
  gotoxy(8, 7);
  cin >> answer;
  answer = toupper(answer);

  if (answer == 'B') {
    cout << "Congratulations! Moving on to the 100,000$ question." << endl
         << endl;
    score = 10000;
    system("pause");
    // question = 5;
  }

  else {
    cout << "Oof! I'm very sorry, but you will have to go home with 1000$"
         << endl;
    updateLeaderboard();
    system("pause");
    // question = 1;
    showLeaderboard();
  }

  system("CLS");
  cout << "For 100,000$..." << endl << endl;
  cout << "Which bone are babies born without?" << endl;
  cout << "A. Knee Cap" << endl;
  cout << "B. Tail Bone" << endl;
  cout << "C. Femur" << endl;
  cout << "D. Humerus" << endl;

  cout << "Answer [ ]" << endl;
  gotoxy(8, 7);
  cin >> answer;
  answer = toupper(answer);

  if (answer == 'A') {
    cout << "Congratulations! And finally... You may proceed to the million "
            "dollar question!"
         << endl;
    cout << "I hope you're prepared for this one, " << playerName << "!" << endl
         << endl;
    score = 100000;
    system("pause");
    // question = 6;
  }

  else {
    cout << "So close! I'm very sorry, but you will have to go home with "
            "10,000$! Not bad!"
         << endl;
    updateLeaderboard();
    system("pause");
    // question = 1;
    showLeaderboard();
  }

  system("CLS");
  cout << "For 1,000,000$..." << endl << endl;
  cout << "Who is the OOP teacher of C2A (Also the coolest person)?" << endl;
  cout << "A. Ms. Nelia Rocamora" << endl;
  cout << "B. Sir Mark Anthony De Vera" << endl;
  cout << "C. Ms. Donna Garcia" << endl;
  cout << "D. Sir Franze Garcia" << endl;

  cout << "Answer [ ]" << endl;
  gotoxy(8, 7);
  cin >> answer;
  answer = toupper(answer);

  if (answer == 'B') {
    cout << "Congratulations! You're a millionaire! *cue confetti*" << endl
         << endl;
    score = 1000000;
    system("pause");
    updateLeaderboard();
    // question = 1;
    showLeaderboard();
  }

  else {
    cout << "So close! I'm very sorry, but you will have to go home with "
            "100,000$! Not bad!"
         << endl;
    updateLeaderboard();
    system("pause");
    // question = 1;
    showLeaderboard();
  }
}
