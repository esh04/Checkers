#include "checkers.h"



int main()
{


    checkersGrid CheckerBoard[SIZE][SIZE];
    initBoard(CheckerBoard);
    printBoard(CheckerBoard);

    
    //Input from user
    char turn = 'O';
    while (1)
    {
        coordinates start, final;
        printf("\n*******%c Turn*******\n", turn);
        printf("Enter values of Y1 X1 Y2 X2\n");
        char y1, y2;
        
        scanf("%c %d %c %d", &y1, &start.x, &y2, &final.x);
        start.y = y1 - 'A';
        final.y = y2 - 'A';
        
        movements(CheckerBoard, turn, start, final);
        if(turn == 'X'){
            turn = 'O';
        }else{
            turn = 'X';
        }
        
        printf("\n\n");
        printBoard(CheckerBoard);
    }

    return 0;
}


