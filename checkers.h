#ifndef __CHECKERS_H
#define __CHECKERS_H

#include <stdio.h>
#include "constants.h"

void initBoard(checkersGrid Board[][SIZE]);
void printBoard(checkersGrid Board[][SIZE]);
int isvalid(checkersGrid Board[][SIZE], char P, char M, int b, char N, int d);
#endif
