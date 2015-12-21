#ifndef TICTACTOE_H
#define TICTACTOE_H

// Player info
namespace players
{
    enum Players
    {
        PLAYER_ONE,
        PLAYER_TWO
    };
}

// Function prototypes

// Core game functions
bool gameMain();
int getIndexInArray(int amountOfColumns, int rowToCheck, int columnToCheck);
void drawBoard(char *board, int rows, int columns, int arrayLength);

bool checkWinningConditions(char *board, int amountOfRows, int amountOfColumns, players::Players currentPlayer);
    // Winning condition sub functions
    bool checkRows(char *board, int amountOfRows, int amountOfColumns, players::Players currentPlayer);
    bool checkColumns(char *board, int amountOfRows, int amountOfColumns, players::Players currentPlayer);
    bool checkDiagonals(char *board, int amountOfRows, int amountOfColumns, players::Players currentPlayer);

// Player functions
void placeSymbol(char *board, int amountOfRows, int amountOfColumns, players::Players currentPlayer);
std::string playerToPlayerName(players::Players playerToConvert);
char playerToSymbol(players::Players playerToConvert);
bool requestReplay();

#endif
