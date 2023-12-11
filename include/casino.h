/* ************************************************************************** */
/** @File Name
  casino.h

  @Description
    This file groups the declarations of the functions that
    implement the casino module.
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#ifndef CASINO_H
#define CASINO_H

#include "input_wrapper.h"
#include "output_wrapper.h"
#include "balance.h"
#include "randomization.h"
#include "blackjack.h"
#include "roulette.h"
#include "video_poker.h"

void initCasino(PmodOLEDrgb* oledStruct);
void cleanupCasino(PmodOLEDrgb* oledStruct);
int askUserAge(void);
void startCasino();
void viewGames(Balance balance, PmodOLEDrgb oledStruct);

#endif /* CASINO_H */
