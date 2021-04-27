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
