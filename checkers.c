#include "checkers.h"
#include "Que.h"

void initBoard(checkersGrid Board[][SIZE])
{
    //Create empty board
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            Board[i][j].state = EMPTY;
            (Board[i][j].checkers).colour = NOCOLOUR;
            (Board[i][j].checkers).type = NOPEICE;
        }
    }

    //place the inital pieces

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < SIZE; j = j + 2)
        {
            if (i == 1)
            {
                Board[i][j].state = FULL;
                (Board[i][j].checkers).colour = RED;
                (Board[i][j].checkers).type = NORMAL;

                Board[SIZE - 1 - i][j + 1].state = FULL;
                (Board[SIZE - 1 - i][j + 1].checkers).colour = BLUE;
                (Board[SIZE - 1 - i][j + 1].checkers).type = NORMAL;
            }
            else
            {
                Board[i][j + 1].state = FULL;
                (Board[i][j + 1].checkers).colour = RED;
                (Board[i][j + 1].checkers).type = NORMAL;

                Board[SIZE - 1 - i][j].state = FULL;
                (Board[SIZE - 1 - i][j].checkers).colour = BLUE;
                (Board[SIZE - 1 - i][j].checkers).type = NORMAL;
            }
        }
    }
}

void printBoard(checkersGrid Board[][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("                   ");

        for (int k = 0; k < SIZE + 1; k++)
        {
            if (k == 0)
                printf("   ");
            else
                printf("----");
        }
        printf("-");
        printf("\n");
        printf("                   ");

        printf("%d  |", i + 1);
        for (int j = 0; j < SIZE; j++)
        {
           if ((Board[i][j].state == FULL) && ((Board[i][j].checkers).colour == RED))
            {
                if ((Board[i][j].checkers).type == KING)
                    printf("\033[31m X*"); //king will be denoted with an asterix next to it
                else
                    printf("\033[31m X ");
                printf("\033[0m|");
            }
            else if ((Board[i][j].state == FULL) && ((Board[i][j].checkers).colour == BLUE))
            {
                if ((Board[i][j].checkers).type == KING)
                    printf("\033[36m O*");
                else
                    printf("\033[36m O ");
                printf("\033[0m|");
            }
            else
            {
                printf("   |");
            }
        }

        printf("\n");
    }
    printf("                   ");

    for (int k = 0; k < SIZE + 1; k++)
    {
        if (k == 0)
            printf("   ");
        else
            printf("----");
    }
    printf("                   ");

    printf("\n");
    printf("   ");
    printf("                   ");

    for (int i = 0; i < SIZE; i++)
    {
        printf("  %c ", 'A' + i);
    }
    printf("\n");
}

char switchTurn(char turn)
{
    if (turn == 'X')
    {
        // Player- O turn
        turn = 'O';
    }
    else
    { // Player- X turn
        turn = 'X';
    }
    return turn;
}

