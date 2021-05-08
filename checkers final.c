#include "checkers final.h"

// initialises the board and sets the peices
void initBoard(checkersGrid Board[][SIZE])
{
    // create empty board
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            Board[i][j].state = EMPTY;
            Board[i][j].checkers.colour = NOCOLOUR;
            Board[i][j].checkers.type = NOPEICE;
        }
    }
    // place the red and blue peices
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < SIZE; j = j + 2)
        {
            if (i == 1)
            {
                // fills the 2nd row
                Board[i][j].state = FULL;
                Board[i][j].checkers.colour = RED;
                Board[i][j].checkers.type = NORMAL;
                // fills the 7th row
                Board[SIZE - 1 - i][j + 1].state = FULL;
                Board[SIZE - 1 - i][j + 1].checkers.colour = BLUE;
                Board[SIZE - 1 - i][j + 1].checkers.type = NORMAL;
            }
            else
            {
                // fills the 1st and 3rd row
                Board[i][j + 1].state = FULL;
                Board[i][j + 1].checkers.colour = RED;
                Board[i][j + 1].checkers.type = NORMAL;
                // fills the 6th and 8th row
                Board[SIZE - 1 - i][j].state = FULL;
                Board[SIZE - 1 - i][j].checkers.colour = BLUE;
                Board[SIZE - 1 - i][j].checkers.type = NORMAL;
            }
        }
    }
}

