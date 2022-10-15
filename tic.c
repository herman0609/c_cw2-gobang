/************************************************************************
University of Leeds
School of Computing
COMP1711/XJCO1711- Procedural Programming
Coursework 2

I confirm that the following code has been developed and written by me and it is entirely the result of my own work.
I also confirm that I have not copied any parts of this program from another person or any other source or facilitated someone to copy this program from me.
I confirm that I will not publish the program online or share it with anyone without permission of the module leader.

Student Name: Sun Hang
Student ID: 2020110158
Email: el20hs@leeds.ac.uk
Date Work Commenced:2021/11/12
*************************************************************************/


// ********************************************************************************************************************
// DO NOT CHANGE ANYTHING IN THE FOLLOWING SECTION. IF YOU CHANGE ANYTHING, YOUR CODE WILL FAIL THE AUTOGRADER TESTS.
// However, please read through this section and look at the array declaration and other functions that you will use in your code

#include <stdio.h>
#include <stdlib.h>
#include "tic.h"

// use this 2d array to store the moves of the game, please don't change its name or size
char grid[MaxGrid][MaxGrid]; // this is the grid that will be used to store the moves of the game

int __Check_Count; // do not use this variable, it is for the grader only

// USE THE FOLLOWING FUNCTIONS TO DISPLAY THE CORRECT PROMPTS AND MESSAGES WHEN YOU NEED THEM
// IN YOUR CODE. THIS WILL GUARANTEE THAT YOU PROGRAM'S OUTPUT MATCHES MINE AND FACILITATE AUTOGRADING

// please use this function to prompt the user to enter the grid size to start a new game
void promptEnterGridSize ()
{
    printf ("Enter grid size (3-10):");
}

// please use this function to prompt the user to enter the winning length for the new game
// the parameter represents the maximum winning length for this game
void promptEnterWinLength (int max_win_length)
{
    printf ("Enter winning length (3-%i):", max_win_length);
}

// please use this function to prompt the user to enter the location of the symbol
// this function takes as a parameter the symbol of the player to be prompted
void promptChooseLocation (char symbol)
{
    printf ("Player %c, Choose Location (row,col): ", symbol);
}

// please use this function to show an error message when an index is out of range
void showErrIndex ()
{
    printf ("Index out of range, please re-enter\n");
}

// please use this function to show an error message when a location is already taken
void showErrTaken ()
{
    printf ("This location is already taken\n");
}

// please use this function to show the win message at the end of the game
// this function takes as parameter the symbol of the player who won the game
void showWinMessage (char symbol)
{
    printf ("**************************\n");
    printf ("Player %c has won the game\n", symbol);
    printf ("**************************\n");
}

// please use this function to show a game over (draw) message at the end of the game
void showGameOverMessage ()
{
    printf ("Game over; there are no winners\n");
}

//  please use this function to prompt the user to choose if they want to play back the game (at the end of the game)
void promptPlayBackGame ()
{
    printf ("\nWould you like to play back the recorded game? (y,n)?");
}

// please use this function to prompt the user to answer with n (next) or e (exit)
// to indicate if they want to proceed with the game's replay or exit the program
void promptNextOrExit ()
{
    printf ("Next or Exit (n,e)?");
}

// You will use this function in effPlayerHasWon (see below).
// This function is basically a wrapper around an if statement to compare the content of the cell at row,col with symbol
// However, it also counts the number of times the function is called
// Needless to say again, don't change this function
int check (int row, int col, char symbol)
{
    __Check_Count++;
    if (grid[row][col] == symbol)
        return 1;
    return 0;
}

// Used by the grader to peek at a certain cell in the grid. Don't use this function
int peek (int row, int col)
{
    return grid[row][col];
}


// END OF CODE SECTION THAT SHOULD NOT BE CHANGED
// ************************************************