int isvalid(checkersGrid Board[][SIZE], char P, char M, int b, char N, int d)
{
    int m;
    if (P == 'O')
    {
        m = 0;
    }
    // here m represents the player O or X
    // m=0(player-O) and m=1(player-X)
    if (P == 'X')
    {
        m = 1;
    }

    int a, c;
    a = M - 65;
    c = N - 65;

    b = b - 1;
    d = d - 1; // to have index from 0 t0 7 instead of 1 to 8
               // here a,b are coordinates of initial position and c,d are coordinates of final position

    int g, h;
    if (a < 0 || b < 0 || c < 0 || d < 0) // if they are not valid coordinates
    {
        return 0;
    }
    if (a > 7 || b > 7 || c > 7 || d > 7)
    {
        return 0;
    }

    g = c - a > 0 ? c - a : a - c;
    h = d - b > 0 ? d - b : b - d;

    if (g != h || g > 2 || h > 2)
        return 0;

    // checks whether  peice is present at coordinates (a,b)  and no piece is present at coordinates (c,d)
    if ((Board[b][a]).state == EMPTY || (Board[d][c]).state != EMPTY)
    {
        return 0;
    }

    if (m == 0) // for player-O(BLUE)
    {
        if ((Board[b][a].checkers).type == NORMAL)
        {
            if ((Board[b][a].checkers).colour == RED) // if that position contains another player's piece
                return 0;

            if (d == b + 1 || d == b + 2)
            {
                return 0;
            }
            if (d == b - 2)
            {
                if (c == a - 2)
                {
                    if ((Board[b - 1][a - 1].checkers).colour == BLUE || (Board[b - 1][a - 1].checkers).colour == NOCOLOUR)
                        return 0;
                }

                if (c == a + 2)
                {

                    if ((Board[b - 1][a + 1].checkers).colour == BLUE || (Board[b - 1][a + 1].checkers).colour == NOCOLOUR)
                        return 0;
                }
            }
        }

        if ((Board[b][a].checkers).type == KING)
        {
            if ((Board[b][a].checkers).colour == RED) // if that position contains another player's piece
                return 0;
            if (d == b - 2)
            {
                if (c == a - 2)
                {
                    if ((Board[b - 1][a - 1].checkers).colour == BLUE || (Board[b - 1][a - 1].checkers).colour == NOCOLOUR)

                        return 0;
                }

                if (c == a + 2)
                {
                    if ((Board[b - 1][a + 1].checkers).colour == BLUE || (Board[b - 1][a + 1].checkers).colour == NOCOLOUR)
                        return 0;
                }
            }

            if (d == b + 2)
            {
                if (c == a - 2)
                {

                    if ((Board[b + 1][a - 1].checkers).colour == BLUE || (Board[b + 1][a - 1].checkers).colour == NOCOLOUR)
                        return 0;
                }

                if (c == a + 2)
                {
                    if ((Board[b + 1][a + 1].checkers).colour == BLUE || (Board[b + 1][a + 1].checkers).colour == NOCOLOUR)

                        return 0;
                }
            }
        }
    }

    if (m == 1) //for player-X(RED)
    {
        if ((Board[b][a].checkers).type == NORMAL)
        {
            if ((Board[b][a].checkers).colour == BLUE) // if that position contains another player's piece
                return 0;

            if (d == b - 1 || d == b - 2)
            {
                return 0;
            }
            if (d == b + 2)
            {
                if (c == a - 2)
                {

                    if ((Board[b + 1][a - 1].checkers).colour == RED || (Board[b + 1][a - 1].checkers).colour == NOCOLOUR)

                        return 0;
                }

                if (c == a + 2)
                {
                    if ((Board[b + 1][a + 1].checkers).colour == RED || (Board[b + 1][a + 1].checkers).colour == NOCOLOUR)
                        return 0;
                }
            }
        }

        if ((Board[b][a].checkers).type == KING)
        {
            if ((Board[b][a].checkers).colour == BLUE) // if that position contains another player's piece
                return 0;
            if (d == b + 2)
            {
                if (c == a - 2)
                {
                    if ((Board[b + 1][a - 1].checkers).colour == RED || (Board[b + 1][a - 1].checkers).colour == NOCOLOUR)
                        return 0;
                }

                if (c == a + 2)
                {
                    if ((Board[b + 1][a + 1].checkers).colour == RED || (Board[b + 1][a + 1].checkers).colour == NOCOLOUR)
                        return 0;
                }
            }

            if (d == b - 2)
            {
                if (c == a - 2)
                {
                    if ((Board[b - 1][a - 1].checkers).colour == RED || (Board[b - 1][a - 1].checkers).colour == NOCOLOUR)
                        return 0;
                }

                if (c == a + 2)
                {

                    if ((Board[b - 1][a + 1].checkers).colour == RED || (Board[b - 1][a + 1].checkers).colour == NOCOLOUR)

                        return 0;
                }
            }
        }
    }

    return 1;
}

