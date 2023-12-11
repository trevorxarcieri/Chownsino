/* ************************************************************************** */
/** @File Name
  balance.h

  @Description
    This file groups the declarations of the functions and structures that
    implement the balance module (defined in balance.c). 
  
  @Author
    Trevor Arcieri and Nicholas Chown
 
 */
/* ************************************************************************** */

#ifndef BALANCE_H
#define BALANCE_H

#include <string.h>
#include <stdio.h>
#include "keypad1.h"
#include "time.h"
#include "output_wrapper.h"

#define ADMIN_SECRET_CODE "123456"

//Define admin code timeout as 10s
#define ADMIN_CODE_TIMEOUT  10000

//Define admin code to be 6 digits long
#define ADMIN_CODE_LENGTH 6

//Define admin balance add amount timeout as 10s
#define ADMIN_AMT_TIMEOUT 10000

//Define admin balance add max length as 9 digits
#define MAX_AMT_LENGTH 9

typedef enum {
  POSITIVE,
  NEGATIVE
} Sign;

typedef struct {
    unsigned int balance;
} Balance;

void initBalance(Balance* balance);
void addToBalance(Balance* balance, int amount);
void subtractFromBalance(Balance* balance, int amount);
void adminModBalance(Balance* balance, Sign sign);
unsigned int amtFromStr(char* str, int len);
void printBalance(Balance* balance);

#endif /* BALANCE_H */
