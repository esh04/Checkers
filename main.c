#include "checkers.h"
#include "stack.h"

StackContents stack[10000];

int main()
{
    checkersGrid CheckerBoard[SIZE][SIZE];
    initBoard(CheckerBoard);
    int ans = 1;
    char turn = 'O';
    char ch;
    int counter = 0;
    introduction();
    if (scanf("%c", &ch))
        while (1)
        {
            // To clear output everytime
            system("clear");

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
            if (counter == 0)
            {
                printf("Press 2 if you want to view all possible moves for %c, else press any other key!\n", turn);
                int a;
                scanf("%d", &a);
                if (a == 2)
                {
                    allPossibleMoves(CheckerBoard, turn);
                }
                system("clear");
                printBoard(CheckerBoard);
                printf("\n                   ");
                printf(" ************* %c's Turn *************\n", turn);
            }

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

            int capture = captures(CheckerBoard, turn, start, final);

            ans = movements(CheckerBoard, turn, start, final) || capture;
            printf("\n\n");

            if (ans == 0)
            {
                // Invalid move
                printf("\n      Invalid Move, Try Again!\n");
            }
            else
            {
                system("clear");
                printBoard(CheckerBoard);
                // If Valid move push into stack everytime
                StackContents StackValues;
                StackValues.start = start;
                StackValues.final = final;
                StackValues.turn = turn;
                push(stack, StackValues);

                // Asking for Undo Option from user
                printf("\nPress 1 if you want to Undo, 2 to view all possible moves for %c, else press any other key!\n", switchTurn(turn));
                int a;
                scanf("%d", &a);
                if (a == 1)
                {
                    int moves;
                    printf("Enter no. of moves you want to Undo\n");
                    scanf("%d", &moves);

                    // Do Undo
                    int undoAns = undo(CheckerBoard, stack, moves, capture);
                    if (moves % 2 == 1)
                    {
                        turn = switchTurn(turn);
                    }
                    if (undoAns == 0)
                    {
                        printf("The no. of moves were Invalid");
                    }
                }
                else if (a == 2)
                {

                    allPossibleMoves(CheckerBoard, switchTurn(turn));
                }

                // Valid move
                turn = switchTurn(turn);
            }
        }
    return 0;
}
