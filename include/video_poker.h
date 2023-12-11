/* ************************************************************************** */
/** @File Name
    videopoker.h

  @Description
    This file groups the declarations of the functions and structures that
    implement the video poker module.

  @Author
    Your Name

 */
 /* ************************************************************************** */

#ifndef VIDEOPOKER_H
#define VIDEOPOKER_H

#include <stdbool.h>
#include "balance.h"
#include "bet.h"
#include "card.h"
#include "cards.h"
#include "input_wrapper.h"
#include "output_wrapper.h"
#include "randomization.h"

#define MAX_HAND 5

void playVideoPoker(Balance* userBalance, PmodOLEDrgb* oledStruct);

void dealInitialHand(Card* hand, CardSet* cardSet);
void getHeldCards(bool* cardsToHold);
void replaceDiscardedCards(Card* hand, CardSet* cardSet, bool* cardsToHold);
void sortHandByValue(Card* hand);
int getBetAmount(Balance* userBalance);
void askPlayAgain();
void payoutWinnings(Balance* balance, Card* hand, int betAmount);

bool isPair(Card* hand);
bool isTwoPair(Card* hand);
bool isThreeOfAKind(Card* hand);
bool isStraight(Card* hand);
bool isFlush(Card* hand);
bool isFullHouse(Card* hand);
bool isFourOfAKind(Card* hand);
bool isStraightFlush(Card* hand);
bool isRoyalFlush(Card* hand);

void displayFullHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards);
void payoutWinnings(Balance* balance, Card* hand);


#endif
