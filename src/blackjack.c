#include "blackjack.h"

void displayPlayerHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards) {
    printUART("Player Hand: ");
    displayFullHand(oledStruct, cards, numCards);
}

void displayFullDealerHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards) {
    printUART("Dealer Hand: ");
    displayFullHand(oledStruct, cards, numCards);
}

void displayDealerHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards) {
    printUART("Dealer Hand: ");
    displayCard(oledStruct, cards[0], 0);
    printlnUART("");
}

void displayGameResult(PmodOLEDrgb* oledStruct, const char* result) {
    printUART((char *) result);
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
    printlnUART("Hit (A) or Stand (B)?");
    char decision = readKeypadInput();
    while (true) {
        if (decision == 'A') {
            pullTopCard(&playerCards[(*numCards)++], cardSet, shuffleStatus);
            if(*numCards == MAX_BJ_HAND)
                break;
            int handValue = calculateHandValue(playerCards, *numCards);
            if (handValue > 21) {
                printlnUART("Player busts!");
                return;
            }
            displayPlayerHand(oledStruct, playerCards, *numCards);
            printlnUART("Hit (A) or Stand (B)?");
        }
        else if (decision == 'B') {
            break;
        }
        
        decision = readKeypadInput();
    }
}

// Function for the dealer's turn
void dealerTurn(PmodOLEDrgb* oledStruct, Card* dealerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus) {
    while (calculateHandValue(dealerCards, *numCards) < 17) {
        pullTopCard(&dealerCards[(*numCards)++], cardSet, shuffleStatus);
        displayFullDealerHand(oledStruct, dealerCards, *numCards);
        if(calculateHandValue(dealerCards, *numCards) > 21)
            printlnUART("Dealer busts!");
    }
}

// Function to determine the winner
bool isPlayerWinner(Card* playerCards, int playerNumCards, Card* dealerCards, int dealerNumCards) {
    int playerValue = calculateHandValue(playerCards, playerNumCards);
    int dealerValue = calculateHandValue(dealerCards, dealerNumCards);

    return playerValue <= 21 && (dealerValue > 21 || playerValue > dealerValue);
}

// Function to determine push
bool isPush(Card* playerCards, int playerNumCards, Card* dealerCards, int dealerNumCards) {
    int playerValue = calculateHandValue(playerCards, playerNumCards);
    int dealerValue = calculateHandValue(dealerCards, dealerNumCards);

    return playerValue <= 21 && (dealerValue == playerValue);
}

// Function to offer and handle double down
bool offerAndHandleDoubleDown(PmodOLEDrgb* oledStruct, Card* playerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus, Bet* currentBet, Balance* userBalance) {
    printlnUART("Do you want to Double Down? (A for yes, B for no)");
    char decision = readKeypadInput();
    while(true)
    {
        if (decision == 'A') {
            if (bet(userBalance, currentBet->amount, currentBet)) {
                pullTopCard(&playerCards[(*numCards)++], cardSet, shuffleStatus);
                displayPlayerHand(oledStruct, playerCards, *numCards);
                return true;
            }
            else {
                printlnUART("Insufficient balance to double down.");
                break;
            }
        }
        else if (decision == 'B')
        {
            break;
        }
        decision = readKeypadInput();
    }
    return false;
}

// Function to offer and handle split
int offerAndHandleSplit(PmodOLEDrgb* oledStruct, Card* playerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus, Bet* currentBet, Balance* userBalance, Card* splitCards) {
    if (playerCards[0].value == playerCards[1].value) {
        printlnUART("Do you want to Split? (A for yes, B for no)");
        char decision = readKeypadInput();
        while(true)
        {
            if (decision == 'A') {
                Bet additionalBet = *currentBet;

                if (bet(userBalance, additionalBet.amount, &additionalBet)) {
                    splitCards[0] = playerCards[1];
                    pullTopCard(&playerCards[1], cardSet, shuffleStatus);
                    pullTopCard(&splitCards[1], cardSet, shuffleStatus);
                    int numSplitCards = 2;

                    displayPlayerHand(oledStruct, playerCards, *numCards);
                    playerTurn(oledStruct, playerCards, numCards, cardSet, shuffleStatus);
                    
                    displayPlayerHand(oledStruct, splitCards, numSplitCards);
                    playerTurn(oledStruct, splitCards, &numSplitCards, cardSet, shuffleStatus);

                    return numSplitCards;
                }
                else {
                    printlnUART("Insufficient balance to split.");
                    break;
                }
            }
            else if (decision == 'B')
            {
                break;
            }
            decision = readKeypadInput();
        }
    }
    return 0;
}