// --------------------------------------------------------------------------------------------------
// NOW IT IS YOUR TURN, YOU CAN DEFINE ANY OTHER GLOBAL VARIABLES YOU MAY NEED IN YOUR CODE BELOW THIS LINE
int size;
int length;
int sh[100][2];
int length1;
char reply;
char answer;
int count_col = 0;
int count_row = 0;
int count_dia = 0;
int count_anti = 0;
int row_o, col_o;
int row_x, col_x;

// END OF SECTION FOR DECLARRING ADDITIONAL GLOBAL VARIABLES
// ----------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// NOW, IMPLEMENT THE FOLLOWING FUNCTIONS BY WRITING THE CORRECT CODE IN THE BODIES OF THE FUNCTIONS
// please, don't change the functions' name, return type, or parameters. If you change any of these the grader will crash
// initially these functions contain 'return -99'. Before implementing a function you should delete this statement

// The purpose of this function is to to start a new game
// It is used to initialise everything at the start of a new game
// This functions takes two integer parameters:
// The first parameter (gridsize) represents the size of the grid of the new game, .e.g. 3 for 3x3 game
// The minimum size of the grid is 3 and the maximum size is 10, if the value of the parameter is wrong (less than 3 or > 10)
// the function returns 0 indicating failure to start a new game.
// The second parameter (winlength) is the number of consecutive symbols for the winning case.
// This number cannot be less than 3 or > gridsize (why?), think but don't click :-)
// If the value of the second parameter is invalid (<3 or >gridsize) the function returns 0 (failure)
// If everything is correct the function returns 1 indicating success in initialising the game.
int newGame (int gridsize, int winlength)
{
    size = gridsize;
    length = winlength;
    if(length < 3 || length > size)
    {
        return 0;
    }
    if(size < 3 || size > 10 )
    {
        return 0;
    }
    int sh;
    int nb;
    for(sh = 0; sh < size; sh++)
    {
        for (nb = 0; nb < size; nb++)
            grid[sh][nb] = '.';
    }
    return 1;
}

