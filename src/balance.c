/* ************************************************************************** */
/** @File Name
  balance.c

  @Description
    This file holds the functionality for managing a player's balance in the casino game.
    It allows for the creation of an integer balance, adding and subtracting from the balance,
    and includes functions for different purposes, such as admin add to balance with a secret code.
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#include "balance.h"
#include "keypad1.h"
#include "time.h"
#include <string.h>
#include <stdio.h>

#define ADMIN_CODE_LENGTH 6
#define ADMIN_SECRET_CODE "123456"

Balance* createBalance(void) {
    Balance* balance = (Balance*)malloc(sizeof(Balance));
    if (balance == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }

    balance->balance = 0;
    return balance;
}

int addToBalance(Balance* balance, int amount) {
    balance->balance += amount;
    return balance->balance;
}

int subtractFromBalance(Balance* balance, int amount) {
    balance->balance -= amount;
    return balance->balance;
}

int adminAddToBalance(Balance* balance, int amount, const char* adminCode) {
    // Prompt for admin code entry
    //TODO: implement print
    printf("Enter admin code: ");

    char enteredCode[ADMIN_CODE_LENGTH + 1] = {0};
    unsigned int startTime = getTicks();

    int codeIndex = 0;

    while (getMsSince(startTime) < ADMIN_CODE_TIMEOUT) {
        // Read keypad input
        char key = readKey();  // Replace with actual readKey function
        if (key != '\0') {
            // Update entered code with the pressed key
            if (codeIndex < ADMIN_CODE_LENGTH) {
                enteredCode[codeIndex++] = key;
                enteredCode[codeIndex] = '\0';  // Null-terminate the string
            }
        }

        // Check if the entered code matches the secret admin code
        if (strcmp(enteredCode, ADMIN_SECRET_CODE) == 0) {
            // Admin code matched, add to balance
            balance->balance += amount;
            return balance->balance;
        }
    }

    // Admin code entry timed out, return current balance
    return balance->balance;
}
