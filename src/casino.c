/* ************************************************************************** */
/** @File Name
  casino.c

  @Description
    This file holds the functionality for initializing, starting,
    and cleaning up the casino system, including both input and output modules.
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#include "casino.h"

void initCasino(PmodOLEDrgb* oledStruct) {
    // Initialize input module
    initInput();

    // Initialize output module
    initOutput(oledStruct);
}

void cleanupCasino(PmodOLEDrgb* oledStruct) {
    // Cleanup output module
    cleanupOutput(oledStruct);

    // Cleanup input module
}

void startCasino() {
    PmodOLEDrgb oledStruct;
    initCasino(&oledStruct);
    // Implement the startCasino functionality here
    // This function can be used to start the overarching casino system
    // and may involve interactions with the initialized input and output modules
    // For example, handling game logic, user interactions, etc.
    // Further implementation will depend on the specifics of your casino system.

    cleanupCasino(&oledStruct);
}
