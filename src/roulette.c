#include "roulette.h"

void playRoulette(Balance* balance) {
    while(true)
    {
        RouletteBet bets[MAX_BETS];
        int numBets = 0;
        placeBets(balance, bets, &numBets);
        if (numBets == 0)
        {
            break;
        }

        int winningNumber = spinRouletteWheel();
        printUART("Winning number is: ");
        printRouNum(winningNumber);
        printlnUART("");

        processResults(winningNumber, balance, bets, numBets);
        printBalance(balance);
    }
}

int spinRouletteWheel() {
    return generateRandomNumber(0, NUM_ROULETTE_NUMBERS);
}

void placeBets(Balance* balance, RouletteBet bets[], int* numBets) {
    while (*numBets < MAX_BETS) {
        printlnUART("Enter bet type (0: number, 1: color, 2: parity, 3: stop betting): ");
        char betTypeInput = readKeypadInput();
        while(betTypeInput == 0){betTypeInput = readKeypadInput();};
        if(betTypeInput == '3')
            break;

        BetType betType = (BetType)(betTypeInput - '0');

        int betValue = 0;
        if (betType == NUMBER) {
            printUART("Enter number (0-36)");
            betValue = getAmtNoTimeout();
            while(betValue < 0 || betValue > 36)
            {
                printUART("Invalid number! Enter number (0-36)");
                betValue = getAmtNoTimeout();
            }
        }
        else if (betType == COLOR) {
            printlnUART("Enter color (0 for BLACK, 1 for RED): ");
            betValue = readKeypadInput();
            while(betValue != '0' && betValue != '1'){betValue = readKeypadInput();};
            betValue -= '0';
        }
        else if (betType == PARITY) {
            printlnUART("Enter parity (0 for EVEN, 1 for ODD): ");
            betValue = readKeypadInput();
            while(betValue != '0' && betValue != '1' && betValue != '2'){betValue = readKeypadInput();};
            betValue -= '0';
        }

        printUART("Enter bet amount");
        int betAmount = getAmtNoTimeout();
        
        bets[*numBets].wager.amount = 0;
        if (bet(balance, betAmount, &bets[*numBets].wager)) {
            bets[*numBets].type = betType;
            bets[*numBets].value = betValue;
            (*numBets)++;
        }
        else {
            printlnUART("Insufficient balance for this bet.");
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

        printBet(bets[i]);

        if (win) {
            winBet(balance, &bets[i].wager, payoutMultiplier(bets[i].type) + 1);
            printlnUART("won!");
        }
        else {
            printlnUART("lost.");
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

void printRouNum(int num) {
    printInt(num, 2);
    switch(getColor(num))
    {
        case GREEN:
            printUART(" (Green) ");
            break;
        case RED:
            printUART(" (Red) ");
            break;
        case BLACK:
            printUART(" (Black) ");
            break;
    }
}

void printBet(RouletteBet bet)
{
    printUART("Your ");
    printInt(bet.wager.amount, MAX_AMT_LENGTH);
    printUART(" Chowncoin bet on the ");
    switch(bet.type)
    {
        case NUMBER:
            printUART("number being ");
            printRouNum(bet.value);
            break;
        case COLOR:
            printUART("color being ");
            switch(bet.value)
            {
                case RED:
                    printUART("red");
                    break;
                case BLACK:
                    printUART("black");
                    break;
            }
            break;
        case PARITY:
            printUART("parity being ");
            switch(bet.value)
            {
                case 0:
                    printUART("even");
                    break;
                case 1:
                    printUART("odd");
                    break;
            }
            break;
    }
    printUART(" ");
}
