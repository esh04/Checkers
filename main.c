#include "checkers.h"
#include "stack.h"
#include "Que.h"

StackContents stack[10000];

int main()
{
    checkersGrid CheckerBoard[SIZE][SIZE];
    initBoard(CheckerBoard);

    Queue q= createQueue();
    int count=0;
    int ans = 1;
    char turn = 'O';
    char ch;
    int counter = 0;
    coordinates *temp;
    introduction();
    if (scanf("%c", &ch))
        while (1)
        {
            // To clear output everytime
            system("clear");

            // Prints the board
            printBoard(CheckerBoard);

            coordinates start, final;// *temp;
            printf("\n                   ");

            printf(" ************* %c's Turn *************\n", turn);
            if (ans == 0) // ans is 0 incase of an invalid move
            {
                printf("\n                   ");

                printf("      Invalid Move, Try Again!\n");
            }

            // Taking inputs
            char y1, y2;
            if (counter == 0) //visible only for first move as undo will not be valid at this point, hence only all posible moves
            {
                printf("Press 2 if you want to view all possible moves for %c, else press any other key!\n", turn);
                int a;
                scanf("%d", &a);
                if (a == 2)
                {
                    printf("Enter k: ");
                    int k = 0;
                    scanf("%d", &k);
                    allPossibleMoves(CheckerBoard, turn, k); //prints coordinates of all moves possible of the current player
                    int temp;
                    printf("\n\nPress any key to continue.\n");
                    scanf("%d", &temp);
                 
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

            //checks whether the coordinates are for capture
            int capture = captures(CheckerBoard, turn, start, final);

            ans = movements(CheckerBoard, turn, start, final) | capture; //move will be valid if either of capture or movements are tru
            printf("\n\n");

            if (ans == 0)
            {
                // Invalid move
                printf("\n      Invalid Move, Try Again!\n");
            }
            else if(ans == 1)
            {
                system("clear");
                printBoard(CheckerBoard);
                
                 enQueue( q,start,final,turn);
                 count++;
                // If Valid move push into stack everytime
                StackContents StackValues;
                StackValues.start = start;
                StackValues.final = final;
                StackValues.turn = turn;
                push(stack, StackValues);

                // Asking for Undo and all possible moves Option from user
                printf("\nPress 1 to Undo, 2 to view all possible moves for %c, 3 to review all moves, else press any other key!\n", switchTurn(turn));
                int a;
                scanf("%d", &a);
                if (a == 1)
                {
                    int moves;
                    printf("Enter the number of moves you want to Undo\n");
                    scanf("%d", &moves);

                    // Do Undo
                    int undoAns = undo(CheckerBoard, stack, moves, capture);
                    for(int i=0;i<moves;i++)
                    {
                          pull(q);
                          count--;
                    }
                    if (moves % 2 == 1)
                    {                            //turn swicthes if we undo odd number of moves but remains same when we undo even number
                        turn = switchTurn(turn); //toggles turn
                    }
                    if (undoAns == 0)
                    {
                        printf("The number of moves were Invalid");
                    }
                }
                else if (a == 2)
                {
                    printf("Enter k: ");
                    int k = 0;
                    scanf("%d", &k);
                    allPossibleMoves(CheckerBoard, switchTurn(turn), k); //will check all possible moves of next player hence the toggle
                    int temp;
                    printf("\n\nPress any key to continue.\n");
                    scanf("%d", &temp);
                }
                else if(a == 3)
                {
                    Reviewgame(q,count);
                }

                turn = switchTurn(turn); //toggle turn
            }
        }
    return 0;
}
