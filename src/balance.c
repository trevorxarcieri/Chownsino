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

void initBalance(Balance* balance) {
    balance->balance = 0;
}

void addToBalance(Balance* balance, int amount) {
    balance->balance += amount;
}

void subtractFromBalance(Balance* balance, int amount) {
    balance->balance -= amount;
}

void adminAddToBalance(Balance* balance) {
    char enteredCode[ADMIN_CODE_LENGTH + 1] = {0};
    unsigned int codeStart = getTicks();  // Assuming getTicks returns the current time in milliseconds

    int codeIndex = 0;

    // Request admin code entry via UART
    UART4_putstr("Enter admin code: ");

    while (getMsSince(codeStart) < ADMIN_CODE_TIMEOUT) {
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
            // Admin code matched, prompt for the amount to add
            UART4_putstr("Enter amount to add to user balance (type non-number to stop): ");

            // Read the amount input from the admin via keypad
            char amountStr[MAX_AMT_LENGTH + 1];
            unsigned int amtStart = getTicks();
            int amountIndex = 0;
            while (getMsSince(amtStart) < ADMIN_AMT_TIMEOUT) {
                // Read keypad input
                char key = readKey();  // Replace with actual readKey function
                if (key != '\0') {
                    // If admin enters non-number, break and stop requesting digits
                    if (key > '9')
                    {
                        break;
                    }

                    // Update entered code with the pressed key
                    if (amountIndex < MAX_AMT_LENGTH) {
                        amountStr[amountIndex++] = key;
                        amountStr[amountIndex] = '\0';  // Null-terminate the string
                    }
                }
            }

            unsigned int amountToAdd = amtFromStr(amountStr, amountIndex);

            // Add the amount to the user balance
            balance->balance += amountToAdd;

            // Display a message indicating successful admin balance addition
            UART4_putstr("Admin: Balance added successfully.\n");
            return;
        }
    }

    // Admin code entry timed out, return current balance
    UART4_putstr("Admin: Admin code entry timed out. Access denied.\n");
}

unsigned int amtFromStr(char* str, int len)
{
    unsigned int amount = 0;
    for(int i = 0; i < len; i++)
    {
        amount *= 10;
        amount += str[i] - '0';
    }
    return amount;
}

