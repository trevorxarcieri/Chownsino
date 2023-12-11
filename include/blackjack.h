/* ************************************************************************** */
/** @File Name
  blackjack.h

  @Description
    This file groups the declarations of the functions and structures that
    implement the blackjack module (defined in blackjack.c). 
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdbool.h>
#include "balance.h"
#include "bet.h"
#include "card.h"
#include "cards.h"
#include "input_wrapper.h"
#include "output_wrapper.h"
#include "randomization.h"

#define BJ_SHOE_RATIO 0.6

#define MAX_BJ_HAND 5

void playBlackjack(Balance* userBalance, PmodOLEDrgb* oledStruct);

void displayPlayerHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards);
void displayFullDealerHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards);
void displayDealerHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards);
void displayGameResult(PmodOLEDrgb* oledStruct, const char* result);

int calculateHandValue(Card* hand, int numCards);
bool isBlackjack(Card* hand);

void playerTurn(PmodOLEDrgb* oledStruct, Card* playerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus);
void dealerTurn(PmodOLEDrgb* oledStruct, Card* dealerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus);

bool isPlayerWinner(Card* playerCards, int playerNumCards, Card* dealerCards, int dealerNumCards);

bool offerAndHandleDoubleDown(PmodOLEDrgb* oledStruct, Card* playerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus, Bet* currentBet, Balance* userBalance);
int offerAndHandleSplit(PmodOLEDrgb* oledStruct, Card* playerCards, int* numCards, CardSet* cardSet, ShuffleStatus* shuffleStatus, Bet* currentBet, Balance* userBalance, Card* splitCards);

#endif