int movements(checkersGrid Board[][SIZE], char turn, coordinates c1, coordinates c2)
{
    char Y1, Y2;
    Y1 = c1.y + 'A';
    Y2 = c2.y + 'A';

    // isvalid=0 if invalid move, else isvalid=1
    int ans = isvalid(Board, turn, Y1, c1.x, Y2, c2.x);

    if (ans == 0) // Invalid move
    {
        return 0;
    }

    if ((abs(c1.y - c2.y) != 1) && (abs(c1.x - c2.x) != 1))
    {
        return 0;
    }
    else // Valid move
    {
        // Player - X
        if (turn == 'X')
        {
            // Change the current piece features
            Board[c2.x - 1][c2.y].state = FULL;
            Board[c2.x - 1][c2.y].checkers.colour = RED;
            if (c2.x == 8)
            {
                Board[c2.x - 1][c2.y].checkers.type = KING;
            }
            else
            {
                Board[c2.x - 1][c2.y].checkers.type = NORMAL;
            }
        }

        // Player - O
        else
        {
            // Change the current piece features
            Board[c2.x - 1][c2.y].state = FULL;
            Board[c2.x - 1][c2.y].checkers.colour = BLUE;
            if (c2.x == 1)
            {
                Board[c2.x - 1][c2.y].checkers.type = KING;
            }
            else
            {
                Board[c2.x - 1][c2.y].checkers.type = NORMAL;
            }
        }

        // Update the previous piece features
        Board[c1.x - 1][c1.y].state = EMPTY;
        Board[c1.x - 1][c1.y].checkers.colour = NOCOLOUR;
        Board[c1.x - 1][c1.y].checkers.type = NOPEICE;
    }
    return 1;
}
int captures(checkersGrid Board[][SIZE], char turn, coordinates c1, coordinates c2)
{
    char y1, y2;
    y1 = c1.y + 'A';
    y2 = c2.y + 'A';
    int ans, x_coordinate, y_coordinate;
    x_coordinate = (c2.x + c1.x) / 2;
    y_coordinate = (c2.y + c1.y) / 2;
    ans = isvalid(Board, turn, y1, c1.x, y2, c2.x);
    if (ans == 0)
    {
        return 0;
    }
    else if ((abs(c2.x - c1.x) != 2) && (abs(c2.y - c1.y) != 2))
    {
        return 0;
    }
    else
    {
        Board[c1.x - 1][c1.y].state = EMPTY;
        Board[c1.x - 1][c1.y].checkers.colour = NOCOLOUR;
        Board[c1.x - 1][c1.y].checkers.type = NOPEICE;
        Board[x_coordinate - 1][y_coordinate].state = EMPTY;
        Board[x_coordinate - 1][y_coordinate].checkers.colour = NOCOLOUR;
        Board[x_coordinate - 1][y_coordinate].checkers.type = NOPEICE;
        if (turn == 'X')
        {
            Board[c2.x - 1][c2.y].state = FULL;
            Board[c2.x - 1][c2.y].checkers.colour = RED;
            if (c2.x == 8)
            {
                Board[c2.x - 1][c2.y].checkers.type = KING;
            }
            else
            {
                Board[c2.x - 1][c2.y].checkers.type = NORMAL;
            }
        }
        else
        {
            Board[c2.x - 1][c2.y].state = FULL;
            Board[c2.x - 1][c2.y].checkers.colour = BLUE;
            if (c2.x == 1)
            {
                Board[c2.x - 1][c2.y].checkers.type = KING;
            }
            else
            {
                Board[c2.x - 1][c2.y].checkers.type = NORMAL;
            }
        }
	// for double captures 
	if(is_capture(Board, turn, c2) >= 1)
	{
		//double captures is possible, return 2
		return 2;
	}
	
    }
    return 1;

}

///
//checking for coordinates where captures can be continued, from before 
coordinates* double_captures(checkersGrid Board[][SIZE], char turn, coordinates c)
{
int x = c.x, i = 0, temp; 
char y = c.y + 'A';
int size = isvalid(Board, turn, y, x, y + 2, x + 2) + isvalid(Board, turn, y, x, y - 2, x + 2) + isvalid(Board, turn, y, x, y - 2, x - 2) + isvalid(Board, turn, y, x, y + 2, x -2);
coordinates *final_coordinates;
final_coordinates = (coordinates *)malloc(sizeof(coordinates) * size);
if(isvalid(Board, turn, y, x, y + 2, x + 2) == 1)
{
	final_coordinates[i].x = x + 2;
	temp = y + 2 - 'A';
	final_coordinates[i].y = temp;
	i++;
}
if(isvalid(Board, turn, y, x, y - 2, x + 2) == 1)
{
        final_coordinates[i].x = x + 2;
	temp = y - 2 - 'A';
        final_coordinates[i].y = temp;//int(y - 2 - 'A');
        i++;
}
if(isvalid(Board, turn, y, x, y - 2, x - 2) == 1)
{
        final_coordinates[i].x = x - 2;
	temp = y - 2 - 'A';
        final_coordinates[i].y = temp;//int(y - 2 - 'A');
        i++;
}
if(isvalid(Board, turn, y, x, y + 2, x -2) == 1)
{
        final_coordinates[i].x = x - 2;
	temp = y + 2 - 'A';
        final_coordinates[i].y = temp;
        i++;
}
return final_coordinates;
}
/////
//
//checking if capture is possible for a single square 
int is_capture(checkersGrid Board[][SIZE], char turn, coordinates c)
{
	//if captures is possible, return 1 else return 0
	int x = c.x;
	char y = c.y + 'A';
       	return isvalid(Board, turn, y, x, y + 2, x + 2) + isvalid(Board, turn, y, x, y - 2, x + 2) + isvalid(Board, turn, y, x, y - 2, x - 2) + isvalid(Board, turn, y, x, y + 2, x -2); 
}

