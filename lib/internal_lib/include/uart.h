/* ************************************************************************** */
/** 
  @Company
    Kettering University

  @File Name
    uart.h

  @Summary
    Defines the parameters used to configure the UART for serial output function

  @Description
    This header file defines the serial communication protocol parameters
    for the PIC32 UART port, and provides the prototypes for the serial
    output functions.
 
  @Author
    Girma Tewolde and Trevor Arcieri
 */
/* ************************************************************************** */

#ifndef _UART_H    /* Guard against multiple inclusion */
#define _UART_H

#include <xc.h>

//define UART configuration constants
#define BRATE 1041 //U4BREG setting for ~9600 baud
#define U_ENABLE 0x8008 //enable UART, BREGH=1, 1 stop, no parity
#define U_TXRX 0x1400 //enable RX and TX, clear all flags

//UART4 interfacing function prototypes    
void initUART4(void);
void UART4_putchar(uint8_t c);
void UART4_putstr(uint8_t *s);

#endif /* _UART_H */

/* *****************************************************************************
 End of File
 */
