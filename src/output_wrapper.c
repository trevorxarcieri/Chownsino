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

void displayCard(PmodOLEDrgb* oledStruct, Card card, int centerPosition) {
    // Implement display logic using UART for now
    //TODO: change display to OLED

    // Display card value
    char valueStr[CARD_STR_LEN];  // Assuming the maximum length of the value is 2 characters
    printCardVal(valueStr, card.value);
    printUART((uint8_t*)valueStr);

    // Display card suit
    char suitStr[2];  // Assuming the maximum length of the suit is 1 character
    switch (card.suit) {
        case HEARTS:
            suitStr[0] = 'H';
            break;
        case DIAMONDS:
            suitStr[0] = 'D';
            break;
        case CLUBS:
            suitStr[0] = 'C';
            break;
        case SPADES:
            suitStr[0] = 'S';
            break;
        default:
            suitStr[0] = '?';
    }
    suitStr[1] = '\0';
    printUART((uint8_t*)suitStr);
}

void displayFullHand(PmodOLEDrgb* oledStruct, Card* cards, int numCards) {
    for(int i = 0; i < numCards - 1; i++)
    {
        displayCard(oledStruct, cards[i], 0);
        printUART(", ");
    }
    displayCard(oledStruct, cards[numCards - 1], 0);
    printlnUART("");
}


void displayCards(PmodOLEDrgb* oledStruct, int numCards, int topLeftPosition, Card* cards) {
    // Implement display logic using UART for now
    //TODO: change display to OLED

    for (int i = 0; i < numCards; ++i) {
        displayCard(oledStruct, cards[i], topLeftPosition + i);
    }
}

void displayOLEDText(PmodOLEDrgb* oledStruct, int x, int y, unsigned char* text) {
    OLEDrgb_SetCursor(oledStruct, x, y);
    OLEDrgb_PutString(oledStruct, (char *) &text);
}

void eraseOLEDText(PmodOLEDrgb* oledStruct, int x, int y, int length) {
    OLEDrgb_SetCursor(oledStruct, x, y);
    for (int i = 0; i < length; i++) {
        OLEDrgb_PutChar(oledStruct, ' ');
    }
}

void displayLCDText(int row, unsigned char* text)
{
    LCD_WriteStringAtPos((char *) text, row, 0);
}

void eraseLCDText()
{
    LCD_DisplayClear();
}

void printlnUART(unsigned char *text)
{
    UART4_putstr((unsigned char*) text);
    UART4_putstr("\n\r");
}
void printUART(unsigned char *text)
{
    UART4_putstr((unsigned char*) text);
}

void displaySquare(PmodOLEDrgb* oledStruct, int x, int y, RouletteSquare square) {
    // Assuming square.color is the color and square.text is the string
    OLEDrgb_DrawRectangle(oledStruct, x, y, x + SQUARE_WIDTH, y + SQUARE_HEIGHT, square.color, 1, square.color);
    displayOLEDText(oledStruct, x + 2, y + 2, (unsigned char *) square.text);
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
