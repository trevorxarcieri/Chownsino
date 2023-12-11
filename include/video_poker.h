/* ************************************************************************** */
/** @File Name
    videopoker.h

  @Description
    This file groups the declarations of the functions and structures that
    implement the video poker module.

  @Author
    Trevor Arcieri and Nicholas Chown

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
#define VP_SHOE_RATIO 0.6

#define ROYAL_FLUSH_MULT 250
#define STRAIGHT_FLUSH_MULT 50
#define FOUR_KIND_MULT 25
#define FULL_HOUSE_MULT 9
#define FLUSH_MULT 6
#define STRAIGHT_MULT 4
#define THREE_KIND_MULT 3
#define TWO_PAIR_MULT 2
#define PAIR_MULT 1

void playVideoPoker(Balance* userBalance, PmodOLEDrgb* oledStruct);

void dealInitialHand(Card* hand, CardSet* cardSet, ShuffleStatus ShuffleStatus);
void getHeldCards(bool* cardsToHold);
void replaceDiscardedCards(Card* hand, CardSet* cardSet, bool* cardsToHold, ShuffleStatus ShuffleStatus);
void sortHandByValue(Card* hand);
void payoutWinnings(Balance* balance, Card* hand, Bet* bet);

bool isPair(Card* hand);
bool isTwoPair(Card* hand);
bool isThreeOfAKind(Card* hand);
bool isStraight(Card* hand);
bool isFlush(Card* hand);
bool isFullHouse(Card* hand);
bool isFourOfAKind(Card* hand);
bool isStraightFlush(Card* hand);
bool isRoyalFlush(Card* hand);

#endif