///checking if captures is possible at all 
int if_capture(checkersGrid Board[][SIZE], char turn)
{       int colour, flag = 0;
        //char input;
	coordinates temp;
        /*if(turn == 'X')
        {
                colour = RED;
                step = 2;
        }
        else
        {
                colour = BLUE;
                step = -2;
        }*/
        for(int i = 0; i < SIZE; i++)
        {
                for(int j = 0; j < SIZE; j++)
                {
                        //we'll first check which one of these are within bounds. 
                        if ((Board[i][j].checkers).colour == colour)
                        {
				temp.x = i;
				temp.y = j + 'A';
                                //flag = flag | isvalid(Board, turn, input, i, input + 2, i + 2) | isvalid(Board, turn, input, i, input + 2, i - 2) | isvalid(Board, turn, input, i, input - 2, i + 2) | isvalid(Board, turn, input, i, input - 2, i - 2);
				flag = flag | is_capture(Board, turn, temp);
                                // j will be the alphabet, i is the letter input        
                                //pass all possible vanues to is_valid function and see if a one is being returned

                        }
                }
        }
        return flag;

}

void allPossibleMoves(checkersGrid Board[][SIZE], char turn, int k)
{
    int colour, forward;
    checkersGrid tempBoard[SIZE][SIZE];
    //Copy contents of Board to tempBoard
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            tempBoard[i][j].state = Board[i][j].state;
            (tempBoard[i][j].checkers).colour = (Board[i][j].checkers).colour;
            (tempBoard[i][j].checkers).type = (Board[i][j].checkers).type;
        }
    }
    /*LIST OF ALL POSSIBLE MOVES:
    1. forward empty diagonal for every peice not captured
    2. if its king forward and backward diagonals 
    3. jump/double jump -- should be the only valid move when exists
    */

    if (turn == 'X')
    {
        colour = RED;
        forward = 1; // for player X forward is adding one to the y coordinate
    }
    else if (turn == 'O')
    {
        colour = BLUE;
        forward = -1; // for the player O forward is subtracting one from the y coordinate
    }

    // check whether capture is possible, if it is that is the only possible move for the player

    // put the code for checking if any capture is possible here
    if (0) //iscapture
    {
        //perform capture on tempBoard
        allPossibleMoves(tempBoard, switchTurn(turn), k - 1);
        return;
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {


            if ((tempBoard[j][i].checkers).colour == colour)
            {
                coordinates initial, final;
                initial.x = i;
                initial.y = j;

                //check valid moves for this peice

                if ((tempBoard[j][i].checkers).type == KING)
                {
                    //can move to backward diagonal too
                    if (isvalid(tempBoard, turn, i + 'A', j + 1, i + 'A' + 1, j - forward + 1))
                    {
                        final.x = i + 1;
                        final.y = i - forward;
                        movements(tempBoard, turn, initial, final);
                        printf("%c%d to %c%d->\n\t", i + 'A', j + 1, i + 'A' + 1, j - forward + 1);
                        for (int m = 0; m < 3 - k; m++)   //this loop is only for indenting the output for a better view
                            printf("\t");
                        if (k - 1 > 0)
                            allPossibleMoves(tempBoard, switchTurn(turn), k - 1); //recursion after toggling the turn and decrementing k as one iteration is completed
                        printf("\n");
                    }
                    if (isvalid(tempBoard, turn, i + 'A', j + 1, i + 'A' - 1, j - forward + 1))
                    {
                        final.x = i - 1;
                        final.y = i - forward;
                        movements(tempBoard, turn, initial, final);
                        printf("%c%d to %c%d->\n\t", i + 'A', j + 1, i + 'A' - 1, j - forward + 1);
                        for (int m = 0; m < 3 - k; m++)
                            printf("\t");
                        if (k - 1 > 0)
                            allPossibleMoves(tempBoard, switchTurn(turn), k - 1); //recursion after toggling the turn and decrementing k as one iteration is completed
                        printf("\n");
                    }
                }
                //check forward movement
                if (isvalid(tempBoard, turn, i + 'A', j + 1, i + 1 + 'A', j + 1 + forward))
                {
                    final.x = i + 1;
                    final.y = i + forward;
                    movements(tempBoard, turn, initial, final);
                    for (int m = 0; m < 3 - k; m++)
                        printf("\t");
                    printf("%c%d to %c%d->\n", i + 'A', j + 1, i + 'A' + 1, j + forward + 1);
                    if (k - 1 > 0)
                        allPossibleMoves(tempBoard, switchTurn(turn), k - 1); //recursion after toggling the turn and decrementing k as one iteration is completed
                }
                if (isvalid(tempBoard, turn, i + 'A', j + 1, i + 'A' - 1, j + 1 + forward))
                {
                    final.x = i - 1;
                    final.y = i + forward;
                    movements(tempBoard, turn, initial, final);
                    for (int m = 0; m < 3 - k; m++)
                        printf("\t");
                    printf("%c%d to %c%d->\n", i + 'A', j + 1, i + 'A' - 1, j + forward + 1);
                    if (k - 1 > 0)
                        allPossibleMoves(tempBoard, switchTurn(turn), k - 1); //recursion after toggling the turn and decrementing k as one iteration is completed
                }

            }
        }
    }
}

