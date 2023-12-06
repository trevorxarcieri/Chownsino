/* ************************************************************************** */
/** 

  @File Name
    card.c

  @Description
    This file holds the functionality for generating random cards in the casino game.
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#include "card.h"

Card generateRandomCard(void) {
    Card randomCard;

    // Generate a random card value
    randomCard.value = (CardValue)generateRandomNumber(1, 14);

    // Generate a random suit
    randomCard.suit = (Suit)generateRandomNumber(0, 4);

    return randomCard;
}
