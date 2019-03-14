/*
* Compute the number of white pieces have placed the black king in check and determine if it is checkmate
* Print 100 if checkmate, if not print out the number of pieces that have the king in check
*
* White pieces are denoted by K = king, Q = queen, N = knight, P = pawn, B = bishop, R = rook
* Black pieces are denoted by k = king, q = queen, n = knight, p = pawn, b = bishop, r = rook
*/

#include <stdio.h>
#include <stdbool.h>

#define BoardSize 8
#define Invalid -1
#define MaxPiecesToCheckKing 16
#define ArraySize(array) (sizeof(array) / sizeof(array[0]))

// Defining enum of locations to move a chess piece
typedef enum{
    Move_Up,
    Move_Down,
    Move_ToTheRight,
    Move_ToTheLeft,
    Move_DiagonallyRightUp,
    Move_DiagonallyRightDown,
    Move_DiagonallyLeftUp,
    Move_DiagonallyLeftDown,
    Move_Invalid
} DirectionToMove_t;

// Defining structure to maintain the current location on the board
typedef struct{
    int row;
    int col;
} ChessPieceLocation_t;
ChessPieceLocation_t kingLocation;  // Storing the location of the king
ChessPieceLocation_t locationsToMove[] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, 1}, {1, 1}, {-1, -1}, {1, -1} };   // Storing row, column move maps to enum of directions to move

// Defining chess pieces on the board
enum{
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn
};
char friendlyPieces[] = { 'k', 'q', 'r', 'b', 'n', 'p' };
char enemyPieces[] = { 'K', 'Q', 'R', 'B', 'N', 'P' };

// Defining chess board to be used throughout program
char chessBoard[BoardSize][BoardSize] = { '-' };

/******************************************************************
* Helper functions to determine if we have valid locations on the
* chess boar
******************************************************************/
_Bool FoundChessPiece(ChessPieceLocation_t pieceLocation, char desiredPiece){
    if(chessBoard[pieceLocation.row][pieceLocation.col] == desiredPiece) return true;
    else return false;
}

_Bool IsSameLocation(ChessPieceLocation_t first, ChessPieceLocation_t second){
    if(first.row == second.row && first.col == second.col) return true;
    return false;
}

_Bool EmptyChessBoardCell(ChessPieceLocation_t chessPieceLocation){
    if(chessBoard[chessPieceLocation.row][chessPieceLocation.col] == '-') return true;
    else return false;
}

_Bool ValidChessBoardPosition(ChessPieceLocation_t chessPieceLocation){
    if(chessPieceLocation.row < 0 || chessPieceLocation.row >= BoardSize) return false;
    else if(chessPieceLocation.col < 0 || chessPieceLocation.col >= BoardSize) return false;
    else return true;
}

void UpdateLocation(ChessPieceLocation_t *chessPieceLocation, DirectionToMove_t direction){
    ChessPieceLocation_t newLocation = *chessPieceLocation;
    newLocation.row += locationsToMove[direction].row;
    newLocation.col += locationsToMove[direction].col;

    *chessPieceLocation = newLocation;
}


/*********************************************************************
* Function to read in the chess board (called single time)
* Determines location of initial chess piece
*********************************************************************/
ChessPieceLocation_t ReadInChessBoardAndGetLocationOf(char chessPiece){
    ChessPieceLocation_t pieceLocation = { Invalid };
    int row, col;

    for(row = 0; row < BoardSize; row++){
        for(col = 0; col < BoardSize; col++){
            scanf(" %c", &chessBoard[row][col]);
            ChessPieceLocation_t tempLocation;
            tempLocation.row = row;
            tempLocation.col = col;
            if(FoundChessPiece(tempLocation, chessPiece)){
                pieceLocation = tempLocation;
            }
        }
    }

    return pieceLocation;
}

