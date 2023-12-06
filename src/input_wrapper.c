/* ************************************************************************** */
/** @File Name
  input_wrapper.c

  @Description
    This file holds the functionality for the wrapper input module,
    providing a general initialization function and read input functions
    for buttons, switches, and the keypad.
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#include "input_wrapper.h"

void initInput(void) {
    ADC_Init();
    ACL_Init_Default();
    initButtons();
    initSwitches();
    initKeypad();
}

unsigned char readButtonsInput(void) {
    return readButtons();
}

unsigned char readSwitchesInput(void) {
    return readSwitches();
}

unsigned char readKeypadInput(void) {
    return readKey();
}