// Main gameplay function
void playBlackjack(Balance* userBalance, PmodOLEDrgb* oledStruct) {
    CardSet cardSet; 
    initCardSet(&cardSet, 1, BJ_SHOE_RATIO);
    Card deckTemp[cardSet.cardsLeft];
    cardSet.deck = deckTemp;
    Card discardTemp[cardSet.cardsLeft];
    cardSet.discardPile = discardTemp;
    initCardsInSet(&cardSet);
    ShuffleStatus shuffleStatus;

    while(true)
    {
        Bet currentBet = {0};
        printUART("Enter the amount you'd like to bet");
        int betAmount = getAmtNoTimeout(); /* get bet amount from user */
        if(betAmount == 0)
        {
            break;
        }

        if (!bet(userBalance, betAmount, &currentBet)) {
            continue;
        }

        Card playerCards[MAX_BJ_HAND];
        Card dealerCards[MAX_BJ_HAND];
        pullTopCard(&playerCards[0], &cardSet, &shuffleStatus);
        pullTopCard(&dealerCards[0], &cardSet, &shuffleStatus);
        pullTopCard(&playerCards[1], &cardSet, &shuffleStatus);
        pullTopCard(&dealerCards[1], &cardSet, &shuffleStatus);
        
        int numPlayerCards = 2;
        int numDealerCards = 2;
        
        displayPlayerHand(oledStruct, playerCards, numPlayerCards);
        displayDealerHand(oledStruct, dealerCards, numDealerCards);

        bool playerHasBlackjack = isBlackjack(playerCards);
        bool dealerHasBlackjack = isBlackjack(dealerCards);

        if (playerHasBlackjack && !dealerHasBlackjack) {
            winBet(userBalance, &currentBet, 2.5);
            displayGameResult(oledStruct, "Player wins with Blackjack!");
            printBalance(userBalance);
            return;
        }
        else if (dealerHasBlackjack) {
            displayGameResult(oledStruct, "Dealer wins with Blackjack!");
            printBalance(userBalance);
            return;
        }
        else if (playerHasBlackjack && dealerHasBlackjack) {
            displayGameResult(oledStruct, "Push: Both have Blackjack!");
            printBalance(userBalance);
            return;
        }

        bool doubleDownOccurred = offerAndHandleDoubleDown(oledStruct, playerCards, &numPlayerCards, &cardSet, &shuffleStatus, &currentBet, userBalance);
        unsigned int numSplitCards = 0;
        bool splitOccurred = false;
        Card splitCards[MAX_BJ_HAND];
        if (!doubleDownOccurred) {
            numSplitCards = offerAndHandleSplit(oledStruct, playerCards, &numPlayerCards, &cardSet, &shuffleStatus, &currentBet, userBalance, splitCards);
            splitOccurred = numSplitCards != 0;
        }

        if (!playerHasBlackjack && !doubleDownOccurred && !splitOccurred) {
            playerTurn(oledStruct, playerCards, &numPlayerCards, &cardSet, &shuffleStatus);
        }

        if (calculateHandValue(playerCards, numPlayerCards) <= 21) {
            dealerTurn(oledStruct, dealerCards, &numDealerCards, &cardSet, &shuffleStatus);
        }

        bool playerWins = isPlayerWinner(playerCards, numPlayerCards, dealerCards, numDealerCards);
        if (playerWins) {
            winBet(userBalance, &currentBet, 2);
            displayGameResult(oledStruct, "Player wins with ");
            displayFullHand(oledStruct, playerCards, numPlayerCards);
        }
        else {
            bool push = isPush(playerCards, numPlayerCards, dealerCards, numDealerCards);
            if(push)
            {
                winBet(userBalance, &currentBet, 1);
                displayGameResult(oledStruct, "Player pushes with ");
                displayFullHand(oledStruct, playerCards, numPlayerCards);
            }
            else
            {
                displayGameResult(oledStruct, "Dealer wins against ");
                displayFullHand(oledStruct, playerCards, numPlayerCards);
            }
        }

        if(splitOccurred)
        {
            playerWins = isPlayerWinner(splitCards, numSplitCards, dealerCards, numDealerCards);
            if (playerWins) {
                winBet(userBalance, &currentBet, 2);
                displayGameResult(oledStruct, "Player wins with ");
                displayFullHand(oledStruct, splitCards, numSplitCards);
            }
            else {
                bool push = isPush(playerCards, numPlayerCards, dealerCards, numDealerCards);
                if(push)
                {
                    winBet(userBalance, &currentBet, 1);
                    displayGameResult(oledStruct, "Player pushes with ");
                    displayFullHand(oledStruct, splitCards, numSplitCards);
                }
                else
                {
                    displayGameResult(oledStruct, "Dealer wins against ");
                    displayFullHand(oledStruct, splitCards, numSplitCards);
                }
            }
        }

        printBalance(userBalance);
    }
}
