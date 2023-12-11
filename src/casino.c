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
    printlnUART("Are you over 21? Press 'A' for Yes, 'B' for No.");

    while (1) {
        char userInput = readKey();

        if (userInput == 'A') {
            return 1;  // User is over 21
        } else if (userInput == 'B') {
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
        printlnUART("Welcome to the casino entrance!");

        int running = 1;

        Balance *userBalance;
        initBalance(userBalance);

        while (running) {
            // Display options for the user
            printlnUART("Options:");
            printlnUART("1. Cash In");
            printlnUART("2. Cash Out");
            printlnUART("3. Exit");
            printlnUART("4. View Casino Games");
            printlnUART("Enter your choice: ");

            char choice = readKey();

            switch (choice) {
                case '1':
                    // Cash in using the adminModBalance function
                    adminModBalance(userBalance, POSITIVE);
                    printlnUART("Cash In Successful.");
                    break;
                case '2':
                    // Cash out
                    adminModBalance(userBalance, NEGATIVE);
                    break;
                case '3':
                    // Exit if the user balance is 0
                    if (userBalance == 0) {
                        running = 0;
                    }
                    break;
                case '4':
                    // View casino games
                    // TODO: Implement viewGames function
                    // viewGames();
                    break;
                default:
                    printlnUART("Invalid choice. Please try again.");
                    break;
            }
        }
    } else {
        // User is not over 21, exit
        printlnUART("Exiting. You must be over 21 to enter the casino.");
    }

    cleanupCasino(&oledStruct);
}
