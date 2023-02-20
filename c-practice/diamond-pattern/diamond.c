#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int upperHalf();
int lowerHalf();
int main() {
  upperHalf();
  printf("\n");
  lowerHalf();

  return 0;
}

int upperHalf() {
  int NOD = 1; // left side dashes, rows, Number of Dashes (reverse), iterations
  int iter = 0;
  bool nextRow = false;
  bool left = true;

  for (int i = NOD; i <= 5; i++) {
    printf("-");
    usleep(100000);

    // if dashes have reached the end of the line, then do the following:
    if (i == 5) {
      // if left side is being printed, then print first asterisk
      if (left == true)
        printf("*");
      usleep(100000);

      // if NOD is not equal to one (printin is now at the second row), then
      // print the subsequent "* and -" print until the NOD, which in this case
      // is the amount of "* and -", is reached if j is not at the initial
      // value, then print "*". This is done to prevent multiple iterations of
      // "*" at the start
      if (NOD != 1 && left == true) {
        for (int j = 0; j < NOD; j++) {
          if (j != 0) {
            printf("*");
            usleep(100000);
          }
          printf("-");
          usleep(100000);
        }
      }
      // return back to the loop once more, for the number of dashes required,
      // but not before doing the following actions below:
      i = NOD;
      iter++;

      // start the printing of the right side by making left = false
      // if program is at the second iteration of the first line, then make
      // nextRow true, and reset iterations for the next row make nextRow =
      // true, to print a new line (wit hthe conditional below), and reset all
      // variables, excetp for NOD reset iterations
      left = false;
      if (iter == 2) {
        nextRow = true;
        iter = 0;
      }
    }

    // if right (left = false) side is done, then print new line, and decrease
    // the number of dashes, and reset left
    if (left == false && nextRow == true) {
      if (NOD == 1) {
        printf("-");
        usleep(100000);
      }
      printf("\n");
      usleep(100000);
      NOD++;
      nextRow = false;
      left = true;
    }
  }
  return 0;
}

int lowerHalf() {
  int NOD = 1;
  int iter = 0;
  bool left = true;

  for (int i = 1; i <= NOD && NOD <= 5; i++) {
    printf("-");
    usleep(100000);

    if (i == NOD) {
      if (left == true) {
        for (int j = 5; NOD <= j; j--) {
          printf("*");
          usleep(100000);

          if (j != NOD) {
            printf("-");
            usleep(100000);
          }

          if (j == NOD) {
            left = false;
          }
        }
      }

      i = 0;
      iter++;

      if (left == false && iter == 2) {
        NOD++;
        printf("\n");
        usleep(100000);

        iter = 0;
        left = true;
      }
    }
  }
  return 0;
}
