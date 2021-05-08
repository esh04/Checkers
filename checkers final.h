#ifndef __CHECKERS_H__
#define __CHECKERS_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "constants final.h"

// representation of the coordinates
typedef struct coordinates
{
    int x; // stores characters from A to H 
    int y; // stores number from 1 to 8
} coordinates;
// representation of peices
typedef struct peice
{
    int type; // stores whether the peice is a king or a normal piece and no piece if the coordinate has no peice on it
    int colour; // stores colour of the peice, is nocolour if no peice exists on the coordinate or it is blue or red
} peice;
// representation of the board
typedef struct checkersGrid
{
    int state; // empty or full acording to wether a peice exists or not
    peice checkers; // peice assosciated with that position in the grid;
} checkersGrid;

void initBoard(checkersGrid Board[][SIZE]);
void printBoard(checkersGrid Board[][SIZE]);
int isValid(checkersGrid Board[][SIZE], char turn, coordinates start, coordinates end);
void introduction();
#endif