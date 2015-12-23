#include "stdafx.h"
#include <iostream>
#include <string> // For the player names

#include "TicTacToe.h" // Includes player enums

/* Returns the index of a multi-dimensional array [rowToCheck][columnToCheck] 
 * to a single dimensional array
 * example: [0][1] of an array with 4 elements (2x2), would be:
 *          (0 * 2) + 1 = index of 3, which would point to the 2nd element!
 */
int convertMultiToSingleDimension(int amountOfColumns, int rowToCheck, int columnToCheck)
{
    return (rowToCheck * amountOfColumns) + columnToCheck;
}

// Draw the tictactoe board, with included whitespace, X's and O's
void drawBoard(char *board, int amountOfRows, int amountOfColumns)
{
    using std::cout;
    int currentElement = 0;
    for (int row = 0; row < amountOfRows; ++row)
    {
        for (int column = 0; column < amountOfColumns; ++column)
        {
            // Only display a number if there is nothing already there, such as an 'X'
            if (board[currentElement] != 'X' && board[currentElement] != 'O')
            {
                cout << ((currentElement++) + 1);
            }
            else
            {
                //we output the current element before increasing the index
                cout << board[currentElement++];
            }

            // We don't add a spacer after the last element in each row
            if (column != (amountOfColumns - 1))
            {
                cout << '|';
            }
        }
        cout << "\n";
    }
}

// Asks a player where they wish to place his/her's symbol 
void placeSymbol(char *board, int amountOfRows, int amountOfColumns, players::Players currentPlayer)
{
    using namespace std;

    int indexOfArray{ 0 };
    char elementInArray = 0;
    bool continueLoop = true;

    do
    {
        cout << "Which spot would you like to place your marker in: ";
        short spotToPlaceIn;
        cin >> spotToPlaceIn;

        // Converts the single dimensional index they picked to
        // a multiple dimensional index to be used throughout the program
        short row{ 0 };
        short column{ 0 };
        int currentElement{ 0 };
        for (int currentRow = 0; currentRow < amountOfRows; ++currentRow)
        {
            for (int correntColumn = 0; correntColumn < amountOfColumns; ++correntColumn)
            {
                // We subtract spotToPlaceIn on account arrays start with 0 not 1
                // check currentElement before we increase
                if ((spotToPlaceIn - 1) == currentElement++)
                {
                    row = currentRow;
                    column = correntColumn;
                    break;
                }
            }
        }

        // Check to see if the selection is not out of bounds
        if (row < amountOfRows && column < amountOfColumns)
        {
            indexOfArray = convertMultiToSingleDimension(amountOfColumns, row, column);
            elementInArray = board[indexOfArray];
            continueLoop = false;
            if (elementInArray == 'X' || elementInArray == 'O')
            {
                cout << "Space already taken\n";
                continueLoop = true;
            }
        }
        else
        {
            continueLoop = true;
            cout << "Out of bounds\n";
        }
    } 
    while (continueLoop);
 
    board[indexOfArray] = playerToSymbol(currentPlayer);
}

// Checks rows for any winning conditions, such as X X X or O O O
bool checkRows(char *board, int amountOfRows, int amountOfColumns, players::Players currentPlayer)
{
    for (int row = 0; row < amountOfRows; ++row)
    {
        int amountOfWinningCharacters{ 0 };
        for (int column = 0; column < amountOfColumns; ++column)
        {
            int indexOfCurrentElement = convertMultiToSingleDimension(amountOfColumns, row, column);

            if (board[indexOfCurrentElement] == playerToSymbol(currentPlayer))
                ++amountOfWinningCharacters;
        }
        // We check columns on account a row is located on seperate columns rows are NOT on rows
        if (amountOfWinningCharacters == amountOfColumns)
            return true;
    }
    return false;
}

// Checks columns for any winning conditions
bool checkColumns(char *board, int amountOfRows, int amountOfColumns, players::Players currentPlayer)
{
    for (int column = 0; column < amountOfColumns; ++column)
    {
        int amountOfWinningCharacters{ 0 };
        for (int row = 0; row < amountOfRows; ++row)
        {
            int indexOfCurrentElement = convertMultiToSingleDimension(amountOfColumns, row, column);

            if (board[indexOfCurrentElement] == playerToSymbol(currentPlayer))
                ++amountOfWinningCharacters;
        }
        // We check rows on account a row is located on seperate rows 
        // columns are NOT on columns
        if (amountOfWinningCharacters == amountOfRows)
            return true;
    }
    return false;
}

