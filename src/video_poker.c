#include "video_poker.h"

// Main Video Poker Function
void playVideoPoker(Balance* userBalance, PmodOLEDrgb* oledStruct) {
    CardSet cardSet; 
    initCardSet(&cardSet, 1, VP_SHOE_RATIO);
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

        Card hand[MAX_HAND];
        bool cardsToHold[MAX_HAND] = { false };

        // Deal initial hand
        dealInitialHand(hand, &cardSet, shuffleStatus);
        displayFullHand(oledStruct, hand, MAX_HAND);

        // Player selects cards to hold
        getHeldCards(cardsToHold);
        replaceDiscardedCards(hand, &cardSet, cardsToHold, shuffleStatus);
        displayFullHand(oledStruct, hand, MAX_HAND);

        // Final hand evaluation and payout
        payoutWinnings(userBalance, hand, &currentBet);
        printBalance(userBalance);
    }
}

void dealInitialHand(Card* hand, CardSet* cardSet, ShuffleStatus shuffleStatus) {
    for (int i = 0; i < MAX_HAND; i++) {
        pullTopCard(&hand[i], cardSet, &shuffleStatus); // Use Blackjack function
    }
}

void getHeldCards(bool* cardsToHold) {
    printlnUART("Choose cards to hold (1-5, press any other key to stop):");
    while(true)
    {
        char key = readKeypadInput();
        if(key == 0)
            continue;
        int i = key - '0';
        if (i <= MAX_HAND && i > 0)
        {
            cardsToHold[i - 1] = !cardsToHold[i - 1];
            if(cardsToHold[i - 1])
            {
                printUART("Now holding card ");
            }
            else
            {
                printUART("Now unholding card ");
            }
            UART4_putchar(key);
            printlnUART("");
        }
        else 
        {
            break;
        }
    }
}

void replaceDiscardedCards(Card* hand, CardSet* cardSet, bool* cardsToHold, ShuffleStatus shuffleStatus) {
    for (int i = 0; i < MAX_HAND; i++) {
        if (!cardsToHold[i]) {
            pullTopCard(&hand[i], cardSet, &shuffleStatus);
        }
    }
}

// Helper function to sort the hand by card values
void sortHandByValue(Card* hand) {
    for (int i = 0; i < MAX_HAND - 1; i++) {
        for (int j = 0; j < MAX_HAND - i - 1; j++) {
            if (hand[j].value > hand[j + 1].value) {
                Card temp = hand[j];
                hand[j] = hand[j + 1];
                hand[j + 1] = temp;
            }
        }
    }
}

bool isPair(Card* hand) {
    sortHandByValue(hand);
    for (int i = 0; i < MAX_HAND - 1; i++) {
        if (hand[i].value == hand[i + 1].value) return true;
    }
    return false;
}

bool isTwoPair(Card* hand) {
    sortHandByValue(hand);
    int pairs = 0;
    for (int i = 0; i < MAX_HAND - 1; i++) {
        if (hand[i].value == hand[i + 1].value) {
            pairs++;
            i++;
        }
    }
    return pairs == 2;
}

bool isThreeOfAKind(Card* hand) {
    sortHandByValue(hand);
    for (int i = 0; i < MAX_HAND - 2; i++) {
        if (hand[i].value == hand[i + 1].value && hand[i].value == hand[i + 2].value) return true;
    }
    return false;
}

bool isStraight(Card* hand) {
    sortHandByValue(hand);
    for (int i = 0; i < MAX_HAND - 1; i++) {
        if (hand[i].value + 1 != hand[i + 1].value) return false;
    }
    return true;
}

bool isFlush(Card* hand) {
    Suit firstSuit = hand[0].suit;
    for (int i = 1; i < MAX_HAND; i++) {
        if (hand[i].suit != firstSuit) return false;
    }
    return true;
}

bool isFullHouse(Card* hand) {
    sortHandByValue(hand);
    bool threeFirstTwoLast = (hand[0].value == hand[2].value) && (hand[3].value == hand[4].value);
    bool twoFirstThreeLast = (hand[0].value == hand[1].value) && (hand[2].value == hand[4].value);
    return threeFirstTwoLast || twoFirstThreeLast;
}

bool isFourOfAKind(Card* hand) {
    sortHandByValue(hand);
    return (hand[0].value == hand[3].value) || (hand[1].value == hand[4].value);
}

bool isStraightFlush(Card* hand) {
    return isStraight(hand) && isFlush(hand);
}

bool isRoyalFlush(Card* hand) {
    return isStraightFlush(hand) && hand[0].value == TEN && hand[4].value == ACE;
}

void payoutWinnings(Balance* balance, Card* hand, Bet* bet) {
    int multiplier = 0;

    if (isRoyalFlush(hand))
    {
        multiplier = ROYAL_FLUSH_MULT;
        printlnUART("Royal flush!");
    }
    else if (isStraightFlush(hand))
    {
        multiplier = STRAIGHT_FLUSH_MULT;
        printlnUART("Straight flush!");
    }
    else if (isFourOfAKind(hand))
    {
        multiplier = FOUR_KIND_MULT;
        printlnUART("Four of a kind!");
    }
    else if (isFullHouse(hand))
    {
        multiplier = FULL_HOUSE_MULT;
        printlnUART("Full house!");
    }
    else if (isFlush(hand))
    {
        multiplier = FLUSH_MULT;
        printlnUART("Flush!");
    }
    else if (isStraight(hand))
    {
        multiplier = STRAIGHT_MULT;
        printlnUART("Straight!");
    }
    else if (isThreeOfAKind(hand))
    {
        multiplier = THREE_KIND_MULT;
        printlnUART("Three of a kind!");
    }
    else if (isTwoPair(hand))
    {
        multiplier = TWO_PAIR_MULT;
        printlnUART("Two pair!");
    }
    else if (isPair(hand))
    {
        multiplier = PAIR_MULT;
        printlnUART("Pair!");
    }
    else
    {
        printlnUART("No winning arrangement.");
    }

    winBet(balance, bet, multiplier);
}
