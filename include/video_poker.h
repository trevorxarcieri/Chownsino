#ifndef VIDEO_POKER_H
#define VIDEO_POKER_H

#include "balance.h"
#include "card.h"
#include "randomization.h"
#include "input_wrapper.h"
#include "output_wrapper.h"

#define MAX_HAND 5
#define MAX_CARD_STRING_LENGTH 20

typedef enum {
    HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH,
    FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH
} HandRanking;

void playVideoPoker(Balance* balance);
void dealInitialHand(Card* hand, CardDeck* deck);
void playerChoices(Card* hand, CardDeck* deck);
HandRanking evaluateHand(Card* hand);
void payoutWinnings(Balance* balance, HandRanking handRanking);
void displayHand(Card* hand);
void readString(char* str, int maxLength);
void sortHand(Card* hand);
bool isRoyalFlush(Card* hand);
bool isStraightFlush(Card* hand);
bool isFourOfAKind(Card* hand);
bool isFullHouse(Card* hand);
bool isFlush(Card* hand);
bool isStraight(Card* hand);
bool isThreeOfAKind(Card* hand);
bool isTwoPair(Card* hand);
bool isOnePair(Card* hand);
void cardToString(const Card* card, char* cardStr);

#endif // VIDEO_POKER_H
