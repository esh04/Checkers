#include "checkers.h"



int main()
{


    checkersGrid CheckerBoard[SIZE][SIZE];
    initBoard(CheckerBoard);
    printBoard(CheckerBoard);

    
    //Input from user
    int turn = 1;
    while (1)
    {
        coordinates start, final;
        printf("Enter values of X1 Y1 X2 Y2\n");
        char y1, y2;
        scanf("%c %d %c %d", &y1, &start.x, &y2, &final.x);
        start.y = y1 - 'A';
        final.y = y2 - 'A';
        movements(CheckerBoard, turn, start, final);
        printf("\n\n");
        printBoard(CheckerBoard);
    }

    return 0;
}


