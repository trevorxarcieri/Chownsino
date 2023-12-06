/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Kettering University

  @File Name
    keypad1.c

  @Summary
    Implements the functions keypad interfacing functions for the keypad interfacing
    on PMODA.

  @Description
    This file provides functions for implementing a keypad device driver. 
    The keypad ports initialization function has to be executed first before
    trying to access inputs from the keypad.  

  @Author
    Girma Tewolde and Trevor Arcieri
 
 */
/* ************************************************************************** */


#include <xc.h>
#include "keypad1.h"
#include "time.h"

//global data items
unsigned char keys[4][4] = {{'1','2','3', 'A'}, 
                            {'4','5','6', 'B'},
                            {'7','8','9', 'C'},
                            {'0','F','E', 'D'}
                           };

//the initKeypad() function properly configures the pins used for interfacing
//the keypad module to the PIC32 MCU)
//this function assumes the keypad module is connected to the PMODB port 
//of the Basys MX3 board (refer to the reference manual)

void initKeypad(void) {   
    //configure pins that support analog functions to operate in digital mode
    ANSELDCLR = 0x0002;       //configure PORTD pin 1 as digital

    //configure directions of pins
    //configure the columns as outputs and the rows as inputs
    col1_dir = OUT;
    col2_dir = OUT;
    col3_dir = OUT;
    col4_dir = OUT;
    row1_dir = IN;
    row2_dir = IN;
    row3_dir = IN;
    row4_dir = IN;
 }

//To receive inputs from the keypad the user calls the readKey() function 
//The function scans the four columns of the keypad sequentially, one at a time,
//starting with columns 1, by outputting logic 0 to one column at a time. 
//During the time when a specific column is driven by logic 0, if the user 
//pressed a key on that particular column, the algorithm will detect the row of 
//the key that is pressed. 
//From the combination of the active column and detected row numbers
//the program is able to identify the key that was presses and it returns its 
//character to the caller. If there was no key pressed during the scan time,
//the function returns 0 (which corresponds to NULL in C).
unsigned char readKey(void) {
    unsigned char keyout = 0;  //NULL;      //initialize keyout to NULL

	for(int i = 1; i <= 4; i++) //Iterate through columns 1-4
    {
        switch(i) //Turn off current column
        {
            case 1:
                col1 = 0;
                break;
            case 2:
                col2 = 0;
                break;
            case 3:
                col3 = 0;
                break;
            case 4:
                col4 = 0;
                break;
        }
        for(int j = 1; j <= 4; j++) //Iterate through rows 1-4
        {
            switch(j) //If a row is off, the key at the intersection of that row
                      //and the current column is being pressed
            {
                case 1:
                    if(!row1)
                    {
                        msDelay(20); //debounce
                        while(!row1); //wait for key unpress
                        keyout = keys[j-1][i-1];
                    }
                    break;
                case 2:
                    if(!row2)
                    {
                        msDelay(20); //debounce
                        while(!row2); //wait for key unpress
                        keyout = keys[j-1][i-1];
                    }
                    break;
                case 3:
                    if(!row3)
                    {
                        msDelay(20); //debounce
                        while(!row3); //wait for key unpress
                        keyout = keys[j-1][i-1];
                    }                    
                    break;
                case 4:
                    if(!row4)
                    {
                        msDelay(20); //debounce
                        while(!row4); //wait for key unpress
                        keyout = keys[j-1][i-1];
                    }
                    break;
            }
        }
        switch(i) //Turn current column back on
        {
            case 1:
                col1 = 1;
                break;
            case 2:
                col2 = 1;
                break;
            case 3:
                col3 = 1;
                break;
            case 4:
                col4 = 1;
                break;
        }
    }
	
    //return the key pressed. If no key was pressed during the key scan 
    //operation, return NULL
    return keyout;
}    

/* *****************************************************************************
 End of File
 */