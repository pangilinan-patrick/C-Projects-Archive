#include <stdio.h>
/*
 * Three departments:
 * Fire, Police, Sanitation
 * Each assigned a number in the range of 1-7
 * Fire #, Police #, Sanitation # must all be different
 * Fire # + Police # + Sanitation # must be equal to 12
 * Police # must be even
 *
 * OUTPUT:
 * All permutations of valid departments numbers.
 */

int main() {
  int fire, police, sanitation;

  for (fire = 1; fire < 8; fire++) {
    for (police = 2; police < 8; police = police + 2) {
      for (sanitation = 1; sanitation < 8; sanitation++) {
        if ((fire + police + sanitation == 12) && (fire != police) &&
            (fire != sanitation) && (police % 2 == 0)) {
          printf("Fire #%d Police #%d Sanitation #%d\n", fire, police,
                 sanitation);
        }
      }
    }
  }
  return 0;
}
