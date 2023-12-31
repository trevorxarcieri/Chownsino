/* ************************************************************************** */
/** @File Name
  output_wrapper.h

  @Description
    This file groups the declarations of the functions that
    implement the wrapper output module.
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#ifndef OUTPUT_WRAPPER_H
#define OUTPUT_WRAPPER_H

#include <stdio.h>
#include "general_IO.h"
#include "lcd.h"
#include "uart.h"
#include "PmodOLEDrgb.h"
#include "card.h"  // Include the header for the Card struct

#define OLED_WIDTH 96
#define SQUARE_WIDTH 20
#define SQUARE_HEIGHT 20
#define SQUARE_SPACING 5

// Define the Roulette Square struct
typedef struct {
    uint16_t color;  // Color of the square
    const char* text;  // Text to be displayed in the square
} RouletteSquare;

void initOutput(PmodOLEDrgb* oledStruct);
void cleanupOutput(PmodOLEDrgb* oledStruct);

void displayCard(PmodOLEDrgb* oledStruct, Card card, int centerPosition);
void displayCards(PmodOLEDrgb* oledStruct, int numCards, int topLeftPosition, Card* cards);
void displayFullHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards);

void displaySquare(PmodOLEDrgb* oledStruct, int x, int y, RouletteSquare square);
void displaySquares(PmodOLEDrgb* oledStruct, int x, int y, int numSquares, RouletteSquare* squares);

void displayOLEDText(PmodOLEDrgb* oledStruct, int x, int y, unsigned char* text);
void eraseOLEDText(PmodOLEDrgb* oledStruct, int x, int y, int length);

void displayLCDText(int row, unsigned char* text);
void eraseLCDText();

void printlnUART(unsigned char *text);
void printUART(unsigned char *text);

void displayWin(/* Additional parameters as needed */);
void displayLoss(/* Additional parameters as needed */);
void displayDraw(/* Additional parameters as needed */);

// Add space for further display functions

#endif /* OUTPUT_WRAPPER_H */
