/* ************************************************************************** */
/** @File Name
  input_wrapper.h

  @Description
    This file groups the declarations of the functions that
    implement the wrapper input module.
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#ifndef INPUT_WRAPPER_H
#define INPUT_WRAPPER_H

#include "adc.h"
#include "acl.h"
#include "general_IO.h"
#include "keypad1.h"

void initInput(void);
unsigned char readButtonsInput(void);
unsigned char readSwitchesInput(void);
unsigned char readKeypadInput(void);

#endif /* INPUT_WRAPPER_H */