// Checks diagonals for any winning conditions
bool checkDiagonals(char *board, int amountOfRows, int amountOfColumns, players::Players currentPlayer)
{
    // 0,0 | 0,1 | 0,2
    // 1,0 | 1,1 | 1,2
    // 2,0 | 2,1 | 2,2

    //Check the left diagonal  '\'
    // Move the direction of the check from the top left to the bottom right
    bool gameIsOver = false;
    for (int row = 0, column = 0; row < amountOfRows; ++row, ++column)
    {
        int indexOfCurrentElement = convertMultiToSingleDimension(amountOfColumns, row, column);
        if (board[indexOfCurrentElement] != playerToSymbol(currentPlayer))
        {
            gameIsOver = false;
            break;
        }
        else
        {
            gameIsOver = true;
        }
    }
    // No need to go through the other diagonal if we have already found an acceptable winning condition
    if (gameIsOver)
    {
        return gameIsOver;
    }

    // Check the right diagonal '/'
    // Move the direction of the check from the bottom left to the top right
    for (int row = 2, column = 0; column < amountOfColumns; --row, ++column)
    {
        int indexOfCurrentElement = convertMultiToSingleDimension(amountOfColumns, row, column);
        if (board[indexOfCurrentElement] != playerToSymbol(currentPlayer))
        {
            gameIsOver = false;
            break;
        }
        else
        {
            gameIsOver = true;
        }
    }

    if (gameIsOver)
    {
        return gameIsOver;
    }
    else
    {
        // If no acceptable winning conditions are found, return false
        return false;
    }
}

/* Used as a medium for the three functions above, also handles whether to check for
 * diagonals or not.
 */
bool checkWinningCondition(char *board, int amountOfRows, int amountOfColumns, players::Players currentPlayer)
{
    bool diagonalWithWinningCondition = false;

    bool rowWithWinningCondition = checkRows(board, amountOfRows, amountOfColumns, currentPlayer);
    bool columnWithWinningCondition = checkColumns(board, amountOfRows, amountOfColumns, currentPlayer);

    // Only check for diagonals if the board has equal amount of rows and columns
    if (!(amountOfRows % amountOfColumns))
        diagonalWithWinningCondition = checkDiagonals(board, amountOfRows, amountOfColumns, currentPlayer);

    if (rowWithWinningCondition || columnWithWinningCondition || diagonalWithWinningCondition)
    {
        std::cout << playerToPlayerName(currentPlayer) << " is the winner!\n";
        return true;
    }
    else
    {
        return false;
    }
}

// Asks players if they wish to play again, return TRUE if they do, if not return FALSE
bool requestReplay()
{
    std::cout << "Would you like to play again? Y/N";

    char playerOption;
    std::cin >> playerOption;

    if (playerOption == 'Y' || playerOption == 'y') return true;
    else
    {
        return false;
    }
}

// converts supplied player to it's char equivilent, example: player 1 = X
char playerToSymbol(players::Players playerToConvert)
{
    switch (playerToConvert)
    {
        case players::PLAYER_ONE:
            return 'X';
        case players::PLAYER_TWO:
            return 'O';
    }
}

// Converts "playerToConvert" to it's string format
std::string playerToPlayerName(players::Players playerToConvert)
{
    switch (playerToConvert)
    {
        case players::PLAYER_ONE:
            return "player one";
        case players::PLAYER_TWO:
            return "player two";
    };
}

// Handles all game functions,
// TRUE  = if a game has not ended OR the players wish to play again 
// FALSE = if a game has ended OR the players do NOT wish to play again
//
bool gameMain()
{
    std::cout << "How many rows would you like: ";
    int rows;
    std::cin >> rows;

    std::cout << "How many columns would you like: ";
    int columns;
    std::cin >> columns;

    int boardLength = rows * columns;
    char *board = new char[boardLength] {' '};

    const int maxTurns = boardLength;

    for (int turn = 1; turn <= maxTurns; ++turn)
    {
        players::Players currentPlayer;

        // We use magic number '2' so we can have the players take turns
        // 1 % 2 remiander 1(Player one), 2 % 2 remainder 0(Player two)
        if ((turn % 2) == 1) currentPlayer = players::PLAYER_ONE;
        else                 currentPlayer = players::PLAYER_TWO;

        drawBoard(board, rows, columns);
        placeSymbol(board, rows, columns, currentPlayer);
        if (checkWinningCondition(board, rows, columns, currentPlayer))
        {
            // We are done with the board de-allocate it
            delete board;
            board = 0;
            return true;
        }
    }
    std::cout << "Game is a tie\n";

    // We are done with the board de-allocate it
    delete board;
    board = 0;
    return true;
}

int main()
{
    do
    {
        gameMain(); 
    } 
    while (requestReplay());

    return 0;
}
