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

#include "card.h"

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

CardSet* createCardSet(int numDecks, double shoeRatio);
void destroyCardSet(CardSet* cardSet);
Card pullTopCard(CardSet* cardSet, ShuffleStatus* shuffleStatus);
void discardTopCard(CardSet* cardSet);
void shuffleCardSet(CardSet* cardSet);

#endif /* CARDS_H */