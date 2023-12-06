/* ************************************************************************** */
/** @File Name
  bet.h

  @Description
    This file groups the declarations of the functions and structures that
    implement the bet module (defined in bet.c). 
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#ifndef BET_H
#define BET_H

#include "balance.h"

typedef struct {
    int amount;
} Bet;

int bet(Balance* balance, int betAmount, Bet* outBet);
void winBet(Balance* balance, Bet* bet, int multiplier);

#endif /* BET_H */
