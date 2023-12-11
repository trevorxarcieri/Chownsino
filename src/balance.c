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

void addToBalance(Balance* balance, unsigned int amount) {
    balance->balance += amount;
}

void subtractFromBalance(Balance* balance, unsigned int amount) {
    if (amount > balance->balance)
    {
        balance->balance = 0;
    }
    balance->balance -= amount;
}

void adminModBalance(Balance* balance, Sign sign) {
    char enteredCode[ADMIN_CODE_LENGTH + 1] = {0};
    unsigned int codeStart = getTicks();  // Assuming getTicks returns the current time in milliseconds

    int codeIndex = 0;

    // Request admin code entry via UART
    printlnUART("Enter admin code: ");

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
            printUART("Enter amount to ");
            if(sign == POSITIVE)
                printUART("add to");
            else
                printUART("subtract from");
            printUART(" user balance");

            // Read the amount input from the admin via keypad
            unsigned int amount = getAmt(ADMIN_AMT_TIMEOUT);

            if(sign == POSITIVE)
            {
                addToBalance(balance, amount);
            }
            else
            {
                subtractFromBalance(balance, amount);
            }

            // Display a message indicating successful admin balance addition
            printBalance(balance);
            return;
        }
        
        if(codeIndex == ADMIN_CODE_LENGTH)
        {
            break;
        }
    }

    // Admin code entry timed out, return current balance
    printlnUART("Admin: Admin code entry failed. Access denied.");
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

unsigned int getAmtNoTimeout()
{
    return getAmt(MAX_TIMEOUT);
}

unsigned int getAmt(unsigned int timeout)
{
    printlnUART(" (type non-number to stop): "); 
    char amountStr[MAX_AMT_LENGTH + 1];
    unsigned int amtStart = getTicks();
    int amountIndex = 0;
    while (getMsSince(amtStart) < timeout) {
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

        if(amountIndex == MAX_AMT_LENGTH)
        {
            break;
        }
    }

    return amtFromStr(amountStr, amountIndex);
}

void printBalance(Balance* balance)
{
    printUART("Current user balance: ");
    printInt(balance->balance, MAX_AMT_LENGTH);
    printlnUART(" Chowncoin");
}

void printInt(unsigned int num, int digits)
{
    char str[digits + 1];
    str[0] = '0';
    str[1] = '\0';
    for(int i = 1; i < digits + 1 && num != 0; i++)
    {
        for(int j = i; j > 0; j--)
        {
            str[j] = str[j - 1]; 
        }
        str[0] = '0' + num % 10;
        str[i] = '\0';
        num /= 10;
    }
    printUART(str);
}
