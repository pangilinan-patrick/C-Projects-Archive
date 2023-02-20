#include <stdio.h>

int main() {
  int array[5][5] = {2, 3, 4, 5, 6};

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (i != 0) {
        if (j == 0)
          array[i][j] = array[i - 1][j] + 1;
        else
          array[i][j] = array[i][j - 1] + array[i - 1][j];
      }
      printf("%d ", array[i][j]);

      if (j == 4)
        printf("\n");
    }
  }
  return 0;
}
