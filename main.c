
#include "checkers.h"

int main()
{
    checkersGrid CheckerBoard[SIZE][SIZE];
    initBoard(CheckerBoard);
    int ans = 1;
    char turn = 'O';
    char ch;
    asciiArt();
    if (scanf("%c", &ch))
        while (1)
        {
            // To clear output everytime
            system("clear");

            //printf("\n\n       WELCOME TO CHECKER'S GAME\n\n");

            // Prints the board
            printBoard(CheckerBoard);

            coordinates start, final;
            printf("\n                   ");

            printf(" ************* %c's Turn *************\n", turn);
            if (ans == 0)
            {
                printf("\n                   ");

                printf("      Invalid Move, Try Again!\n");
            }
            // Taking inputs
            char y1, y2;
            printf("                   ");

            printf("     Enter values of X1 Y1 X2 Y2\n");
            //Input from user
            scanf("\n%c %d %c %d", &y1, &start.x, &y2, &final.x);
            // Takes lower characters as input
            y1 = toupper(y1);
            y2 = toupper(y2);

            // Converting to integer values
            start.y = y1 - 'A';
            final.y = y2 - 'A';

            ans = movements(CheckerBoard, turn, start, final) || captures(CheckerBoard, turn, start, final);
            printf("\n\n");

            if (ans == 0)
            {
                // Invalid move
                printf("\n      Invalid Move, Try Again!\n");
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
