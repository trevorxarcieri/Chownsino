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

void initCasino(PmodOLEDrgb* oledStruct);
void cleanupCasino(PmodOLEDrgb* oledStruct);
int askUserAge(void);
void startCasino();

#endif /* CASINO_H */