/****************************************************************************
* Functions to recursively move up the chess board until we find pieces that
* can move to/capture pieces that are at the starting location.
****************************************************************************/
_Bool ChessPieceIsFound(ChessPieceLocation_t currentSearchLocation, const ChessPieceLocation_t locationOfChessPiece, const char chessPieceToFind, DirectionToMove_t direction){

    while(ValidChessBoardPosition(currentSearchLocation)){
        // printf("search location: %d, %d; location of piece: %d, %d\n", currentSearchLocation.row, currentSearchLocation.col, locationOfChessPiece.row, locationOfChessPiece.col);
        // printf("piece we are looking for: %c; piece at search location: %c\n", chessPieceToFind, chessBoard[currentSearchLocation.row][currentSearchLocation.col]);
        if(EmptyChessBoardCell(currentSearchLocation) || IsSameLocation(locationOfChessPiece, currentSearchLocation)){
            UpdateLocation(&currentSearchLocation, direction);
        }
        else if(FoundChessPiece(currentSearchLocation, chessPieceToFind)){
            return true;
        }
        else{
            break;
        }
    }

    return false;
}

int CheckForPawns(ChessPieceLocation_t kingLocation, const char pawn){
    int pawnRowPositions[] = { 1, 1 };
    int pawnColPositions[] = { -1, 1 };
    int count = 0;

    size_t index;
    for(index = 0; index < ArraySize(pawnRowPositions); index++){
        ChessPieceLocation_t checkLocation;
        checkLocation.row = kingLocation.row + pawnRowPositions[index];
        checkLocation.col = kingLocation.col + pawnColPositions[index];

        if(ValidChessBoardPosition(checkLocation) && FoundChessPiece(checkLocation, pawn)){
            count += 1;
        }
    }

    return count;
}

int CheckForKnights(ChessPieceLocation_t kingLocation, const char knight){
    int knightRowPositions[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
    int knightColPositions[] = { -1, 1, 1, -1, -2, 2, -2, 2 };
    int count = 0;

    size_t index;
    for(index = 0; index < ArraySize(knightRowPositions); index++){
        ChessPieceLocation_t checkLocation;
        checkLocation.row = kingLocation.row + knightRowPositions[index];
        checkLocation.col = kingLocation.col + knightColPositions[index];

        if(ValidChessBoardPosition(checkLocation) && FoundChessPiece(checkLocation, knight)){
            count += 1;
        }
    }

    return count;
}

int CheckForKing(ChessPieceLocation_t kingLocation, const char king){
    int kingRowPositions[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
    int kingColPositions[] = { -1, 0, 1, 1, -1, -1, 0, 1 };
    int count = 0;

    size_t index;
    for(index = 0; index < ArraySize(kingRowPositions); index++){
        ChessPieceLocation_t checkLocation;
        checkLocation.row = kingLocation.row + kingRowPositions[index];
        checkLocation.col = kingLocation.col + kingColPositions[index];

        if(ValidChessBoardPosition(checkLocation) && FoundChessPiece(checkLocation, king)){
            count += 1;
        }
    }

    return count;
}

/*************************************************************************************
* Functions that help determine the number of pieces that are checking the king.
* Functions that help determine if the king is currently in checkmate
**************************************************************************************/
int GetNumOfChessPiecesThatCanMoveTo(ChessPieceLocation_t locationToStartSearch, ChessPieceLocation_t locationOfChessPiece, char chessPieces[]){
    int count = 0;

    int index;
    for(index = 0; index < ArraySize(chessPieces); index++){
        if(index == Rook || index == Queen){
            if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[index], Move_Up)) count++;
            if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[index], Move_Down)) count++;
            if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[index], Move_ToTheLeft)) count++;
            if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[index], Move_ToTheRight)) count++;
        }

        if(index == Bishop || index == Queen){
            if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[index], Move_DiagonallyLeftUp)) count++;
            if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[index], Move_DiagonallyRightUp)) count++;
            if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[index], Move_DiagonallyLeftDown)) count++;
            if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[index], Move_DiagonallyRightDown)) count++;
        }

        if(index == King) count += CheckForKing(locationToStartSearch, chessPieces[King]);
        if(index == Knight) count += CheckForKnights(locationToStartSearch, chessPieces[Knight]);
        if(index == Pawn) count += CheckForPawns(locationToStartSearch, chessPieces[Pawn]);
    }

    return count;
}

int main(){

    kingLocation = ReadInChessBoardAndGetLocationOf(friendlyPieces[King]);
    int checkCount = GetNumOfChessPiecesThatCanMoveTo(kingLocation, kingLocation, enemyPieces);
    printf("%d\n", checkCount);

    return 0;
}