void introduction()
{
    system("clear");

    printf("\n\n\n +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
           " ____________________________________________________________________________\n\n"
           "   ######  ##     ## ########  ######  ##    ## ######## ########   ######\n"
           "  ##    ## ##     ## ##       ##    ## ##   ##  ##       ##     ## ##    ##\n"
           "  ##       ##     ## ##       ##       ##  ##   ##       ##     ## ##       \n"
           "  ##       ######### ######   ##       #####    ######   ########   ######  \n"
           "  ##       ##     ## ##       ##       ##  ##   ##       ##   ##         ## \n"
           "  ##    ## ##     ## ##       ##    ## ##   ##  ##       ##    ##  ##    ##\n"
           "   ######  ##     ## ########  ######  ##    ## ######## ##     ##  ######  \n"
           " ____________________________________________________________________________\n\n"
           " +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n\n\n\n Press any key to continue..");
}

// Stack Implementation in C- using arrays
int top = -1;

void push(StackContents s[10000], StackContents c)
{
    top++;
    s[top] = c;
}

void pop(StackContents s[10000])
{
    if (top <= -1)
    {
        printf("You have entered a wrong value of moves!\n");
        return;
    }
    else
    {
        top--;
    }
}

int undo(checkersGrid Board[][SIZE], StackContents *stack, int moves, int capture)
{   
    // Stack
    if (top < moves - 1) 
    {
        return 0;
    }
    else
    {
        // if(capture == 1)
        // {
        //     moves++;
        // }

        for (int i = 0; i < moves; i++)
        {
            if (capture == 1 && moves == 1)
            {
                StackContents AllValues = stack[top];
                coordinates c1 = AllValues.start; // Initial
                coordinates c2 = AllValues.final; // Final
                char turn = AllValues.turn;       // Turn can be X or O

                pop(stack);

                if (turn == 'X')
                {
                    // Inital State
                    Board[c1.x - 1][c1.y].state = FULL;
                    Board[c1.x - 1][c1.y].checkers.colour = RED;
                    Board[c1.x - 1][c1.y].checkers.type = NORMAL;

                    Board[(c1.x + c2.x) / 2 - 1][(c1.y + c2.y) / 2].state = FULL;
                    Board[(c1.x + c2.x) / 2 - 1][(c1.y + c2.y) / 2].checkers.colour = BLUE;
                    Board[(c1.x + c2.x) / 2 - 1][(c1.y + c2.y) / 2].checkers.type = NORMAL;
                }
                else
                {
                    // Inital State
                    Board[c1.x - 1][c1.y].state = FULL;
                    Board[c1.x - 1][c1.y].checkers.colour = BLUE;
                    Board[c1.x - 1][c1.y].checkers.type = NORMAL;

                    Board[(c1.x + c2.x) / 2 - 1][(c1.y + c2.y) / 2].state = FULL;
                    Board[(c1.x + c2.x) / 2 - 1][(c1.y + c2.y) / 2].checkers.colour = RED;
                    Board[(c1.x + c2.x) / 2 - 1][(c1.y + c2.y) / 2].checkers.type = NORMAL;
                }

                // Final State
                Board[c2.x - 1][c2.y].state = EMPTY;
                Board[c2.x - 1][c2.y].checkers.colour = NOCOLOUR;
                Board[c2.x - 1][c2.y].checkers.type = NOPEICE;
            }

            else
            {

                StackContents AllValues = stack[top];
                coordinates c1 = AllValues.start; // Initial
                coordinates c2 = AllValues.final; // Final
                char turn = AllValues.turn;       // Turn can be X or O

                pop(stack);

                if (turn == 'X')
                {
                    // Inital State
                    Board[c1.x - 1][c1.y].state = FULL;
                    Board[c1.x - 1][c1.y].checkers.colour = RED;
                    Board[c1.x - 1][c1.y].checkers.type = NORMAL;
                }
                else
                {
                    // Inital State
                    Board[c1.x - 1][c1.y].state = FULL;
                    Board[c1.x - 1][c1.y].checkers.colour = BLUE;
                    Board[c1.x - 1][c1.y].checkers.type = NORMAL;
                }

                // Final State
                Board[c2.x - 1][c2.y].state = EMPTY;
                Board[c2.x - 1][c2.y].checkers.colour = NOCOLOUR;
                Board[c2.x - 1][c2.y].checkers.type = NOPEICE;
            }
        }
    }
    return 1;
}
Que newmove(coordinates a, coordinates b, char c)
{
    Que temp = (Que)malloc(sizeof(struct quecontents));
    temp->c1.x = a.x;
    temp->c1.y = a.y;
    temp->c2.x = b.x;
    temp->c2.y = b.y;
    temp->c = c;
    temp->next = NULL;
    return temp;
}
// basically my datastructure has three properties
//1. enque 2.Deque 3.eject

