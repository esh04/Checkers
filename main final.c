#include "checkers final.h"

int main(void)
{
    checkersGrid CheckerBoard[SIZE][SIZE];
    initBoard(CheckerBoard);
    char turn = 'O';
    int no_winner = 0;
    int is_valid = 1;
    int input;
    introduction();
    if (getchar())
    {
        while (no_winner == 0)
        {
            system("clear");
            printBoard(CheckerBoard);

            printf(" ************* %c's Turn *************\n", turn);
            if (is_valid == 0)
            {
                printf("\n                   ");

                printf("      Invalid Move, Try Again!\n");
            }
            printf("Press 1 to input a move\n");
            printf("Press 2 to view possible all possible moves for k turns\n");
            printf("Press 3 to review\n");
            printf("Press 4 to undo\n");
            scanf("%d", &input);
            while (input < 1 && input > 4)
            {
                printf("Invalid Input\nTry Again!!\n");
                scanf("%d", &input);
            }
            if (input == 1)
            {
                input_move(CheckerBoard);
            }
            else if (input == 2)
            {
                allPossibleMoves(CheckerBoard);
            }
            else if (input == 3)
            {
                review(CheckerBoard);
            }
            else
            {
                undo(CheckerBoard);
            }
        }
    }
}