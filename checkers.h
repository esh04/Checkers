#ifndef __CHECKERS_H
#define __CHECKERS_H

#include <stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "constants.h"
#include "stack.h"

void initBoard(checkersGrid Board[][SIZE]);
void printBoard(checkersGrid Board[][SIZE]);
int isvalid(checkersGrid Board[][SIZE], char P, char M, int b, char N, int d);
int movements(checkersGrid Board[][SIZE], char turn, coordinates c1, coordinates c2); //c1-Initial & c2-final coordinates 
int captures(checkersGrid Board[][SIZE], char turn, coordinates c1, coordinates c2);
int is_capture(checkersGrid Board[][SIZE], char turn, coordinates c);
int if_capture(checkersGrid Board[][SIZE], char turn);
coordinates* double_captures(checkersGrid Board[][SIZE], char turn, coordinates c);
void introduction();
int undo(checkersGrid Board[][SIZE],StackContents *stack, int moves, int capture);
void allPossibleMoves(checkersGrid Board[][SIZE], char turn);
char switchTurn(char turn);
//int captures(checkersGrid Board[][SIZE], char turn, coordinates c1, coordinates c2);

#endif
