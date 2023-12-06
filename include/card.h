/* ************************************************************************** */
/** 

  @File Name
    card.h

  @Description
    This file groups the declarations of the functions and structures that 
    implement the card module (defined in card.c). 
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#ifndef CARD_H
#define CARD_H

typedef enum {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
} Suit;

typedef enum {
    ACE = 1,
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING
} CardValue;

typedef struct {
    CardValue value;
    Suit suit;
} Card;

Card generateRandomCard(void);

#endif /* CARD_H */
