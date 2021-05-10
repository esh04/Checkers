#include "checkers.h"
#include "stack.h"
#include "Que.h"

// ************File used to call & run the functions************

int main(void)
{
    // variables
    checkersGrid CheckerBoard[SIZE][SIZE];
    initBoard(CheckerBoard);
    StackContents stack[10000];
    Queue q = createQueue();
    int count_queue = 0;
    char turn = 'O';
    int capture, valid;
    coordinates start, final;
    char temp1, temp2;
    int moves;
    int reply;
    int undo_ans;
    int k;
    int temp;
    char dummy[100];
    int win = 0;
    int capture_possible;
    int capture_temp;
    char input[100];
    int draw;
    // graphics
    introduction();
    scanf("%[^\n]", input);
    getchar();
    while (1)
    {
        // takes input
        system("clear");
        printBoard(CheckerBoard);
        printf("\n               ");
        printf(" ************ %c's Turn ************\n", turn);
        printf("Input: ");
        scanf("%[^\n]", input);
        getchar();
        remove_spaces(input);
        // draw
        if (!strcmp(input, "5"))
        {
            if (win == 0)
            {
                system("clear");
                printBoard(CheckerBoard);
                printf("\n               ");
                printf(" ************ %c's Turn ************\n", switchTurn(turn));
                printf("Does %c accept the draw offer?\nEnter 1 to accept, else enter any other number\n", switchTurn(turn));
                scanf("%d", &draw);
                getchar();
                if (draw == 1)
                {
                    win = 3;
                    system("clear");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %c's Turn ************\n", switchTurn(turn));
                    printf("The game is a draw\n");
                }
                else
                {
                    printf("Player %c does not accept\n", switchTurn(turn));
                }
            }
            else
            {
                printf("Can't offer draw after win\n");
            }
            printf("Enter anything to continue.");
            scanf("%[^\n]", dummy);
            getchar();
        }
        // Exit
        else if (!strcmp(input, "0"))
        {
            system("clear");
            printBoard(CheckerBoard);
            printf("\n                  Thank you for playing the game!!\n\n");
            return 0;
        }
        // Input moves
        else if (!strcmp(input, "1"))
        {
            // if win or draw has taken place input cannot be called
            if (win != 0)
            {
                system("clear");
                printBoard(CheckerBoard);
                printf("\n               ");
                printf(" ************ %c's Turn ************\n", turn);
                printf("You cannot input as winner is declared; unless you undo\n");
                printf("Enter anything to continue.\n");
                scanf("%[^\n]", dummy);
                getchar();
            }
            else
            {
                system("clear");
                printBoard(CheckerBoard);
                printf("\n               ");
                printf(" ************ %c's Turn ************\n", turn);
                printf("             ");
                printf("      Enter values of X1 Y1 X2 Y2\n");
                scanf(" %c %d %c %d", &temp1, &start.x, &temp2, &final.x);
                getchar();
                temp1 = toupper(temp1);
                temp2 = toupper(temp2);
                start.y = temp1 - 65;
                final.y = temp2 - 65;
                // check if captures in the current position are possible
                capture_possible = if_capture_possible(CheckerBoard, turn);
                // check if capture move was played
                capture = captures(CheckerBoard, turn, start, final);
                capture_temp = capture > 0 ? 1 : 0;
                // if capture was possible and that move was not played
                if (capture_temp != capture_possible)
                    valid = -1;
                else
                    valid = movements(CheckerBoard, turn, start, final) || capture; //move will be valid if either of capture or movements are true

                printf("\n\n");
                // if the move made was valid
                if (valid == 0)
                {
                    // Invalid move
                    system("clear");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %c's Turn ************\n", turn);
                    printf("                     Invalid Move, Try Again!\n");
                    printf("Enter anything to continue.\n");
                    scanf("%[^\n]", dummy);
                    getchar();
                }
                // capture was possible but was not inputted my the player
                else if (valid == -1)
                {
                    system("clear");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %c's Turn ************\n", turn);
                    printf("\n           Invalid Move, Try Again! Capture is possible\n");
                    printf("Enter anything to continue.\n");
                    scanf("%[^\n]", dummy);
                    getchar();
                }
                // Valid move
                else
                {
                    sound();
                    // add to queue for review
                    enQueue(q, start, final, turn);
                    count_queue++;
                    // If Valid move push into stack everytime
                    StackContents StackValues;
                    StackValues.start = start;
                    StackValues.final = final;
                    StackValues.turn = turn;
                    StackValues.cap = capture;
                    if (CheckerBoard[final.x - 1][final.y].checkers.type == KING)
                        StackValues.type = 1;
                    else
                        StackValues.type = 0;
                    push(stack, StackValues);
                    // check if turn should be switched, it must not be if double or more captures are available consecutively
                    if (ifdouble(CheckerBoard, final, turn) && capture > 0)
                        ;
                    else
                        turn = switchTurn(turn);
                }
                // check for winner
                win = winner(CheckerBoard, turn);
                // draw
                if (win == 3)
                {
                    system("clear");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %c's Turn ************\n", turn);
                    printf("The game is a draw\n");
                }
                // O is the winner
                if (win == 1)
                {
                    system("clear");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %c's Turn ************\n", turn);
                    printf("The winner is O\n");
                }
                // X is the winner
                else if (win == 2)
                {
                    system("clear");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %c's Turn ************\n", turn);
                    printf("The winner is X\n");
                }
                // if winner has been declared
                if (win != 0)
                {
                    printf("Enter anything to continue.\n");
                    scanf("%[^\n]", dummy);
                    getchar();
                }
            }
        }
        // undo
        else if (!strcmp(input, "2"))
        {
            if (count_queue == 0)
            {
                system("clear");
                printBoard(CheckerBoard);
                printf("\n               ");
                printf(" ************ %c's Turn ************\n", turn);
                printf("Can't undo on the 0th move\n");
                printf("Enter anything to continue.\n");
                scanf("%[^\n]", dummy);
                getchar();
            }
            else
            {
                // take input
                printf("           Enter the number of moves you want to undo:\n");
                scanf(" %d", &moves);
                getchar();
                system("clear");
                printBoard(CheckerBoard);
                printf("\n               ");
                printf(" ************ %c's Turn ************\n", switchTurn(turn));
                printf("         Does player %c accept %c's request to undo %d moves?\n          Enter 1 to accept or any other number to deny\n", switchTurn(turn), turn, moves);
                scanf(" %d", &reply);
                getchar();
                if (reply == 1)
                {
                    printf("                   The player %c accepts\n", switchTurn(turn));
                    printf("Enter anything to continue undo moves\n");
                    scanf("%[^\n]", dummy);
                    getchar();
                    undo_ans = undo(CheckerBoard, stack, moves);
                    if (undo_ans == 1)
                    {
                        if (moves > 0)
                        {
                            win = 0;
                        }
                        // if undo is called, moves are removed from review
                        for (int i = 0; i < moves; i++)
                        {
                            pull(q);
                            count_queue--;
                        }
                        if (moves % 2 == 1)
                        {                            //turn swicthes if we undo odd number of moves but remains same when we undo even number
                            turn = switchTurn(turn); //toggles turn
                        }
                    }
                    // if input in undo moves > than moves that have been played
                    else if (undo_ans == 0)
                    {
                        system("clear");
                        printBoard(CheckerBoard);
                        printf("\n               ");
                        printf(" ************ %c's Turn ************\n", turn);
                        printf("Invalid Input, the number of moves to undo is greater than the number of moves played!!\n");
                        printf("Enter anything to continue.\n");
                        scanf("%[^\n]", dummy);
                        getchar();
                    }
                }
                // the opponent denies
                else
                {
                    system("clear");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %c's Turn ************\n", turn);
                    printf("                     The player %c denies\n", switchTurn(turn));
                    printf("Enter anything to continue.\n");
                    scanf("%[^\n]", dummy);
                    getchar();
                }
            }
        }
        // review
        else if (!strcmp(input, "3"))
        {
            if (count_queue == 0)
            {
                system("clear");
                printBoard(CheckerBoard);
                printf("\n               ");
                printf(" ************ %c's Turn ************\n", turn);
                printf("Cannot review in the 0th move\n");
                printf("Enter anything to continue.\n");
                scanf("%[^\n]", dummy);
                getchar();
            }
            else
                Reviewgame(q, count_queue);
        }
        // all possible moves
        else if (!strcmp(input, "4"))
        {
            printf("                  Enter the number of moves(k):");
            scanf(" %d", &k);
            getchar();
            system("clear");
            printBoard(CheckerBoard);
            printf("\n               ");
            printf(" ************ %c's Turn ************\n", turn);
            allPossibleMoves(CheckerBoard, turn, k); //will check all possible moves of player
            printf("Enter anything to continue.\n");
            scanf("%[^\n]", dummy);
            getchar();
        }
        // invalid input
        else
        {
            system("clear");
            printBoard(CheckerBoard);
            printf("\n               ");
            printf(" ************ %c's Turn ************\n", turn);
            printf("Invalid input\n");
            printf("Enter anything to continue.\n");
            scanf("%[^\n]", dummy);
            getchar();
        }
    }
    return 0;
}
