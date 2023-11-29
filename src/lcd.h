/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Digilent

  @File Name
    lcd.h

  @Summary
    Defines the I/O pins and function prototypes for the LCD interfacing

  @Description
    The I/O pins used for interfacing to the LCD and the function prototypes
    are defined in this header file.
    Include the file in the project when this library is needed.
    Use #include "lcd.h" in the source files where the functions are needed.

  @Author
    Digilent (Edited by Girma Tewolde and Trevor Arcieri)
 
 */
/* ************************************************************************** */

#ifndef _LCD_H    /* Guard against multiple inclusion */
#define _LCD_H

//Define CPU clock frequency and core timer ticks for one second
#define CPU_FREQ    80000000
#define ONE_SEC_TICKS (CPU_FREQ/2)    

//port configuration values for input & output 
#define OUT     0
#define IN      1    

// LCD
#define tris_LCD_DISP_RS    TRISBbits.TRISB15
#define lat_LCD_DISP_RS     LATBbits.LATB15
#define ansel_LCD_DISP_RS   ANSELBbits.ANSB15
#define rp_LCD_DISP_RS      RPB15R


#define tris_LCD_DISP_RW    TRISDbits.TRISD5
#define  lat_LCD_DISP_RW    LATDbits.LATD5
#define rp_LCD_DISP_RW      RPD5R

#define tris_LCD_DISP_EN    TRISDbits.TRISD4
#define  lat_LCD_DISP_EN    LATDbits.LATD4
#define rp_LCD_DISP_EN      RPD4R

#define tris_LCD_DATA       TRISE
#define lat_LCD_DATA        LATE
#define prt_LCD_DATA        PORTE
#define msk_LCD_DATA        0xFF
#define  lat_LCD_DATA_ADDR   0xBF886440
#define ansel_LCD_DB2        ANSELEbits.ANSE2
#define ansel_LCD_DB4        ANSELEbits.ANSE4
#define ansel_LCD_DB5        ANSELEbits.ANSE5
#define ansel_LCD_DB6        ANSELEbits.ANSE6
#define ansel_LCD_DB7        ANSELEbits.ANSE7

#define cmdLcdFcnInit 	0x3C        // function set command, (8-bit interface, 2 lines, and 5x8 dots)
#define cmdLcdCtlInit 	0x0C        // display control set command
#define cmdLcdEntryMode 0x06        // Entry Mode Set
#define cmdLcdClear		0x01		// clear display command
#define cmdLcdRetHome	0x02		// return home command
#define cmdLcdDisplayShift 0x18		// shift display command
#define cmdLcdCursorShift  0x10		// shift cursor command
#define cmdLcdSetDdramPos	0x80	// set DDRAM position command
#define cmdLcdSetCgramPos	0x40	// set CGRAM position command

#define mskBStatus 0x80             // bit busy 
#define mskShiftRL 0x04             // bit for direction 
#define displaySetOptionDisplayOn	0x4 // Set Display On option
#define	displaySetOptionCursorOn 	0x2 // Set Cursor On option
#define	displaySetBlinkOn 			0x1 // Set Blink On option

#define posCgramChar0 0		// position in CGRAM for character 0
#define posCgramChar1 8		// position in CGRAM for character 1
#define posCgramChar2 16	// position in CGRAM for character 2
#define posCgramChar3 24	// position in CGRAM for character 3
#define posCgramChar4 32	// position in CGRAM for character 4
#define posCgramChar5 40	// position in CGRAM for character 5
#define posCgramChar6 48	// position in CGRAM for character 6
#define posCgramChar7 56	// position in CGRAM for character 7    
    
//LCD interfacing function prototypes    
    
#define LCD_SetWriteDdramPosition(bAddr) LCD_WriteCommand(cmdLcdSetDdramPos | bAddr);

void LCD_Init();
void LCD_InitSequence(unsigned char bDisplaySetOptions);
void LCD_WriteStringAtPos(char *szLn, unsigned char idxLine, unsigned char bAdr);
void LCD_DisplaySet(unsigned char bDisplaySetOptions);
void LCD_DisplayClear();
void LCD_DisplayShift(unsigned char fRight);
void LCD_CursorShift(unsigned char fRight);
void LCD_ReturnHome();
void LCD_WriteBytesAtPosCgram(unsigned char *pBytes, unsigned char len, unsigned char bAdr);

// private
unsigned char LCD_ReadByte();
unsigned char LCD_ReadStatus();
void LCD_WriteByte(unsigned char bData);
void LCD_SetWriteCgramPosition(unsigned char bAdr);
void LCD_WriteCommand(unsigned char bCmd);
void LCD_WriteDataByte(unsigned char bData);
void LCD_ConfigurePins();

//utility function for small time delay
void DelayAprox10Us( unsigned int tusDelay );

/* *****************************************************************************
 End of File
 */
