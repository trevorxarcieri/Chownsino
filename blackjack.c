#include "balance.h"
#include "bet.h"
#include "card.h"
#include "cards.h"
#include "casino.h"
#include "input_wrapper.h"
#include "output_wrapper.h"
#include "randomization.h"

// Global game state variables
Balance userBalance;
CardSet cardSet;
PmodOLEDrgb oledStruct; // Placeholder for the OLED structure

// Placeholder for display functions
void displayPlayerHand(Card* cards, int numCards) {
    // Placeholder: Implement display logic
}

void displayDealerHand(Card* cards, int numCards) {
    // Placeholder: Implement display logic
}

void displayGameResult(const char* result) {
    printlnUART(result);
}

void displayBalance(Balance* balance) {
    // Placeholder: Implement balance display logic
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

// Function to get a user decision (hit or stand)
char getUserDecision() {
    printlnUART("Hit (H) or Stand (S)?");
    return readKeypadInput();
}

// Function for the player's turn
void playerTurn(Card* playerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus) {
    while (true) {
        int handValue = calculateHandValue(playerCards, *numCards);
        displayPlayerHand(playerCards, *numCards);
        if (handValue > 21) {
            printlnUART("Player busts!");
            return;
        }

        char decision = getUserDecision();
        if (decision == 'H') {
            playerCards[(*numCards)++] = pullTopCard(cardSet, shuffleStatus);
        }
        else if (decision == 'S') {
            break;
        }
    }
}

// Function for the dealer's turn
void dealerTurn(Card* dealerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus) {
    while (calculateHandValue(dealerCards, *numCards) < 17) {
        dealerCards[(*numCards)++] = pullTopCard(cardSet, shuffleStatus);
    }
}

// Function to determine the winner
bool isPlayerWinner(Card* playerCards, int playerNumCards, Card* dealerCards, int dealerNumCards) {
    int playerValue = calculateHandValue(playerCards, playerNumCards);
    int dealerValue = calculateHandValue(dealerCards, dealerNumCards);

    return playerValue <= 21 && (dealerValue > 21 || playerValue > dealerValue);
}

// Function to offer and handle double down
bool offerAndHandleDoubleDown(Card* playerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus, Bet* currentBet, Balance* userBalance) {
    printlnUART("Do you want to Double Down? (Y/N)");
    char decision = readKeypadInput();

    if (decision == 'Y' || decision == 'y') {
        if (bet(userBalance, currentBet->amount, currentBet)) {
            playerCards[(*numCards)++] = pullTopCard(cardSet, shuffleStatus);
            displayPlayerHand(playerCards, *numCards);
            return true;
        }
        else {
            printlnUART("Insufficient balance to double down.");
        }
    }
    return false;
}

// Function to offer and handle split
void offerAndHandleSplit(Card* playerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus, Bet* currentBet, Balance* userBalance) {
    if (playerCards[0].value == playerCards[1].value) {
        printlnUART("Do you want to Split? (Y/N)");
        char decision = readKeypadInput();

        if (decision == 'Y' || decision == 'y') {
            Bet additionalBet = *currentBet;

            if (bet(userBalance, additionalBet.amount, &additionalBet)) {
                Card splitHands[2][5];
                int numCardsSplit[2] = { 1, 1 };
                splitHands[0][0] = playerCards[0];
                splitHands[1][0] = playerCards[1];

                splitHands[0][1] = pullTopCard(cardSet, shuffleStatus);
                splitHands[1][1] = pullTopCard(cardSet, shuffleStatus);

                for (int i = 0; i < 2; i++) {
                    playerTurn(splitHands[i], &numCardsSplit[i], cardSet, shuffleStatus);
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
void playBlackjack() {
    Bet currentBet;
    ShuffleStatus shuffleStatus;

    int betAmount = /* get bet amount from user */;
    if (!bet(&userBalance, betAmount, &currentBet)) {
        return;
    }

    Card playerCards[5];
    Card dealerCards[5];
    playerCards[0] = pullTopCard(&cardSet, &shuffleStatus);
    dealerCards[0] = pullTopCard(&cardSet, &shuffleStatus);
    playerCards[1] = pullTopCard(&cardSet, &shuffleStatus);
    dealerCards[1] = pullTopCard(&cardSet, &shuffleStatus);

    bool playerHasBlackjack = isBlackjack(playerCards);
    bool dealerHasBlackjack = isBlackjack(dealerCards);

    if (playerHasBlackjack && !dealerHasBlackjack) {
        winBet(&userBalance, &currentBet, 3);
        displayGameResult("Player wins with Blackjack!");
        displayBalance(&userBalance);
        return;
    }
    else if (dealerHasBlackjack) {
        displayGameResult("Dealer wins with Blackjack!");
        displayBalance(&userBalance);
        return;
    }
    else if (playerHasBlackjack && dealerHasBlackjack) {
        displayGameResult("Push: Both have Blackjack!");
        displayBalance(&userBalance);
        return;
    }

    bool doubleDownOccurred = offerAndHandleDoubleDown(playerCards, &numPlayerCards, &cardSet, &shuffleStatus, &currentBet, &userBalance);
    if (!doubleDownOccurred) {
        offerAndHandleSplit(playerCards, &numPlayerCards, &cardSet, &shuffleStatus, &currentBet, &userBalance);
    }

    int numPlayerCards = 2;
    int numDealerCards = 2;
    if (!playerHasBlackjack) {
        playerTurn(playerCards, &numPlayerCards, &cardSet, &shuffleStatus);
    }
    if (calculateHandValue(playerCards, numPlayerCards) <= 21) {
        dealerTurn(dealerCards, &numDealerCards, &cardSet, &shuffleStatus);
    }

    bool playerWins = isPlayerWinner(playerCards, numPlayerCards, dealerCards, numDealerCards);
    if (playerWins) {
        winBet(&userBalance, &currentBet, 2);
        displayGameResult("Player wins!");
    }
    else {
        displayGameResult("Dealer wins!");
    }

    displayBalance(&userBalance);
}

// Initialization of the game state
void gameInit() {
    randomizationInit();
    initCasino(&oledStruct);
    initBalance(&userBalance);
    initCardSet(&cardSet, 1, SHOE_RATIO);
}

// Cleanup function
void gameCleanup() {
    cleanupCasino(&oledStruct);
}

// Main function
int main() {
    gameInit();
    playBlackjack();
    gameCleanup();
    return 0;
}
