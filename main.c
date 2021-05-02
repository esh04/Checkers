#include "checkers.h"



int main()
{

    printf("\n\n       WELCOME TO CHECKER'S GAME\n\n");
    checkersGrid CheckerBoard[SIZE][SIZE];
    initBoard(CheckerBoard);
    printBoard(CheckerBoard);

    
    //Input from user
    char turn = 'O';
    while (1)
    {
        coordinates start, final;
        printf("\n   *********** %c Turn **************\n", turn);
        printf("     Enter values of X1 Y1 X2 Y2\n");
        char y1, y2;
        
        scanf("\n%c %d %c %d", &y1, &start.x, &y2, &final.x);
        y1 = toupper(y1);
        y2 = toupper(y2);

        start.y = y1 - 'A';
        final.y = y2 - 'A';
        
        int ans = movements(CheckerBoard, turn, start, final);
        printf("\n\n");
        printBoard(CheckerBoard);

        if(ans==0){
            printf("\n      Invalid Move, Try Again!!!\n");
        }else{
            if(turn == 'X'){
                turn = 'O';
            }else{
                turn = 'X';
            }
        }
        
    }

    return 0;
}