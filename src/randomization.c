/* ************************************************************************** */
/** Descriptive File Name

  @File Name
    randomization.c

  @Description
    This file holds the functionality for creating randomization used
    throughout the casino.
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "randomization.h"

void randomizationInit(void) {
    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));
}

int generateRandomNumber(int a, int b) {
    // Ensure that a is less than b
    if (a >= b) {
        return -1; // Invalid input, return an error code
    }

    // Generate a random number in the range [a, b)
    return (rand() % (b - a)) + a;
}
