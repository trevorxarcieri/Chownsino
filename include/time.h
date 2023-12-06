/* ************************************************************************** */
/**
  @File Name
    time.h

  @Summary
    Defines the I/O pins and function prototypes for the keypad interfacing

  @Description
    This file groups the declarations of the functions that implement timing
    utilities used throughout the program.
    The file is included wherever timing utilities are necessary.

  @Author
    Girma Tewolde and Trevor Arcieri
 */
/* ************************************************************************** */

#ifndef _TIME_H    /* Guard against multiple inclusion */
#define _TIME_H

#include <xc.h>

#define PB_FREQ  40000000
#define ONE_SEC_TICKS PB_FREQ
#define ONE_MS_TICKS (ONE_SEC_TICKS/1000)

unsigned int getTicks(void);

unsigned int getMsSince(unsigned int start);

unsigned int getMsDiff(unsigned int start, unsigned int end);

//prototype for millisecond resolution time delay function (based on core timer)
void msDelay(unsigned int);

//utility function for small time delay
void DelayAprox10Us( unsigned int tusDelay );

#endif