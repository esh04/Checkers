#ifndef __CONSTANTS_H
#define __CONSTANTS_H

// size of checkers
#define SIZE 8

// colors
#define NOCOLOUR -1
#define BLUE 0
#define RED 1

// states of checkers
#define FULL 2
#define EMPTY -2

// type of peice
#define NORMAL 3
#define KING 4
#define NOPEICE -3

//structures for board and the peices

typedef struct coordinates
{
    int x; // coordinate x is an aplhabet so the ascii - 'A' can be stored. 
    int y; // board starts from 1, hence input - 1 will be stored.
} coordinates;

typedef struct peice
{
    int type; // whether the peice is a king or a normal piece. No piece if that coordinate has no peice on the b
    int colour; //colour of the peice, will be no colour if no peice exists on the location
} peice;

typedef struct checkersGrid
{
    int state; //empty or full
    peice checkers; // peice assosciated with that position in the grid;
} checkersGrid;


#endif