// The purpose of this function is to show the game's grid on the screen
// The grid should exactly look like the examples in the assignment specification
// Please note the following when you implement the function:
// There is one empty line before the grid to make it stand out from text before it
// The column indices are printed at the top and the first one is indented by exactly one tab (\t); indices are separated by exactly one space
// The row indices are printed at the left followed by exactly one tab (\t)
// The grid symbols are separated by exactly one space
// There is one empty line after the grid to make it stand out from text after it
void showGrid ()
{
    printf("\n");
    printf("\t");
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%i ",i);
    }
    printf("\n");
    int sh;
    int nb;
    for(sh = 0; sh < size; sh++)
    {
        printf("%i", sh);
        printf("\t");
        for (nb = 0; nb < size; nb++)
        {
            printf("%c", grid[sh][nb]);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

// The purpose of this function is to make a move by a player.
// Making a move means putting the player's symbol (letter) in the desired cell
// This function takes 3 parameters. The first two represent indices of the row and column of the cell in which the player
// wants to place their symbol.
// The last parameter is the symbol (letter) of that player.
// A move can only be made if:
// 1- The row and column numbers are valid (not less than 0 or greater than the game's grid size), and
// 2- the cell is not already occupied by another symbol, and
// 3- the symbol is a valid one (X or O).
// If the move can be made (because it is valid), the function makes the move (i.e. puts the symbol in the cell) and returns 1 indicating success.
// otherwise the function returns 0 indicating failure to make the move
// my solution is 4 lines only
int makeMove(int row, int col, char symbol)
{
    if (row < 0 || row > size){
        return 0;}
    else if (col < 0 || col > size){
        return 0;}
    else if (grid[row][col] == 'X' || grid[row][col] == 'O'){
        return 0;}
    else
    {
        grid[row][col] = symbol;
        return 1;
    }
}

// This function is used to check if the board is full, i.e. every location in the grid is filled with either X or O
// it returns 1 if the grid is full, 0 otherwise
// my solution is 5 lines
int boardIsFull()
{
    int sh;
    int nb;
    for(sh = 0; sh < size; sh++)
    {
        for(nb = 0; nb < size; nb++)
        {
            if (grid[sh][nb] == '.')
                return 0;
        }
    }
    return 1;
}


// This function is used to check if there is any horizontal line in the grid that contains a consecutive sequence of the same symbol
// It can be used to check that a player has won the game by forming a horizontal run of their own symbol
// The function returns 1 if the player given by parameter symbol has formed a horizontal line of the required length otherwise it returns 0
// The first parameter is the player's symbol (X or O), and the second parameter is the required length (number of cells) of consecutive symbols
// If any of the parameters is invalid the function should return -1 indicating failure to make a move

int checkHorizontal (char symbol, int length)
{
    int sum = 0;
    if(symbol != 'X' && symbol != 'O'){
        return -1;}
    
    if(length < 3 || length > size){
        return -1;}
    int i;
    int j;
    for(i = 0; i < size; i++)
        {
            for(j = 0; j < size; j++)
                {
                    if(grid[i][j] == symbol)
                        {
                            sum++;
                            if(sum == length)
                                {
                                    return 1;
                                }
                        }
                    else
                        {
                        sum = 0;
                        }
                }
            sum = 0;
        }
    return 0;
}


// This function is used to check if there is any vertical line in the grid that contains a consecutive sequence of the same symbol
// It can be used to check that a player has won the game by forming a vertical run of their own symbol
// The function returns 1 if the player given by parameter symbol has formed a vertical line of the required length otherwise it returns 0
// The first parameter is the player's symbol (X or O), and the second parameter is the required length (number of cells) of consecutive symbols
// If any of the parameters is invalid the function should return -1 indicating failure to make a move
int checkVertical (char symbol, int length)
{
    int sum0 = 0;

    if(length < 3 || length > size){
        return -1;}
    int i;
    int j;
    for(j = 0; j < size; j++)
    {
        for(i = 0; i < size; i++)
        {
            if(grid[i][j] == symbol)
            {
                sum0++;
                if(sum0 == length)
                {
                    return 1;
                }
            }
            else
            {
            sum0 = 0;
            }
        }
        sum0 = 0;
    }
    return 0;
}

// This function is used to check if there is any diagonal line in the grid that contains a consecutive sequence of the same symbol
// A diagonal line runs from higher left to lower right (or vice versa). Note that there are more than one diagonal line in a grid.
// It can be used to check that a player has won the game by forming a diagonal run of their own symbol
// The function returns 1 if the player given by parameter symbol has formed a diagonal line of the required length otherwise it returns 0
// The first parameter is the player's symbol (X or O), and the second parameter is the required length (number of cells) of consecutive symbols
// If any of the parameters is invalid the function should return -1 indicating failure to make a move
int checkDiagonals (char symbol, int length)
{
    int sum;
    int s;
    int h;
    if (length < 3 || length > size){
        return -1;
    }
    int i;
    int j;
    int k;
    if (symbol == 'X' || symbol == 'O') {
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                sum = 0;
                s = i;
                h = j;
                for (k = 0; k < length; k++) {
                    if (s < size && h < size) {
                        if (grid[s][h] == symbol) {
                            sum++;
                            s++;
                            h++;
                        }
                        if (sum == length) {
                            return 1;
                        }
                    }
                }
            }
        }
        return 0;
    }
    else{
        return -1;
    }
}

// This function is used to check if there is any anti-diagonal (reverse diagonal) section in the grid that contains a consecutive sequence of the same symbol
// An anti-diagonal line runs from higher right to lower left (or vice versa). Note that there are more than one anti-diagonal line in a grid.
// It can be used to check that a player has won the game by forming an anti-diagonal run of their own symbol
// The function returns 1 if the player given by parameter symbol has formed an anti-diagonal line of the required length otherwise it returns 0
// The first parameter is the player's symbol (X or O), and the second parameter is the required length (number of cells) of consecutive symbols
// If any of the parameters is invalid the function should return -1 indicating an failure to make a move
int checkAntiDiagonals (char symbol, int length)
{       
    int sum;
    int s;
    int h;
    if (length < 3 || length > size){
        return -1;
    }
    int i;
    int j;
    int k;
    if (symbol == 'X' || symbol == 'O') {
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                sum = 0;
                s = i;
                h = j;
                for (k = 0; k < length; k++) {
                    if (s < size && h > -1) {
                        if (grid[s][h] == symbol) {
                            sum++;
                            s++;
                            h--;
                        }
                        if (sum == length) {
                            return 1;
                        }
                    }
                }
            }
        }
        return 0;
    }
    else{
        return -1;
    }
}


