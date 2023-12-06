/* ************************************************************************** */
/** @File Name
  bet.c

  @Description
    This file holds the functionality for handling bets in the casino game.
    It includes functions for placing a bet, checking the balance, withdrawing
    the bet from the balance, and winning a bet by adding the winnings to the balance.
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#include "bet.h"

int bet(Balance* balance, int betAmount, Bet* outBet) {
    // Check if the balance is sufficient for the bet
    if (balance->balance >= betAmount) {
        // Withdraw the bet amount from the balance
        balance->balance -= betAmount;

        // Set the bet amount in the Bet struct
        outBet->amount = betAmount;

        // Return success
        return 1;
    } else {
        // Insufficient balance for the bet
        return 0;
    }
}

void winBet(Balance* balance, Bet* bet, int multiplier) {
    // Calculate the winnings
    int winnings = bet->amount * multiplier;

    // Add the winnings to the balance
    balance->balance += winnings;
}
