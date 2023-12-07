/* ************************************************************************** */
/** @File Name
  cards.h

  @Description
    This file groups the declarations of the functions and structures that
    implement the cards module (defined in cards.c). 
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#ifndef CARDS_H
#define CARDS_H

#include <stdlib.h>
#include "card.h"
#include "randomization.h"

typedef struct {
    int numDecks;
    double shoeRatio;
    int cardsLeft;
    Card* deck;
    Card* discardPile;
} CardSet;

typedef enum {
    NO_SHUFFLE,
    SHUFFLING
} ShuffleStatus;

void initCardSet(CardSet* cardSet, int numDecks, double shoeRatio);
Card pullTopCard(CardSet* cardSet, ShuffleStatus* shuffleStatus);
void discardTopCard(CardSet* cardSet);
void shuffleCardSet(CardSet* cardSet);

#endif /* CARDS_H */
