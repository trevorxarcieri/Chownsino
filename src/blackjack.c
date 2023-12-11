#include "blackjack.h"

// Global game state variables
Balance userBalance;
CardSet cardSet;
PmodOLEDrgb oledStruct; // Placeholder for the OLED structure

void displayPlayerHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards) {
    printUART("Player Hand: ");
    displayFullHand(oledStruct, cards, numCards);
}

void displayFullDealerHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards) {
    printUART("Dealer Hand: ");
    displayFullHand(oledStruct, cards, numCards);
}

void displayFullHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards) {
    for(int i = 0; i < numCards - 1; i++)
    {
        displayCard(oledStruct, cards[i], 0);
        printUART(", ");
    }
    displayCard(oledStruct, cards[numCards - 1], 0);
}

void displayDealerHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards) {
    printUART("Dealer Hand: ");
    displayCard(oledStruct, cards[0], 0);
}

void displayGameResult(PmodOLEDrgb* oledStruct, const char* result) {
    printlnUART((char *) result);
}

// Function to calculate the total value of a hand
int calculateHandValue(Card* hand, int numCards) {
    int value = 0;
    int aceCount = 0;
    for (int i = 0; i < numCards; i++) {
        if (hand[i].value >= JACK) {
            value += 10;
        }
        else if (hand[i].value == ACE) {
            value += 11;
            aceCount++;
        }
        else {
            value += hand[i].value;
        }
    }
    // Adjust for Aces
    while (value > 21 && aceCount > 0) {
        value -= 10;
        aceCount--;
    }
    return value;
}

// Function to check for Blackjack
bool isBlackjack(Card* hand) {
    return (hand[0].value == ACE && (hand[1].value >= TEN && hand[1].value <= KING)) ||
        (hand[1].value == ACE && (hand[0].value >= TEN && hand[0].value <= KING));
}

// Function for the player's turn
void playerTurn(PmodOLEDrgb* oledStruct, Card* playerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus) {
    while (true) {
        printlnUART("Hit (A) or Stand (B)?");
        char decision = readKeypadInput();
        if (decision == 'A') {
            pullTopCard(&playerCards[(*numCards)++], cardSet, shuffleStatus);
            displayPlayerHand(oledStruct, playerCards, *numCards);
        }
        else if (decision == 'B') {
            break;
        }
        
        int handValue = calculateHandValue(playerCards, *numCards);
        if (handValue > 21) {
            printlnUART("Player busts!");
            return;
        }

    }
}

// Function for the dealer's turn
void dealerTurn(PmodOLEDrgb* oledStruct, Card* dealerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus) {
    while (calculateHandValue(dealerCards, *numCards) < 17) {
        pullTopCard(&dealerCards[(*numCards)++], cardSet, shuffleStatus);
        displayFullDealerHand(oledStruct, dealerCards, *numCards);
    }
}

// Function to determine the winner
bool isPlayerWinner(Card* playerCards, int playerNumCards, Card* dealerCards, int dealerNumCards) {
    int playerValue = calculateHandValue(playerCards, playerNumCards);
    int dealerValue = calculateHandValue(dealerCards, dealerNumCards);

    return playerValue <= 21 && (dealerValue > 21 || playerValue > dealerValue);
}

// Function to offer and handle double down
bool offerAndHandleDoubleDown(PmodOLEDrgb* oledStruct, Card* playerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus, Bet* currentBet, Balance* userBalance) {
    printlnUART("Do you want to Double Down? (A for yes, B for no)");
    char decision = readKeypadInput();

    if (decision == 'Y' || decision == 'y') {
        if (bet(userBalance, currentBet->amount, currentBet)) {
            pullTopCard(&playerCards[(*numCards)++], cardSet, shuffleStatus);
            displayPlayerHand(oledStruct, playerCards, *numCards);
            return true;
        }
        else {
            printlnUART("Insufficient balance to double down.");
        }
    }
    return false;
}

