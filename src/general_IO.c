/* ************************************************************************** */
/** 
  @Company
    Kettering University

  @File Name
    general_IO.c

  @Summary
    Implements the functions necessary for the basic I/O control operations of switches,
    buttons, and LEDs

  @Description
    
  @Author
    Girma Tewolde
  @Last modification
    09/09/2020 @ 6:24 PM
 */
/* ************************************************************************** */

#include "general_IO.h"
#include "time.h"

//initialize all switches as inputs
//switches (SW0..SW7)are attached to the PIC32 GPIO pins 
//... RF3, RF5, RF4, RD15, RD14, RB11, RB10, RB9, respectively
void initSwitches(void) {
    TRISFSET = 0x0038; //configure pins 3, 4, and 5 of PORTF as inputs
    TRISDSET = 0xC000;  //configure pins 14 and 15 of PORTD as inputs
    ANSELBCLR = 0x0E00; //configure pins 9, 10, and 11 of PORTB as digital 
    TRISBSET = 0x0E00;  //configure pins 9, 10, and 11 of PORTB as inputs
/* here is alternative way of configuring the above pins as inputs   
    SW0_dir = IN;       
    SW1_dir = IN;
    SW2_dir = IN;
    SW3_dir = IN;
    SW4_dir = IN;
    ANSELBbits.ANSB11 = 0; // RB11 (SW5) disabled analog
    SW5_dir = IN;
    ANSELBbits.ANSB10 = 0; // RB10 (SW) disabled analog
    SW6_dir = IN;
    ANSELBbits.ANSB9 = 0; // RB9 (SW7) disabled analog
    SW7_dir = IN;
*/ 
}


unsigned char readSwitches(void) {
    unsigned char inputState = 0;
    
    //create a bit pattern based on the status of the button inputs
    inputState = (SW7 << 7) | (SW6 << 6) | (SW5 << 5) | (SW4 << 4) | 
            (SW3 << 3) | (SW2 << 2) | (SW1 << 1) | SW0;
    
    return inputState;
}

//initialize the pushbutton switches (configure port direction)
void initButtons(void) {
    //configure the button pins as inputs
    ANSELBbits.ANSB1 = 0; // RB1 (BTNU) disabled analog
    BTNU_dir = IN;
    CNPDBbits.CNPDB1 = 1;

    ANSELBbits.ANSB0 = 0; // RB0 (BTNL) disabled analog
    BTNL_dir = IN; 
    CNPDBbits.CNPDB0 = 1;

    BTNC_dir = IN;

    ANSELBbits.ANSB8 = 0; // RB8 (BTNR) disabled analog
    BTNR_dir = IN;
    CNPDBbits.CNPDB8 = 1;

    BTND_dir = IN;
}

//read the button states
//a logic value of 1 indicates a button is pressed, 0 indicates it is released
//concatenate the button states into a 5-bit binary number (right justified)
//inputState = {0,0,0,BTNU, BTNL, BTNC, BTNR, BTND}
//The buttons have mechanical bouncing issues which is not handled in this function
//the user can use software debouncing technique in their code 
unsigned char readButtons(void) {
    unsigned char inputState = 0;
    
    //create a bit pattern based on the status of the button inputs
    inputState = (BTNU << 4) | (BTNL << 3) | (BTNC << 2) | (BTNR << 1) | BTND;
    
    return inputState;
    
}

//initialize all the GPIO pins used for driving the LEDs
void initAllLEDs(void) {
    //the LEDs are driven by the lower 8 bits of PORTA
    TRISACLR = 0xFF;   //configure as outputs
}

//write to all LEDs
void writeAllLEDs(unsigned char val) {
    LATA = (LATA & 0xFF00) | val;   //write val to LEDs
}

//write to a specific LED
//index is the bit position for the LED (0 to 7)
//val is 1 to turn on the LED, and 0 to turn off the LED
void writeLED(unsigned char index, unsigned char val) {
    unsigned char ledMask = 1 << index;
    if(val)
        LATASET = ledMask;
    else
        LATACLR = ledMask;
}