// prints the board in the current state
void printBoard(checkersGrid Board[][SIZE])
{
    // printing rows
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
        // prints the row coordinates
        printf("%d  |", i + 1);
        // printing coloumns
        for (int j = 0; j < SIZE; j++)
        {
            if (Board[i][j].checkers.colour == RED)
            {
                // \033[31m \033[0m| gives X red colour
                if (Board[i][j].checkers.type == NORMAL)
                {
                    printf("\033[31m X ");
                    printf("\033[0m|");
                }
                else
                {
                    printf("\033[31m X* ");
                    printf("\033[0m|");
                }
            }
            else if (Board[i][j].checkers.colour == BLUE)
            {
                // \033[36m \033[0m| gives O blue colour
                if (Board[i][j].checkers.type == NORMAL)
                {
                    printf("\033[31m O ");
                    printf("\033[0m|");
                }
                else
                {
                    printf("\033[31m O* ");
                    printf("\033[0m|");
                }
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

    // prints the coloumn coordinates
    for (int i = 0; i < SIZE; i++)
    {
        printf("  %c ", 'A' + i);
    }
    printf("\n");
}

// checks if the move being made is valid or not
// return 2 if it is a capture move
// returns 0 if it is invalid
// returns 1 is it a simple diagnol move
int isValid(checkersGrid Board[][SIZE], char turn, coordinates start, coordinates end)
{
    // checks for turn; if m == 1 it is X's turn, else it is O's turn
    int m = 1;
    if (turn == 'O')
        m = 0;

    // shifts the index from (1 to 8) to (0 to 7)
    start.x--;
    end.x--;
    // shifts the index from (65 to 72) to (0 to 7)
    start.y -= 65;
    end.y -= 65;
    // checks if the coordinates entered are not beyond the scope of the board
    if (start.x < 0 || start.x > 7 || start.y < 0 || start.y > 7 ||
        end.x < 0 || end.x > 7 || end.y < 0 || end.y > 7)
        return 0;
    // stores the absolute difference of x and y coordinates respectively
    int diff_x = abs(start.x - end.x);
    int diff_y = abs(start.y - end.y);
    // since moves are always diagnol diff_x should always be equal to diff_y
    // and never more than 2 since that is the max a checker can move
    if (diff_x != diff_y || diff_x > 2 || diff_y > 2)
        return 0;
    // verifies if there is a peice at start and no peice at end; if false returns 0
    if (Board[start.x][start.y].state == EMPTY || Board[end.x][end.y].state != EMPTY)
        return 0;
    // if it is X's turn
    if (m == 1)
    {
        // if the start position contains a blue piece it can't be moved by when O has to play
        if (Board[start.x][start.y].checkers.colour == BLUE)
            return 0;
        if (Board[start.x][start.y].checkers.type == NORMAL)
        {
            // normal X checkers can't move back
            if (end.x == start.x - 1 || end.x == start.x - 2)
                return 0;
        }
        if (diff_x == 1)
            return 1;
        // if normal or king X checker moves diagonally by one space the programs returns true
        // since all conditions are satisfied for it to be valid, we thus check for capture now
        // we check for forward movemnt irrespectove of whether if is king or normal peice since
        // both can move forward (by forward we mean from 1 towards 8)
        if (end.x == start.x + 2)
        {
            // if it moves diagnolly to the left
            if (end.y == start.y - 2)
            {
                // in a capture, an opposite checker is supposed to be in middle of start and end
                // we check for this condition if not satisfied return 0
                if (Board[start.x + 1][start.y - 1].checkers.colour == BLUE)
                    ;
                else
                    return 0;
            }
            // if it moves diagnolly to the right
            if (end.y == start.y + 2)
            {
                // we check for an opposite checker in the middle
                if (Board[start.x + 1][start.y + 1].checkers.colour == BLUE)
                    ;
                else
                    return 0;
            }
        }
        // we check valid moves for king
        // we check backward capture movement for king specifically
        // (by backward we mean from 8 to 1)
        if (Board[start.x][start.y].checkers.type == KING)
        {
            // backward capture
            if (end.x == start.x - 2)
            {
                // if it moves diagnolly to the left
                if (end.y == start.y - 2)
                {
                    // in a capture, an opposite checker is supposed to be in middle of start and end
                    // we check for this condition if not satisfied return 0
                    if (Board[start.x - 1][start.y - 1].checkers.colour == BLUE)
                        ;
                    else
                        return 0;
                }
                // if it moves diagnolly to the right
                if (end.y == start.y + 2)
                {
                    // we check for an opposite checker in the middle
                    if (Board[start.x + 1][start.y + 1].checkers.colour == BLUE)
                        ;
                    else
                        return 0;
                }
            }
        }
    }
    // if it is O's turn
    else
    {
        // if the start position contains a red piece it can't be moved by when O has to play
        if (Board[start.x][start.y].checkers.colour == RED)
            return 0;
        if (Board[start.x][start.y].checkers.type == NORMAL)
        {
            // normal O checkers can't move backwards (by backward we mean from 8 towards 1)
            if (end.x == start.x + 1 || end.x == start.x + 2)
                return 0;
        }
        if (diff_x == 1)
            return 1;
        // if normal or king X checker moves diagonally by one space the programs returns true
        // since all conditions are satisfied for it to be valid, we thus check for capture now
        // we check for backward movemnt irrespectove of whether if is king or normal peice since
        // both can move backward
        if (end.x == start.x - 2)
        {
            // if it moves diagnolly to the left
            if (end.y == start.y - 2)
            {
                // in a capture, an opposite checker is supposed to be in middle of start and end
                // we check for this condition if not satisfied return 0
                if (Board[start.x - 1][start.y - 1].checkers.colour == RED)
                    ;
                else
                    return 0;
            }
            // if it moves diagnolly to the right
            if (end.y == start.y + 2)
            {
                // we check for an opposite checker in the middle
                if (Board[start.x - 1][start.y + 1].checkers.colour == RED)
                    ;
                else
                    return 0;
            }
        }
        // we check valid moves for king
        // we check forward capture movement for king specifically
        if (Board[start.x][start.y].checkers.type == KING)
        {
            // backward capture
            if (end.x == start.x + 2)
            {
                // if it moves diagnolly to the left
                if (end.y == start.y - 2)
                {
                    // in a capture, an opposite checker is supposed to be in middle of start and end
                    // we check for this condition if not satisfied return 0
                    if (Board[start.x - 1][start.y - 1].checkers.colour == RED)
                        ;
                    else
                        return 0;
                }
                // if it moves diagnolly to the right
                if (end.y == start.y + 2)
                {
                    // we check for an opposite checker in the middle
                    if (Board[start.x + 1][start.y + 1].checkers.colour == RED)
                        ;
                    else
                        return 0;
                }
            }
        }
    }
    return 2;
}

// Introduces the game in the start
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
    printf("\n\n\nInstructions to play the game are specified as you move forward in the game\n");
    printf("Enjoy the game!!\n");
    printf("\n\n\n\n Press any key to continue..");
}