// Function to offer and handle split
void offerAndHandleSplit(PmodOLEDrgb* oledStruct, Card* playerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus, Bet* currentBet, Balance* userBalance) {
    if (playerCards[0].value == playerCards[1].value) {
        printlnUART("Do you want to Split? (A for yes, B for no)");
        char decision = readKeypadInput();

        if (decision == 'A') {
            Bet additionalBet = *currentBet;

            if (bet(userBalance, additionalBet.amount, &additionalBet)) {
                Card splitHands[2][5];
                int numCardsSplit[2] = { 1, 1 };
                splitHands[0][0] = playerCards[0];
                numCardsSplit[0]++;
                splitHands[1][0] = playerCards[1];
                numCardsSplit[1]++;

                pullTopCard(&splitHands[0][1], cardSet, shuffleStatus);
                pullTopCard(&splitHands[1][1], cardSet, shuffleStatus);
                displayPlayerHand(oledStruct, splitHands[0], numCardsSplit[0]);
                displayPlayerHand(oledStruct, splitHands[1], numCardsSplit[1]);

                for (int i = 0; i < 2; i++) {
                    playerTurn(oledStruct, splitHands[i], &numCardsSplit[i], cardSet, shuffleStatus);
                    // Handle bets and display results for each hand
                }
            }
            else {
                printlnUART("Insufficient balance to split.");
            }
        }
    }
}

// Main gameplay function
void playBlackjack(Balance userBalance, PmodOLEDrgb oledStruct) {
    blackjackInit(); 

    Bet currentBet;
    ShuffleStatus shuffleStatus;

    printUART("Enter the amount you'd like to bet");
    int betAmount = getAmtNoTimeout(); /* get bet amount from user */
    if (!bet(&userBalance, betAmount, &currentBet)) {
        return;
    }

    Card playerCards[5];
    Card dealerCards[5];
    pullTopCard(&playerCards[0], &cardSet, &shuffleStatus);
    pullTopCard(&dealerCards[0], &cardSet, &shuffleStatus);
    pullTopCard(&playerCards[1], &cardSet, &shuffleStatus);
    pullTopCard(&dealerCards[1], &cardSet, &shuffleStatus);
    
    int numPlayerCards = 2;
    int numDealerCards = 2;
    
    displayPlayerHand(&oledStruct, playerCards, numPlayerCards);
    displayDealerHand(&oledStruct, dealerCards, numDealerCards);

    bool playerHasBlackjack = isBlackjack(playerCards);
    bool dealerHasBlackjack = isBlackjack(dealerCards);

    if (playerHasBlackjack && !dealerHasBlackjack) {
        winBet(&userBalance, &currentBet, 3);
        displayGameResult(&oledStruct, "Player wins with Blackjack!");
        printBalance(&userBalance);
        return;
    }
    else if (dealerHasBlackjack) {
        displayGameResult(&oledStruct, "Dealer wins with Blackjack!");
        printBalance(&userBalance);
        return;
    }
    else if (playerHasBlackjack && dealerHasBlackjack) {
        displayGameResult(&oledStruct, "Push: Both have Blackjack!");
        printBalance(&userBalance);
        return;
    }

    bool doubleDownOccurred = offerAndHandleDoubleDown(&oledStruct, playerCards, &numPlayerCards, &cardSet, &shuffleStatus, &currentBet, &userBalance);
    if (!doubleDownOccurred) {
        offerAndHandleSplit(&oledStruct, playerCards, &numPlayerCards, &cardSet, &shuffleStatus, &currentBet, &userBalance);
    }

    if (!playerHasBlackjack) {
        playerTurn(&oledStruct, playerCards, &numPlayerCards, &cardSet, &shuffleStatus);
    }
    if (calculateHandValue(playerCards, numPlayerCards) <= 21) {
        dealerTurn(&oledStruct, dealerCards, &numDealerCards, &cardSet, &shuffleStatus);
    }

    bool playerWins = isPlayerWinner(playerCards, numPlayerCards, dealerCards, numDealerCards);
    if (playerWins) {
        winBet(&userBalance, &currentBet, 2);
        displayGameResult(&oledStruct, "Player wins!");
    }
    else {
        displayGameResult(&oledStruct, "Dealer wins!");
    }

    printBalance(&userBalance);
}

// Initialization of the game state
void blackjackInit() {
    initCardSet(&cardSet, 1, SHOE_RATIO);
}
