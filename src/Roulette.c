#include "balance.h"
#include "bet.h"
#include "randomization.h"
#include "input_wrapper.h"
#include "output_wrapper.h"

#define NUM_ROULETTE_NUMBERS 37 // Numbers 0-36
#define MAX_BETS 5 // Max number of bets per round
#define RED 1
#define BLACK 0
#define GREEN -1

typedef enum { NUMBER, COLOR, PARITY } BetType;
typedef struct { BetType type; int value; int amount; } RouletteBet;

// Function Declarations
void playRoulette(Balance* balance);
int spinRouletteWheel();
void placeBets(Balance* balance, RouletteBet bets[], int* numBets);
void processResults(int winningNumber, Balance* balance, RouletteBet bets[], int numBets);
int getColor(int number);
int payoutMultiplier(BetType type);
void printInt(int num);
void clearScreen();
char readKeypadInput(); // Implement this based on your keypad

int main() {
    Balance userBalance;
    initBalance(&userBalance);

    while (true) {
        playRoulette(&userBalance);
        // Add exit condition if needed
    }

    return 0;
}

void playRoulette(Balance* balance) {
    RouletteBet bets[MAX_BETS];
    int numBets = 0;
    placeBets(balance, bets, &numBets);

    int winningNumber = spinRouletteWheel();
    printlnUART("Winning number is: ");
    printInt(winningNumber);

    processResults(winningNumber, balance, bets, numBets);
    printBalance(balance);
}

int spinRouletteWheel() {
    return generateRandomNumber(0, NUM_ROULETTE_NUMBERS);
}

void placeBets(Balance* balance, RouletteBet bets[], int* numBets) {
    while (*numBets < MAX_BETS) {
        printlnUART("Enter bet type (0: NUMBER, 1: COLOR, 2: PARITY): ");
        char betTypeInput = readKeypadInput();
        BetType betType = (BetType)(betTypeInput - '0');

        int betValue = 0;
        if (betType == NUMBER) {
            printlnUART("Enter number (0-36): ");
            betValue = /* Read number from user */;
        }
        else if (betType == COLOR) {
            printlnUART("Enter color (0 for BLACK, 1 for RED): ");
            betValue = /* Read color from user */;
        }
        else if (betType == PARITY) {
            printlnUART("Enter parity (0 for EVEN, 1 for ODD): ");
            betValue = /* Read parity from user */;
        }

        printlnUART("Enter bet amount: ");
        int betAmount = /* Read bet amount from user */;

        if (betAmount <= balance->balance) {
            bets[*numBets].type = betType;
            bets[*numBets].value = betValue;
            bets[*numBets].amount = betAmount;
            subtractFromBalance(balance, betAmount);
            (*numBets)++;
        }
        else {
            printlnUART("Insufficient balance for this bet.");
        }

        printlnUART("Place another bet? (Y/N): ");
        char anotherBet = readKeypadInput();
        if (anotherBet == 'N' || anotherBet == 'n') {
            break;
        }
    }
}

void processResults(int winningNumber, Balance* balance, RouletteBet bets[], int numBets) {
    int winningColor = getColor(winningNumber);
    int winningParity = winningNumber % 2;

    for (int i = 0; i < numBets; i++) {
        int win = 0;
        switch (bets[i].type) {
        case NUMBER:
            win = (winningNumber == bets[i].value);
            break;
        case COLOR:
            win = (winningColor == bets[i].value);
            break;
        case PARITY:
            win = (winningNumber > 0 && winningParity == bets[i].value);
            break;
        }

        if (win) {
            int winnings = bets[i].amount * payoutMultiplier(bets[i].type);
            addToBalance(balance, winnings);
            printlnUART("Win!");
        }
        else {
            printlnUART("Lose!");
        }
    }
}

int getColor(int number) {
    if (number == 0) {
        return GREEN;
    }

    int redNumbers[] = { 1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36 };
    for (int i = 0; i < sizeof(redNumbers) / sizeof(redNumbers[0]); i++) {
        if (number == redNumbers[i]) {
            return RED;
        }
    }
    return BLACK;
}

int payoutMultiplier(BetType type) {
    switch (type) {
    case NUMBER:
        return 35; // Single number pays 35 to 1
    case COLOR:
    case PARITY:
        return 1;  // Red/Black and Odd/Even pay 1 to 1
    default:
        return 0;  // Default case, should not occur
    }
}

void printInt(int num) {
    char buffer[12]; // Enough for an int
    sprintf(buffer, "%d", num); // Convert int to string
    printlnUART(buffer); // Use your UART print function
}
