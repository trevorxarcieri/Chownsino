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

//Define admin code timeout as 10s
#define ADMIN_CODE_TIMEOUT  10000

//Define admin code to be 6 digits long
#define ADMIN_CODE_LENGTH 6

typedef struct {
    int balance;
} Balance;

Balance* createBalance(void);
int addToBalance(Balance* balance, int amount);
int subtractFromBalance(Balance* balance, int amount);
int adminAddToBalance(Balance* balance, int amount, const char* adminCode);

#endif /* BALANCE_H */
