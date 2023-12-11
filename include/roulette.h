#ifndef ROULETTE_H
#define ROULETTE_H

#include <stdbool.h>
#include "balance.h"
#include "bet.h"
#include "randomization.h"
#include "input_wrapper.h"
#include "output_wrapper.h"

#define NUM_ROULETTE_NUMBERS 37 // Numbers 0-36
#define MAX_BETS 5 // Max number of bets per round
#define RED 1
#define BLACK 0
#define GREEN -1

typedef enum { NUMBER, COLOR, PARITY } BetType;
typedef struct { BetType type; int value; Bet wager; } RouletteBet;

// Function Declarations
void playRoulette(Balance* balance);
int spinRouletteWheel();
void placeBets(Balance* balance, RouletteBet bets[], int* numBets);
void processResults(int winningNumber, Balance* balance, RouletteBet bets[], int numBets);
int getColor(int number);
int payoutMultiplier(BetType type);
void printRouNum(int num);
void printBet(RouletteBet bet);

#endif
