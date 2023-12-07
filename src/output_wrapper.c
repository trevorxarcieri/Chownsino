/* ************************************************************************** */
/** @File Name
  output_wrapper.c

  @Description
    This file holds the functionality for the wrapper output module,
    providing an initialization function and a cleanup function
    for various output devices.
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#include "output_wrapper.h"

void initOutput(PmodOLEDrgb* oledStruct) {
    // Initialize LEDs
    initAllLEDs();

    // Initialize LCD display
    LCD_Init();

    // Initialize UART
    initUART4();

    // Initialize OLED display
    initOLED(oledStruct);
}

void cleanupOutput(PmodOLEDrgb* oledStruct) {
    // Cleanup OLED display
    cleanupOLED(oledStruct);
}

void displayText(PmodOLEDrgb* oledStruct, int x, int y, const char* text) {
    OLEDrgb_SetCursor(oledStruct, x, y);
    OLEDrgb_PutString(oledStruct, (char *) &text);
}

void eraseText(PmodOLEDrgb* oledStruct, int x, int y, int length) {
    OLEDrgb_SetCursor(oledStruct, x, y);
    for (int i = 0; i < length; i++) {
        OLEDrgb_PutChar(oledStruct, ' ');
    }
}

void displaySquare(PmodOLEDrgb* oledStruct, int x, int y, RouletteSquare square) {
    // Assuming square.color is the color and square.text is the string
    OLEDrgb_DrawRectangle(oledStruct, x, y, x + SQUARE_WIDTH, y + SQUARE_HEIGHT, square.color, 1, square.color);
    displayText(oledStruct, x + 2, y + 2, square.text);
}

void displaySquares(PmodOLEDrgb* oledStruct, int x, int y, int numSquares, RouletteSquare* squares) {
    int currentX = x;
    int currentY = y;

    for (int i = 0; i < numSquares; i++) {
        displaySquare(oledStruct, currentX, currentY, squares[i]);
        currentX += SQUARE_WIDTH + SQUARE_SPACING;

        // Adjust to the next row if needed
        if ((currentX + SQUARE_WIDTH) > OLED_WIDTH) {
            currentX = x;
            currentY += SQUARE_HEIGHT + SQUARE_SPACING;
        }
    }
}
