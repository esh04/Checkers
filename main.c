
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
            
            ans =  movements(CheckerBoard, turn, start, final) || capture;
            printf("\n\n");



            if (ans == 0)
            {
                // Invalid move
                printf("\n      Invalid Move, Try Again!\n");
            }
            else
            {   
                printBoard(CheckerBoard);
                // If Valid move push into stack everytime
                StackContents StackValues;
                StackValues.start = start;
                StackValues.final = final;
                StackValues.turn  = turn;
                push(stack, StackValues);

                // Asking for Undo Option from user
                printf("Press 1 if you want to Undo, else press any other key!\n");
                int a;
                scanf("%d",&a);
                if(a==1){
                    int moves;
                    printf("Enter no. of moves you want to Undo\n");
                    scanf("%d", &moves);

                    // Do Undo 
                    int undoAns = undo(CheckerBoard, stack, moves, capture);
                    if(undoAns==0){
                        printf("The no. of moves were Invalid");
                    }
                }

                
                // Valid move
                if (turn == 'X')
                {  
                    // Player- O turn
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
