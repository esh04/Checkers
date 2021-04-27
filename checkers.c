#include "checkers.h"



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
                Board[i][j + 1].state = FULL;
                (Board[i][j + 1].checkers).colour = RED;
                (Board[i][j + 1].checkers).type = NORMAL;

                Board[SIZE - 1 - i][j + 1].state = FULL;
                (Board[SIZE - 1 - i][j + 1].checkers).colour = BLUE;
                (Board[SIZE - 1 - i][j + 1].checkers).type = NORMAL;
            }
            else
            {
                Board[i][j].state = FULL;
                (Board[i][j].checkers).colour = RED;
                (Board[i][j].checkers).type = NORMAL;

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

            if ((Board[i][j].state == FULL) && ((Board[i][j].checkers).colour == RED) && ((Board[i][j].checkers).type == NORMAL))
                printf(" %c |", 'X');
            else if ((Board[i][j].state == FULL) && ((Board[i][j].checkers).colour == BLUE) && ((Board[i][j].checkers).type == NORMAL))
                printf(" %c |", 'O');
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

void movements(checkersGrid Board[][SIZE], int turn, coordinates c1, coordinates c2)
{

    //Condition -1(coordinates remain within the array && the final coordinates should be diagonal)
    if (c2.x >= 1 && c2.x <= SIZE && c1.y >= 0 && c1.y <= SIZE - 1)
    {
        // Condition-2 (final coordinates should be empty)
        if (Board[c2.x - 1][c2.y].state == EMPTY)
        {
            // Check for turn - turn =0 for player -1
            if (turn == 0)
            {
                Board[c2.x - 1][c2.y].state = FULL;
                Board[c2.x - 1][c2.y].checkers.colour = RED;
                Board[c2.x - 1][c2.y].checkers.type = NORMAL;
            }
            else
            {
                Board[c2.x - 1][c2.y].state = FULL;
                Board[c2.x - 1][c2.y].checkers.colour = BLUE;
                Board[c2.x - 1][c2.y].checkers.type = NORMAL;
            }
            Board[c1.x - 1][c1.y].state = EMPTY;
            Board[c1.x - 1][c1.y].checkers.colour = NOCOLOUR;
            Board[c1.x - 1][c1.y].checkers.type = NOPEICE;
        }
        else
        {
            printf("Invalid move");
        }
    }
    else
    {
        printf("Invalid move");
    }
}

