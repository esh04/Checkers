#ifndef __CHECKERS_H
#define __CHECKERS_H




#include <stdio.h>
#include<stdlib.h>
#include "constants.h"

void initBoard(checkersGrid Board[][SIZE]);
void printBoard(checkersGrid Board[][SIZE]);
int isvalid(checkersGrid Board[][SIZE], char P, char M, int b, char N, int d);
void movements(checkersGrid Board[][SIZE], int turn, coordinates c1, coordinates c2); //c1-Initial & c2-final coordinates, turn =0 for player 1 & turn=1 for player 2


#endif
