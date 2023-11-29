/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Kettering University

  @File Name
    SWsLEDs.h

  @Summary
    Defines the I/O pins and function prototypes for the switches and LEDs interfacing

  @Description
    This header file defines the I/O pins used by the switches and LEDs interfacing
    circuit, and provides the function prototypes.
  @Author
    Girma Tewolde and Trevor Arcieri
 
 */
/* ************************************************************************** */

#ifndef _SWsLEDs__H    /* Guard against multiple inclusion */
#define _SWsLEDs__H

#define CPU_FREQ    80000000
#define ONE_SEC_TICKS (CPU_FREQ/2)
    
//Buttons BTNL and BTNU share functions with PGD and PGC signals for programming
//the following line should be inserted in the code, to disable their programming function

//port configuration values for input & output    
#define IN      1       
#define OUT     0
    
//definition of pins for pushbuttons
#define BTNU      PORTBbits.RB1
#define BTNL      PORTBbits.RB0
#define BTNC      PORTFbits.RF0
#define BTNR      PORTBbits.RB8
#define BTND      PORTAbits.RA15

#define BTNU_dir  TRISBbits.TRISB1
#define BTNL_dir  TRISBbits.TRISB0
#define BTNC_dir  TRISFbits.TRISF0
#define BTNR_dir  TRISBbits.TRISB8
#define BTND_dir  TRISAbits.TRISA15

//definition of pins for switches    
#define SW0       PORTFbits.RF3
#define SW1       PORTFbits.RF5
#define SW2       PORTFbits.RF4
#define SW3       PORTDbits.RD15
#define SW4       PORTDbits.RD14
#define SW5       PORTBbits.RB11
#define SW6       PORTBbits.RB10
#define SW7       PORTBbits.RB9

#define SW0_dir   TRISFbits.TRISF3
#define SW1_dir   TRISFbits.TRISF5
#define SW2_dir   TRISFbits.TRISF4
#define SW3_dir   TRISDbits.TRISD15
#define SW4_dir   TRISDbits.TRISD14
#define SW5_dir   TRISBbits.TRISB11
#define SW6_dir   TRISBbits.TRISB10
#define SW7_dir   TRISBbits.TRISB9    

//definition of pins for LEDs -- attached to PORTA pins 0 through 7
#define LED0      LATAbits.LATA0
#define LED1      LATAbits.LATA1
#define LED2      LATAbits.LATA2
#define LED3      LATAbits.LATA3
#define LED4      LATAbits.LATA4
#define LED5      LATAbits.LATA5
#define LED6      LATAbits.LATA6
#define LED7      LATAbits.LATA7
    
#define LED0_dir  TRISAbits.TRISA0
#define LED1_dir  TRISAbits.TRISA1
#define LED2_dir  TRISAbits.TRISA2
#define LED3_dir  TRISAbits.TRISA3
#define LED4_dir  TRISAbits.TRISA4
#define LED5_dir  TRISAbits.TRISA5
#define LED6_dir  TRISAbits.TRISA6
#define LED7_dir  TRISAbits.TRISA7
    
//function prototypes
void initButtons(void);
unsigned char readButtons(void);
void initSwitches(void);
unsigned char readSwitches(void);
void initAllLEDs(void);
void writeAllLEDs(unsigned char);
void writeLED(unsigned char index, unsigned char val);

//time delay functions    
void msDelay(unsigned int ms);

#endif /* _SWsLEDs__H */

/* *****************************************************************************
 End of File
 */