Queue createQueue()
{
    Queue q = (Queue)malloc(sizeof(struct queue));
    q->front = q->rear = NULL;
    return q;
}
void enQueue(Queue q, coordinates a, coordinates b, char c)
{
    Que temp = newmove(a, b, c);
    // If queue is empty, then new node is front and rear both
    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }
    // Add the new node at the end of queue and change rear

    q->rear->next = temp;
    q->rear = temp;
}

Que deQueue(Queue q)
{
    // If queue is empty, return NULL.
    if (q->front == NULL)
        return NULL;

    // Store previous front and move front one node ahead
    Que temp = q->front;

    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;

    temp->next = NULL;

    return temp;
}

void pull(Queue q)
{

    Que s;
    s = (Que)malloc(sizeof(struct quecontents));

    if (q->front == NULL)
    {
        return;
    }
    s = q->front;

    if (s->next == NULL)
    {
        q->front = NULL;
        q->rear = NULL;
        s = NULL;
    }
    else
    {

        while (s->next->next != NULL)
        {
            s = s->next;
        }

        s->next = NULL;

        q->rear=s;
    }
}


void Reviewgame(Queue q,int n)
{
    int count=0;
    char h;
    //int x1,x2,y1,y2;
    coordinates c1,c2;
    char d;
    int g;
    checkersGrid Board[8][8];
    initBoard(Board);
    while (count < n)
    {
        
        if(count==0)
        {
            system("clear");
            printBoard(Board);
                 for (int c = 1; c <= 32767; c++) 
       for (int d = 1; d <= 32767; d++) 
       {} 

        }
        Que p = (Que)malloc(sizeof(struct quecontents));
        p = deQueue(q);
        c1.x = p->c1.x;
        c1.y= p->c1.y;
        c2.x = p->c2.x;
        c2.y = p->c2.y;
        d=p->c;

        enQueue( q, c1, c2, d);
        

        if (abs(c2.x - c1.x) == 2 && abs(c2.y - c1.y) == 2)
        {
          g=captures(Board, d,c1,c2);
        }
            else
            {
                g = movements( Board,d,c1,c2);
            }

            system("clear");
            printBoard(Board);
            printf("--------Press any alphabet to see next move------\n");
            scanf("\n%c",&h);

            count++;
        
    }
}
