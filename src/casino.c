/* ************************************************************************** */
/** @File Name
  casino.c

  @Description
    This file holds the functionality for initializing, starting,
    and cleaning up the casino system, including both input and output modules.
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#include "casino.h"

void initCasino(PmodOLEDrgb* oledStruct) {
    // Initialize input module
    initInput();

    // Initialize output module
    initOutput(oledStruct);
}

void cleanupCasino(PmodOLEDrgb* oledStruct) {
    // Cleanup output module
    cleanupOutput(oledStruct);

    // Cleanup input module
}

// Function to ask the user if they are over 21 using UART
int askUserAge() {
    UART4_putstr("Are you over 21? Press 'Y' for Yes, 'N' for No: ");

    while (1) {
        char userInput = readKey();

        if (userInput == 'Y' || userInput == 'y') {
            return 1;  // User is over 21
        } else if (userInput == 'N' || userInput == 'n') {
            return 0;  // User is not over 21
        }
    }
}

void startCasino() {
    PmodOLEDrgb oledStruct;
    initCasino(&oledStruct);

    // Ask the user if they are over 21
    int isOver21 = askUserAge();

    if (isOver21) {
        // User is over 21, continue with casino activities
        UART4_putstr("Welcome to the casino entrance!\n");

        while (1) {
            // Display options for the user
            UART4_putstr("Options:\n");
            UART4_putstr("1. Cash In\n");
            UART4_putstr("2. Cash Out\n");
            UART4_putstr("3. Exit\n");
            UART4_putstr("4. View Casino Games\n");
            UART4_putstr("Enter your choice: ");

            char choice = readKey();

            switch (choice) {
                case '1':
                    // Cash in using the adminAddToBalance function
                    // Note: You need to implement the adminAddToBalance function based on your requirements
                    // For simplicity, assume the function returns the updated user balance
                    // Example: userBalance = adminAddToBalance(&userBalance, amount, adminCode);
                    // Display the updated user balance
                    UART4_putstr("Cash In Successful. Updated User Balance: ");
                    // TODO: Implement printUserBalance function
                    // printUserBalance(userBalance);
                    break;
                case '2':
                    // Cash out
                    // TODO: Implement cashOut function
                    // cashOut(&userBalance);
                    break;
                case '3':
                    // Exit if the user balance is 0
                    // TODO: Implement exit function
                    // if (userBalance == 0) {
                    //     exitCasino();
                    // }
                    break;
                case '4':
                    // View casino games
                    // TODO: Implement viewGames function
                    // viewGames();
                    break;
                default:
                    UART4_putstr("Invalid choice. Please try again.\n");
                    break;
            }
        }
    } else {
        // User is not over 21, exit
        UART4_putstr("Exiting. You must be over 21 to enter the casino.\n");
    }

    cleanupCasino(&oledStruct);
}
