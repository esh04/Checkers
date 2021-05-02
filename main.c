#include "checkers.h"

int main()
{

    checkersGrid CheckerBoard[SIZE][SIZE];
    initBoard(CheckerBoard);

    //Input from user
    char turn = 'O';
    while (1)
    {
        // To clear output everytime
        system("clear");

        printf("\n\n       WELCOME TO CHECKER'S GAME\n\n");

        // Prints the board
        printBoard(CheckerBoard);

        coordinates start, final;
        printf("\n   *********** %c Turn **************\n", turn);

        // Taking inputs
        char y1, y2;
        printf("     Enter values of X1 Y1 X2 Y2\n");
        scanf("\n%c %d %c %d", &y1, &start.x, &y2, &final.x);

        // Takes lower characters as input
        y1 = toupper(y1);
        y2 = toupper(y2);

        // Converting to integer values
        start.y = y1 - 'A';
        final.y = y2 - 'A';

        int ans = movements(CheckerBoard, turn, start, final);
        printf("\n\n");

        if (ans == 0)
        {
            // Invalid move
            printf("\n      Invalid Move, Try Again!!!\n");
        }
        else
        {
            // Valid move
            if (turn == 'X')
            { // Player- O turn
                turn = 'O';
            }
            else
            { // Player- X turn
                turn = 'X';
            }
        }
    }

    return 0;
}