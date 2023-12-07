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

void printCardVal(char* str, CardValue value) {
    // Adjust the array indices based on the CardValue enum
    if (value >= ACE && value <= KING) {
        if (value > ACE && value < TEN) {
            str[0] = '0' + value;
            str[1] = '\0';  // Null-terminate the string
        } else {
            switch(value)
            {
                case ACE:
                    str[0] = 'A';
                    str[1] = '\0';  // Null-terminate the string
                    break;
                case TEN:
                    str[0] = '1';
                    str[1] = '0';
                    str[2] = '\0';  // Null-terminate the string
                    break;
                case JACK:
                    str[0] = 'J';
                    str[1] = '\0';  // Null-terminate the string
                    break;
                case QUEEN:
                    str[0] = 'Q';
                    str[1] = '\0';  // Null-terminate the string
                    break;
                case KING:
                    str[0] = 'K';
                    str[1] = '\0';  // Null-terminate the string
                    break;
            }
        }
    }
}