// This function is used to check if a player has won the game by forming a horizontal, vertical, diagonal, or anti-diagonal line
// of the required length. This function should use the above four functions (checkHorizontal, checkVertical, checkDiagonals, and checkAntiDiagonals)
// to determine if the player has one
// The function returns 1 if the player given by symbol has won, and 0 if the player has not won
// If any of the parameters is invalid the function returns -1 indicating failure to check
// my solution is 5 lines
int playerHasWon (char symbol , int length)
{
    if (symbol == 'X' || symbol == 'O') {
        if(checkHorizontal(symbol, length) || checkVertical(symbol, length) || checkDiagonals(symbol, length) || checkAntiDiagonals(symbol, length)){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return -1;
    }
}

// Do you think the above function (playerHasWon) is the most efficient way of detecting a win?
// Do we do this as humans when we play the game?
// The answer is NO.
// The purpose of this function is to implement a much more efficient version of the playerHasWon function
// The function takes four parameters.
// The first two parameters represent the location (row, and col) of the last move made
// by a player.
// The second parameter is the symbol of that player.
// The last parameter is the length of the winning line
// We will assess the efficiency of the function by the number of times we need to check the contents of a cell.
// To count the number of checks, I have prepared a function called check - see the top of this file - that you have
// to use instead of an if statement when you need to compare the contents of a cell to a given symbol.
//
// This function returns 1 if the player has formed a winning line immediately after placing their symbol in the
// cell given by row,col. If the player did not win, the function returns 0
// It returns -1 if any of the parameters have an invalid value.
int effPlayerHasWon (int row, int col, char symbol , int length)
{
    if(symbol != 'X' && symbol != 'O')
        return -1;
    int count_pai = 0;
    int count_lie = 0;
    int count_dia = 0;
    int count_anti = 0;
    int cola = col;
    int colb = col + 1;
    while(cola >= 0)
        {
            if(check(row, cola, symbol))
                {
                    count_lie++;
                    cola--;
                    if(count_lie == length)
                        return 1;
                }
            else
                break;
        }
    while( colb < size)
        {
            if(check(row, colb, symbol))
                {
                    count_lie++;
                    colb++;
                    if(count_lie == length)
                        return 1;
                }
            else
                break;
        }
    
    
    int rowa = row;
    int rowb = row + 1;
    while(rowa >= 0)
        {
            if(check(rowa, col, symbol))
                {
                    count_pai++;
                    rowa--;
                    if(count_pai == length)
                        return 1;
                }
            else
                break;
        }
    while(rowb < size)
        {
            if(check(rowb, col, symbol))
                {
                    count_pai++;
                    rowb++;
                    if(count_pai == length)
                        return 1;
                }
            else
                break;
        }
    
    
    int rowc = row;
    int colc = col;
    int rowd = row + 1;
    int cold = col + 1;
    while(rowc >= 0 && colc >= 0)
        {
            if(check(rowc, colc, symbol))
                {
                    count_dia++;
                    rowc--;
                    colc--;
                    if(count_dia == length)
                        return 1;
                }
            else
                break;
        }
    while(rowd < size && cold < size)
        {
            if(check(rowd, cold, symbol))
                {
                    count_dia++;
                    rowd++;
                    cold++;
                    if(count_dia == length)
                        return 1;
                }
            else
                break;
        }
    
    
    int rowe = row;
    int cole = col;
    int rowf = row + 1;
    int colf = col - 1;
    while( rowe >= 0 && cole < size )
        {
            if(check(rowe, cole, symbol))
                {
                    count_anti++;
                    rowe--;
                    cole++;
                    if(count_anti == length)
                        return 1;
                }
            else
                break;
        }
    while(rowf < size && colf >= 0)
        {
            if(check(rowf, colf, symbol))
                {
                    count_anti++;
                    rowf++;
                    colf--;
                    if(count_anti == length)
                        return 1;
                }
            else
                break;
        }
    return 0;
}
// IF YOU NEED ADDITIONAL FUNCTIONS YOU CAN DEFINE THEM BELOW THIS LINE
//----------------------------------------------------------------------
void replay_game (int i, int j,char symbol)
{
    grid[i][j] = symbol;
}

// DON'T CHANGE THE FOLLOWING 3 LINES
#ifndef TEST
int main (int argc, char* argv[])
{
    // ENTER THE CODE OF YOUR main FUNCTION BELOW
    promptEnterGridSize();
    scanf("%i", &size);

    while (size < 3 || size > 10)
     {
       showErrIndex();
       promptEnterGridSize();
       scanf("%i", &size);
     }

    promptEnterWinLength (size);
    scanf("%i", &length);

    while (length < 3 || length > size)
     {
       showErrIndex();
       promptEnterWinLength (size);
       scanf("%i", &length);
     }

    newGame(size, length);
    showGrid();

    while (1){
        promptChooseLocation('X');
        scanf("%i,%i", &row_x, &col_x);


        while (row_x >= size || col_x >= size)
        {
            showErrIndex();
            promptChooseLocation('X');
            scanf("%i,%i", &row_x, &col_x);
        }
        
        if (grid[row_x][col_x] !='.')
        {
            showErrTaken();
            promptChooseLocation('X');
            scanf("%i,%i", &row_x, &col_x);
        }


        sh[length1][0] = row_x;
        sh[length1][1] = col_x;
        length1 ++;

        makeMove(row_x, col_x, 'X');
        showGrid();
        
        if (playerHasWon('X', length))
        {
            showWinMessage('X');
            break;
        }
        
        if (boardIsFull())
        {
            showGameOverMessage();
            break;
        }
        

        promptChooseLocation('O');
        scanf("%i,%i", &row_o, &col_o);

        while (row_o >= size || col_o >= size)
        {
            showErrIndex();
            promptChooseLocation('O');
            scanf("%i,%i", &row_o, &col_o);
        }

        if (grid[row_o][col_o] !='.')
        {
            showErrTaken();
            promptChooseLocation('O');
            scanf("%i,%i", &row_o, &col_o);
        }


        sh[length1][0] = row_o;
        sh[length1][1] = col_o;
        length1 ++;
        makeMove(row_o, col_o, 'O');
        showGrid();

        if (playerHasWon('O', length))
        {
            showWinMessage('O');
            break;
        }

        if (boardIsFull())
        {
            showGameOverMessage();
            break;
        }
        }

    promptPlayBackGame();
    scanf(" %c", &reply);

    if (reply == 'y')
    {
        int i;
        int j;
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
                grid[i][j] = '.';
        }

        int sum = 0;

        replay_game(sh[sum][0], sh[sum][1], 'X');
        showGrid();
        sum += 1;
        int hg;
        for (hg = 1; hg < length1; hg++)
        {
            promptNextOrExit();
            scanf(" %c", &answer);
            if (answer == 'n')
                {
                    if (sum % 2 == 1)
                        {
                            replay_game(sh[sum][0], sh[sum][1], 'O');
                            showGrid();
                            sum += 1;
                        }
                    
                    else
                        {
                            replay_game(sh[sum][0], sh[sum][1], 'X');
                            showGrid();
                            sum += 1;
                        }
                }
            
            else if (answer == 'e'){
                break;}
        }
        promptNextOrExit();
    }

// DON'T CHANGE THE FOLLOWING 3 LINES
    return 0;
}
#endif
// DON'T WRITE ANYTHING BELOW THIS LINE
