/* ************************************************************************** */
/**

  @Company
    Kettering University

  @File Name
    keypad1.h

  @Summary
    Defines the I/O pins and function prototypes for the keypad interfacing on PMODA.

  @Description
    The I/O pins used for interfacing to the keypad and the function prototypes
    are defined in this header file.

  @Author
    Girma Tewolde and Trevor Arcieri
 */
/* ************************************************************************** */

#ifndef _KEYPAD_H    /* Guard against multiple inclusion */
#define _KEYPAD_H

#include <xc.h>
#include "general_IO.h"
#include "time.h"

//define pins used for interfacing the keypad
#define col1_dir      TRISGbits.TRISG6
#define col1          LATGbits.LATG6
#define col2_dir      TRISCbits.TRISC4
#define col2          LATCbits.LATC4
#define col3_dir      TRISCbits.TRISC1
#define col3          LATCbits.LATC1
#define col4_dir      TRISCbits.TRISC2
#define col4          LATCbits.LATC2
    
#define row1_dir      TRISGbits.TRISG9
#define row1          PORTGbits.RG9
#define row2_dir      TRISGbits.TRISG8
#define row2          PORTGbits.RG8
#define row3_dir      TRISGbits.TRISG7
#define row3          PORTGbits.RG7
#define row4_dir      TRISCbits.TRISC3
#define row4          PORTCbits.RC3

//keypad interfacing function prototypes    
void initKeypad(void);
unsigned char readKey(void);
    
#endif /* _KEYPAD_H */

/* *****************************************************************************
 End of File
 */
