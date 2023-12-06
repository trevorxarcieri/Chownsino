/* ************************************************************************** */
/** 

  @File Name
    time.c

  @Description
    This file holds the timing utilities used throughout the program.
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#include "time.h"

unsigned int getTicks()
{
  return _CP0_GET_COUNT();
}

unsigned int getMsSince(unsigned int start)
{
  return getMsDiff(start, _CPO_GET_COUNT());
}

//Count ms between start and end ticks, modulo 107,374ms
unsigned int getMsDiff(unsigned int start, unsigned int end)
{
  return (end - start) / ONE_MS_TICKS;
}


//Perform msDelay without resetting core timer
void msDelay(unsigned int ms) 
                              
{
    // Convert ms into how many clock ticks it will take
    unsigned int ticks = ms * (ONE_SEC_TICKS/1000);

    ticks += _CP0_GET_COUNT(); //Set desired tick count by adding desired
                                //ticks to current core timer count

    while (ticks > _CP0_GET_COUNT()); //Wait until core timer reaches the
                                      //desired count
}

/* ------------------------------------------------------------ */
/***    Delay100Us
**
**	Synopsis:
**		Delay100Us(100)
**
**	Parameters:
**		t100usDelay - the amount of time you wish to delay in hundreds of microseconds
**
**	Return Values:
**      none
**
**	Errors:
**		none
**
**	Description:
**		This procedure delays program execution for the specified number
**      of microseconds. This delay is not precise.
**		
**	Note:
**		This routine is written with the assumption that the
**		system clock is 40 MHz.
*/
void DelayAprox10Us( unsigned int  t100usDelay )
{
    int j;
    while ( 0 < t100usDelay )
    {
        t100usDelay--;
        j = 14;
        while ( 0 < j )
        {
            j--;
        }   // end while 
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
         
    }   // end while
}
