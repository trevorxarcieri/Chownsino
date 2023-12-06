/* ************************************************************************** */
/** 
  @Company
    Kettering University

  @File Name
    uart.c

  @Summary
    Implements the functions that support the UART serial output communication

  @Description
     
  @Author
    Girma Tewolde and Trevor Arcieri
 */
/* ************************************************************************** */

#include <xc.h>
#include "uart.h"

void initUART4(void)
{
    // The next two statements map the PPS IO pins to the UART 4 Tx and Rx
    RPF12R = 0x02; // Mapping U4TX to RPF12;
    U4RXR = 0x09; // Mapping U4RX to RPF13    
    U4BRG = BRATE; //initialize the baud rate generator
    U4MODE = U_ENABLE; //initialize the UART module
    U4STA = U_TXRX; //enable TX & RX
}

void UART4_putchar(uint8_t c) { //send a character to UART1
    while (U4STAbits.UTXBF == 1); //wait until transmitter buffer becomes empty
    U4TXREG = c;    //write character to TX data register
}
void UART4_putstr(uint8_t s[]) { //send a null-terminated string to UART1
    while (s[0] != 0) {
        UART4_putchar(s[0]);
        s++;
    }
}

/* *****************************************************************************
 End of File
 */
