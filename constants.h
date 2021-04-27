#ifndef __CONSTANTS_H
#define __CONSTANTS_H

// size of checkers
#define SIZE 8

// colors 
#define WHITE -1
#define BLUE 0
#define RED 1

// states of checkers
#define FULL 2
#define EMPTY -2


struct checkersGrid{
    int isFull;  //empty or full
    int color;   //red, blue or white
};


struct coordinates{
    int x;
    int y;
};



#endif