#include "video_poker.h"

void playVideoPoker(Balance* balance) {
    Card hand[MAX_HAND];
    CardDeck deck;

    initDeck(&deck); // Initialize and shuffle the deck
    dealInitialHand(hand, &deck); // Deal the initial hand
    displayHand(hand); // Display the initial hand

    playerChoices(hand, &deck); // Allow player to choose cards to hold
    displayHand(hand); // Display the final hand

    HandRanking ranking = evaluateHand(hand); // Evaluate the final hand
    payoutWinnings(balance, ranking); // Payout based on the hand ranking
}

void dealInitialHand(Card* hand, CardDeck* deck) {
    for (int i = 0; i < MAX_HAND; i++) {
        hand[i] = drawCard(deck); // Draw a card from the deck
    }
}

void playerChoices(Card* hand, CardDeck* deck) {
        printlnUART("Choose cards to hold (e.g., '135' to hold cards 1, 3, and 5):");
        char choices[6]; // Buffer for player choices
        readString(choices, sizeof(choices)); // Read player choices

    for (int i = 0; i < MAX_HAND; i++) {
        if (strchr(choices, '1' + i) == NULL) {
            hand[i] = drawCard(deck); // Replace unheld cards
        }
    }
}

HandRanking evaluateHand(Card* hand) {
    sortHand(hand); // Sort the hand for evaluation
    // Check for each type of poker hand
    if (isRoyalFlush(hand)) return ROYAL_FLUSH;
    if (isStraightFlush(hand)) return STRAIGHT_FLUSH;
    if (isFourOfAKind(hand)) return FOUR_OF_A_KIND;
    if (isFullHouse(hand)) return FULL_HOUSE;
    if (isFlush(hand)) return FLUSH;
    if (isStraight(hand)) return STRAIGHT;
    if (isThreeOfAKind(hand)) return THREE_OF_A_KIND;
    if (isTwoPair(hand)) return TWO_PAIR;
    if (isOnePair(hand)) return ONE_PAIR;
    return HIGH_CARD; // If no other hand, it's a high card
}

void payoutWinnings(Balance* balance, HandRanking handRanking) {
    int payoutMultiplier = 0;
    switch (handRanking) {
    case ROYAL_FLUSH: payoutMultiplier = 800; break;
    case STRAIGHT_FLUSH: payoutMultiplier = 50; break;
    case FOUR_OF_A_KIND: payoutMultiplier = 25; break;
    case FULL_HOUSE: payoutMultiplier = 9; break;
    case FLUSH: payoutMultiplier = 6; break;
    case STRAIGHT: payoutMultiplier = 4; break;
    case THREE_OF_A_KIND: payoutMultiplier = 3; break;
    case TWO_PAIR: payoutMultiplier = 2; break;
    case ONE_PAIR: payoutMultiplier = 1; break;
    default: payoutMultiplier = 0; break; // No payout for high card
    }
    int winnings = /* bet amount */ *payoutMultiplier; // Replace with the actual bet amount
    addToBalance(balance, winnings);
}

void displayHand(Card* hand) {
    for (int i = 0; i < MAX_HAND; i++) {
        char cardStr[MAX_CARD_STRING_LENGTH];
        cardToString(&hand[i], cardStr); // Convert card to string
        printlnUART(cardStr); // Display the card
    }
}

void readString(char* str, int maxLength) {
    void readString(char* str, int maxLength) {
        int count = 0;
        char ch;

        while (true) {
            ch = UART_getChar(); // Get a character from UART

            // Check for newline or carriage return (end of input)
            if (ch == '\n' || ch == '\r') {
                break;
            }

            // Store the character if there's space in the buffer
            if (count < maxLength - 1) {
                str[count++] = ch;
            }
        }

        str[count] = '\0'; // Null-terminate the string
    }
}

void sortHand(Card* hand) {
    // Simple Bubble Sort implementation to sort the cards
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

bool isRoyalFlush(Card* hand) {
    // Check if the hand is a royal flush
    return isStraightFlush(hand) && hand[0].value == ACE && hand[4].value == KING;
}

bool isStraightFlush(Card* hand) {
    // Check if the hand is a straight flush
    return isStraight(hand) && isFlush(hand);
}

bool isFourOfAKind(Card* hand) {
    // Check if the hand has four cards of the same value
    return (hand[0].value == hand[3].value) || (hand[1].value == hand[4].value);
}

bool isFullHouse(Card* hand) {
    // Check if the hand is a full house
    bool threeFirstTwoLast = (hand[0].value == hand[2].value) && (hand[3].value == hand[4].value);
    bool twoFirstThreeLast = (hand[0].value == hand[1].value) && (hand[2].value == hand[4].value);
    return threeFirstTwoLast || twoFirstThreeLast;
}

bool isFlush(Card* hand) {
    // Check if all cards have the same suit
    Suit firstSuit = hand[0].suit;
    for (int i = 1; i < MAX_HAND; i++) {
        if (hand[i].suit != firstSuit) {
            return false;
        }
    }
    return true;
}

bool isStraight(Card* hand) {
    // Check if the hand contains five consecutive cards
    for (int i = 0; i < MAX_HAND - 1; i++) {
        if (hand[i].value + 1 != hand[i + 1].value) {
            return false;
        }
    }
    return true;
}

bool isThreeOfAKind(Card* hand) {
    // Check if the hand has three cards of the same value
    for (int i = 0; i < 3; i++) {
        if (hand[i].value == hand[i + 1].value && hand[i].value == hand[i + 2].value) {
            return true;
        }
    }
    return false;
}

bool isTwoPair(Card* hand) {
    // Check if the hand has two pairs
    int pairCount = 0;
    for (int i = 0; i < MAX_HAND - 1; i++) {
        if (hand[i].value == hand[i + 1].value) {
            pairCount++;
            i++;
        }
    }
    return pairCount == 2;
}

bool isOnePair(Card* hand) {
    // Check if the hand has a single pair
    for (int i = 0; i < MAX_HAND - 1; i++) {
        if (hand[i].value == hand[i + 1].value) {
            return true;
        }
    }
    return false;
}

void cardToString(const Card* card, char* cardStr) {
    char* values[] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
    char* suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    sprintf(cardStr, "%s of %s", values[card->value - 1], suits[card->suit]);
}
