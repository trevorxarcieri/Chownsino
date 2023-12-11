#include "videopoker.h"

#define MAX_HAND 5

// Function Prototypes
void dealInitialHand(Card* hand, CardSet* cardSet);
void getHeldCards(bool* cardsToHold);
void replaceDiscardedCards(Card* hand, CardSet* cardSet, bool* cardsToHold);
void sortHandByValue(Card* hand);
bool isPair(Card* hand);
bool isTwoPair(Card* hand);
bool isThreeOfAKind(Card* hand);
bool isStraight(Card* hand);
bool isFlush(Card* hand);
bool isFullHouse(Card* hand);
bool isFourOfAKind(Card* hand);
bool isStraightFlush(Card* hand);
bool isRoyalFlush(Card* hand);
void displayHand(Card* hand);
void displayBalance(Balance balance);
void payoutWinnings(Balance* balance, Card* hand);
void playVideoPoker(Balance* userBalance, CardSet* cardSet);
void readStringUART(char* str, int maxLength);

// Main Video Poker Function
void playVideoPoker(Balance* userBalance, PmodOLEDrgb* oledStruct) {
    // Ensure balance is sufficient for minimum bet
    if (userBalance->balance < MIN_BET) {
        printlnUART("Insufficient balance for betting.");
        return;
    }

    // Player places a bet
    int betAmount = getBetAmount(userBalance);
    if (betAmount <= 0) return; // Exit if no bet is placed or invalid bet

    Card hand[MAX_HAND];
    bool cardsToHold[MAX_HAND] = { false };

    // Deal initial hand
    dealInitialHand(hand, &cardSet);
    displayFullHand(oledStruct, hand, MAX_HAND);

    // Player selects cards to hold
    getHeldCards(cardsToHold);
    replaceDiscardedCards(hand, &cardSet, cardsToHold);
    displayFullHand(oledStruct, hand, MAX_HAND);

    // Final hand evaluation and payout
    payoutWinnings(userBalance, hand, betAmount);
    displayBalance(*userBalance);

    // Ask if the player wants to play another round
    askPlayAgain();
}

// Implementations
int getBetAmount(Balance* userBalance) {
    printUART("Enter bet amount: ");
    int betAmount = readBetAmount(); // Implement this to read the bet amount
    return (betAmount <= userBalance->balance && betAmount >= MIN_BET) ? betAmount : 0;
}

void askPlayAgain() {
    printUART("Play again? (Y/N): ");
    char decision = readKeypadInput(); // Use your input method
    if (decision == 'Y' || decision == 'y') {
        playVideoPoker(userBalance, oledStruct); // Recursive call to play again
    }
}

void dealInitialHand(Card* hand, CardSet* cardSet) {
    for (int i = 0; i < MAX_HAND; i++) {
        pullTopCard(&hand[i], cardSet, &shuffleStatus); // Use your Blackjack function
    }
}

void getHeldCards(bool* cardsToHold) {
    printlnUART("Choose cards to hold (e.g., '135' for cards 1, 3, 5):");
    char input[6];
    readStringUART(input, sizeof(input));

    for (int i = 0; i < MAX_HAND; i++) {
        cardsToHold[i] = strchr(input, '1' + i) != NULL;
    }
}

void replaceDiscardedCards(Card* hand, CardSet* cardSet, bool* cardsToHold) {
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

// Function to display a card's value and suit
void printCard(Card card) {
    char cardStr[20]; 
    sprintf(cardStr, "%s of %s", valueToString(card.value), suitToString(card.suit));
    printUART(cardStr); // Replace with your project's function to print to your output
}

void displayFullHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards) {
    printUART("Hand: ");
    for (int i = 0; i < numCards; i++) {
        displayCard(oledStruct, cards[i], 0);
        if (i < numCards - 1) {
            printUART(", ");
        }
    }
    printlnUART("");
}

void displayBalance(Balance balance) {
    char balanceStr[20];
    sprintf(balanceStr, "Balance: %d", balance.balance);
    printlnUART(balanceStr);
}

void payoutWinnings(Balance* balance, Card* hand) {
    int multiplier = 0;

    if (isRoyalFlush(hand)) multiplier = 800;
    // ... other hand checks ...
    else if (isPair(hand)) multiplier = 1;

    int winnings = currentBet * multiplier; // currentBet should be set in your gameplay
    addToBalance(balance, winnings);
}

void readStringUART(char* str, int maxLength) {
    int count = 0;
    char ch;
    while ((ch = UART_getChar()) != '\n' && ch != '\r' && count < maxLength - 1) {
        str[count++] = ch;
    }
    str[count] = '\0'; // Null-terminate the string
}
