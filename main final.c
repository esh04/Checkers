#include "checkers final.h"

int main(void)
{
    checkersGrid CheckerBoard[SIZE][SIZE];
    initBoard(CheckerBoard);
    char turn = 'O';
    int winner = 0;
    int input;
    introduction();
    if (getchar())
    {
        while (winner == 0)
        {
            printf("Press 0 to exit the game\n");
            printf("Press 1 to input a move\n");
            printf("Press 2 to view possible all possible moves for k turns\n");
            printf("Press 3 to review\n");
            printf("Press 4 to undo\n");
            scanf("%d", &input);
            while (input < 0 && input > 4)
            {
                printf("Invalid Input\nTry Again!!\n");
                scanf("%d", &input);
            }
            if (input == 0)
            {
                printf("Thank you for playing!!\n");
                return 0;
            }
            if (input == 1)
            {
                input_move(CheckerBoard);
                winner = checkWinner(CheckerBoard);
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
        printf("The game has ended with the winner ");
        if (winner == 1)
            printf("X\n");
        else
            printf("O\n");
        while (1)
        {
            printf("Now only review and undo functions can be used\n");
            printf("Press 0 to exit the game\n");
            printf("Press 1 to review\n");
            printf("Press 2 to undo\n");

            scanf("%d", &input);
            while (input < 0 && input > 2)
            {
                printf("Invalid Input\nTry Again!!\n");
                scanf("%d", &input);
            }
            if (input == 0)
            {
                printf("Thank you for playing!!\n");
                return 0;
            }
            else if (input == 1)
            {
                review(CheckerBoard);
            }
            else
            {
                undo(CheckerBoard);
            }
        }
    }
    return 0;
}