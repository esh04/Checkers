#include "checkers.h"

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

        for (int k = 0; k < SIZE + 1; k++)
        {
            if (k == 0)
                printf("   ");
            else
                printf("----");
        }
        printf("-");
        printf("\n");

        printf("%d  |", i + 1);
        for (int j = 0; j < SIZE; j++)
        {

            if ((Board[i][j].state == FULL) && ((Board[i][j].checkers).colour == RED) && ((Board[i][j].checkers).type == NORMAL)){
                printf("\033[31m X ");
                printf("\033[0m|");}
            else if ((Board[i][j].state == FULL) && ((Board[i][j].checkers).colour == BLUE) && ((Board[i][j].checkers).type == NORMAL)){
                printf("\033[36m O ");
                printf("\033[0m|");}
            else
                printf("   |");
        }
        printf("\n");
    }
    for (int k = 0; k < SIZE + 1; k++)
    {
        if (k == 0)
            printf("   ");
        else
            printf("----");
    }
    printf("\n");
    printf("   ");

    for (int i = 0; i < SIZE; i++)
    {
        printf("  %c ", 'A' + i);
    }
    printf("\n");
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
                    if ((Board[b - 1][a - 1].checkers).colour == BLUE || (Board[b - 1][a- 1].checkers).colour == NOCOLOUR)
                        return 0;
                }

                if (c == a + 2)
                {

                    if ((Board[b - 1][a+1].checkers).colour == BLUE || (Board[b - 1][a + 1].checkers).colour == NOCOLOUR)
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
                    if ((Board[b- 1][a - 1].checkers).colour == BLUE || (Board[b - 1][a - 1].checkers).colour == NOCOLOUR)

                        return 0;
                }

                if (c == a + 2)
                {
                    if ((Board[b-1][a + 1].checkers).colour == BLUE || (Board[b - 1][a +1].checkers).colour == NOCOLOUR)
                        return 0;
                }
            }

            if (d == b + 2)
            {
                if (c == a - 2)
                {

                    if ((Board[b+ 1][a - 1].checkers).colour == BLUE || (Board[b+ 1][a - 1].checkers).colour == NOCOLOUR)
                        return 0;
                }

                if (c == a + 2)
                {
                    if ((Board[b+ 1][a + 1].checkers).colour == BLUE || (Board[b + 1][a+ 1].checkers).colour == NOCOLOUR)

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

                    if ((Board[b+1][a-1].checkers).colour == RED || (Board[b+1][a-1].checkers).colour == NOCOLOUR)

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

                    if ((Board[b - 1][a + 1].checkers).colour == RED || (Board[b- 1][a + 1].checkers).colour == NOCOLOUR)

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

    int ans = isvalid(Board, turn, Y1, c1.x, Y2, c2.x);

    if (ans == 0)
    {
        return 0;
    }
    else
    {   
        // Player - X
        if (turn == 'X')
        {   
            // Change the current piece features
            Board[c2.x - 1][c2.y].state = FULL;
            Board[c2.x - 1][c2.y].checkers.colour = RED;
            Board[c2.x - 1][c2.y].checkers.type = NORMAL;
        }

        // Player - O
        else
        {   
            // Change the current piece features
            Board[c2.x - 1][c2.y].state = FULL;
            Board[c2.x - 1][c2.y].checkers.colour = BLUE;
            Board[c2.x - 1][c2.y].checkers.type = NORMAL;    
        }

        // Update the previous piece features
        Board[c1.x - 1][c1.y].state = EMPTY;
        Board[c1.x - 1][c1.y].checkers.colour = NOCOLOUR;
        Board[c1.x - 1][c1.y].checkers.type = NOPEICE;

    }
    return 1;
}
