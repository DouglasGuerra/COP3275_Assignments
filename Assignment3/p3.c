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
DirectionToMove_t oppositeDirection[] = { Move_Down, Move_Up, Move_ToTheLeft, Move_ToTheRight, Move_DiagonallyLeftDown, Move_DiagonallyLeftUp, Move_DiagonallyRightDown, Move_DiagonallyRightUp };

// Defining structure to maintain the current location on the board
typedef struct{
    int row;
    int col;
} ChessPieceLocation_t;
ChessPieceLocation_t kingLocation;  // Storing the location of the king
ChessPieceLocation_t locationsToMove[] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, 1}, {1, 1}, {-1, -1}, {1, -1} };   // Storing row, column move maps to enum of directions to move

// Defining structure to maintain location and direction of piece checking king
typedef struct{
    _Bool valid;
    ChessPieceLocation_t location;
    DirectionToMove_t direction;
} ChessPieceCheckingKing_t;
ChessPieceCheckingKing_t piecesCheckingKing[MaxPiecesToCheckKing]; // Defining an array to store the instances of pieces checking the king
int piecesCheckingKingIndex = 0;  // Index for storing pieces that are checking king

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


_Bool ValidKingMove(ChessPieceLocation_t location){
    int index;
    for(index = 0; index < ArraySize(enemyPieces); index++){
        if(FoundChessPiece(location, enemyPieces[index]) || EmptyChessBoardCell(location)) return true;
    }
    return false;
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

/************************************************************************
* Functions to manipulate data structure storing pieces that are checking
* the king
*************************************************************************/
_Bool IsAlreadyStored(ChessPieceLocation_t chessPiece){
    int index;
    for(index = 0; index < piecesCheckingKingIndex; index++){
        ChessPieceCheckingKing_t storedChessPiece = piecesCheckingKing[index];
        if(storedChessPiece.location.row == chessPiece.row && storedChessPiece.location.col == chessPiece.col){
            return true;
        }
    }

    return false;
}

void StoreChessPieceCheckingKing(ChessPieceLocation_t chessPieceLocation, DirectionToMove_t direction){
    if(piecesCheckingKingIndex < MaxPiecesToCheckKing && !IsAlreadyStored(chessPieceLocation)){
        ChessPieceCheckingKing_t chessPieceCheckingKing;
        chessPieceCheckingKing.location = chessPieceLocation;
        chessPieceCheckingKing.direction = direction;
        chessPieceCheckingKing.valid = true;
        piecesCheckingKing[piecesCheckingKingIndex] = chessPieceCheckingKing;
        piecesCheckingKingIndex++;
    }
}

void InvalidateChessPieceCheckingKing(int index){
    if(index >= 0 && index < piecesCheckingKingIndex){
        piecesCheckingKing[index].valid = false;
    }
}

int GetNumOfPiecesCheckingKing(){
    int count = 0;

    int index;
    for(index = 0; index < piecesCheckingKingIndex; index++){
        if(piecesCheckingKing[index].valid) count++;
    }
    return count;
}

_Bool RetrieveChessPieceCheckingKing(ChessPieceCheckingKing_t *chessPieceCheckingKing, int index){
    if(index < piecesCheckingKingIndex){
        *chessPieceCheckingKing = piecesCheckingKing[index];
        return true;
    }
    else return false;
}

/***************************************************************************
* Functions to manipulate data structure to maintain pieces that are being used
* to capture enemy pieces or block the king
****************************************************************************/


/****************************************************************************
* Functions to move through the chess board until we find pieces that
* can move to/capture pieces that are at the starting location.
****************************************************************************/
_Bool ChessPieceIsFound(ChessPieceLocation_t currentSearchLocation, const ChessPieceLocation_t locationOfChessPiece, const char queen, const char rookOrBishop, DirectionToMove_t direction){

    while(ValidChessBoardPosition(currentSearchLocation)){
        // printf("search location: %d, %d; location of piece: %d, %d\n", currentSearchLocation.row, currentSearchLocation.col, locationOfChessPiece.row, locationOfChessPiece.col);
        // printf("piece we are looking for: %c; piece at search location: %c\n", chessPieceToFind, chessBoard[currentSearchLocation.row][currentSearchLocation.col]);
        if(EmptyChessBoardCell(currentSearchLocation) || IsSameLocation(locationOfChessPiece, currentSearchLocation)){
            UpdateLocation(&currentSearchLocation, direction);
        }
        else if(FoundChessPiece(currentSearchLocation, queen) || FoundChessPiece(currentSearchLocation, rookOrBishop)){
            if(IsSameLocation(locationOfChessPiece, kingLocation)){
                StoreChessPieceCheckingKing(currentSearchLocation, oppositeDirection[direction]); // Path of the piece is opposite of the direction we are currently searching in
            }
            return true;
        }
        else{
            break;
        }
    }

    return false;
}

int CheckForPawns(ChessPieceLocation_t location, const char pawn){
    _Bool IsFriendlyPawn = (pawn == friendlyPieces[Pawn]) ? true : false;
    int pawnRowPositions[] = { 1, 1 };
    int pawnColPositions[] = { -1, 1 };
    int count = 0;

    // Checking for pawn capture
    size_t index;
    for(index = 0; index < ArraySize(pawnRowPositions); index++){
        ChessPieceLocation_t checkLocation;
        checkLocation.row = (IsFriendlyPawn) ? location.row - pawnRowPositions[index] : location.row + pawnRowPositions[index];
        checkLocation.col = (IsFriendlyPawn) ? location.col - pawnRowPositions[index] : location.col + pawnColPositions[index];

        if(ValidChessBoardPosition(checkLocation) && FoundChessPiece(checkLocation, pawn) && !EmptyChessBoardCell(checkLocation)){
            if(IsSameLocation(location, kingLocation)) StoreChessPieceCheckingKing(checkLocation, Move_Invalid);
            count += 1;
        }
    }

    // Checking if we can block path of a piece only if we are moving a friendly piece
    if(IsFriendlyPawn){
        ChessPieceLocation_t checkLocation;
        checkLocation.row = location.row - 1;
        checkLocation.col = location.col - 0;

        if(ValidChessBoardPosition(checkLocation) && FoundChessPiece(checkLocation, pawn) && EmptyChessBoardCell(checkLocation)){
            count += 1;
        }
    }

    return count;
}

int CheckForKnights(ChessPieceLocation_t location, const char knight){
    int knightRowPositions[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
    int knightColPositions[] = { -1, 1, 1, -1, -2, 2, -2, 2 };
    int count = 0;

    size_t index;
    for(index = 0; index < ArraySize(knightRowPositions); index++){
        ChessPieceLocation_t checkLocation;
        checkLocation.row = location.row + knightRowPositions[index];
        checkLocation.col = location.col + knightColPositions[index];

        if(ValidChessBoardPosition(checkLocation) && FoundChessPiece(checkLocation, knight)){
            if(IsSameLocation(location, kingLocation)) StoreChessPieceCheckingKing(checkLocation, Move_Invalid);
            count += 1;
        }
    }

    return count;
}

int CheckForKing(ChessPieceLocation_t location, const char king){
    int kingRowPositions[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
    int kingColPositions[] = { -1, 0, 1, 1, -1, -1, 0, 1 };
    int count = 0;

    size_t index;
    for(index = 0; index < ArraySize(kingRowPositions); index++){
        ChessPieceLocation_t checkLocation;
        checkLocation.row = location.row + kingRowPositions[index];
        checkLocation.col = location.col + kingColPositions[index];

        if(ValidChessBoardPosition(checkLocation) && FoundChessPiece(checkLocation, king)){
            if(IsSameLocation(location, kingLocation)) StoreChessPieceCheckingKing(checkLocation, Move_Invalid);
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

    if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[Queen], chessPieces[Rook], Move_Up)) count++;
    if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[Queen], chessPieces[Rook], Move_Down)) count++;
    if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[Queen], chessPieces[Rook], Move_ToTheLeft)) count++;
    if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[Queen], chessPieces[Rook], Move_ToTheRight)) count++;


    if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[Queen], chessPieces[Bishop], Move_DiagonallyLeftUp)) count++;
    if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[Queen], chessPieces[Bishop], Move_DiagonallyRightUp)) count++;
    if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[Queen], chessPieces[Bishop], Move_DiagonallyLeftDown)) count++;
    if(ChessPieceIsFound(locationToStartSearch, locationOfChessPiece, chessPieces[Queen], chessPieces[Bishop], Move_DiagonallyRightDown)) count++;

    if(chessPieces == enemyPieces){
        count += CheckForKing(locationToStartSearch, chessPieces[King]);
    }
    count += CheckForKnights(locationToStartSearch, chessPieces[Knight]);
    count += CheckForPawns(locationToStartSearch, chessPieces[Pawn]);

    return count;
}

_Bool KingCanMoveOutOfCheck(){
    // printf("--------- Checking for king move out of check -------------------\n");
    int kingRowPositions[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
    int kingColPositions[] = { -1, 0, 1, 1, -1, -1, 0, 1 };

    size_t index;
    for(index = 0; index < ArraySize(kingRowPositions); index++){
        ChessPieceLocation_t newLocation;
        newLocation.row = kingLocation.row + kingRowPositions[index];
        newLocation.col = kingLocation.col + kingColPositions[index];
        if(ValidChessBoardPosition(newLocation) && ValidKingMove(newLocation)){
            // printf("\nNew Location\n");
            // printf("%d, %d\n", newLocation.row, newLocation.col);
            if(GetNumOfChessPiecesThatCanMoveTo(newLocation, newLocation, enemyPieces) == 0){
                return true;
            }
        }
    }
    // printf("--------------------- Done -------------------------- \n");

    return false;
}

void CapturePiecesCheckingKing(){
    ChessPieceCheckingKing_t chessPiece;
    int index = 0;
    while(RetrieveChessPieceCheckingKing(&chessPiece, index)){
        if(chessPiece.valid && GetNumOfChessPiecesThatCanMoveTo(chessPiece.location, chessPiece.location, friendlyPieces) > 0){
            InvalidateChessPieceCheckingKing(index);
        }
        index++;
    }
}

void BlockThePathOfCheckingPieces(){
    ChessPieceCheckingKing_t chessPiece;
    int index = 0;
    while(RetrieveChessPieceCheckingKing(&chessPiece, index)){
        if(chessPiece.valid && chessPiece.direction != Move_Invalid){
            ChessPieceLocation_t location = chessPiece.location;
            while(!IsSameLocation(location, kingLocation) && ValidChessBoardPosition(location)){
                if(GetNumOfChessPiecesThatCanMoveTo(location, chessPiece.location, friendlyPieces) > 0){
                    InvalidateChessPieceCheckingKing(index);
                }
                UpdateLocation(&location, chessPiece.direction);
            }
        }
        index++;
    }
}

_Bool IsCheckMate(){
    // printf("---------------- Checking for checkmate --------------------------\n");
    if(KingCanMoveOutOfCheck()) return false;

    CapturePiecesCheckingKing();
    // GetNumOfPiecesCheckingKing();
    BlockThePathOfCheckingPieces();
    if(GetNumOfPiecesCheckingKing() == 0) return false;

    else return true;;
}

void PrintPiecesCheckingKing(){
    ChessPieceCheckingKing_t piece;
    int index = 0;
    while(RetrieveChessPieceCheckingKing(&piece, index)){
        printf("%d, %d, %d, %c\n", piece.location.row, piece.location.col, piece.direction, chessBoard[piece.location.row][piece.location.col]);
        index++;
    }
}

int main(){

    kingLocation = ReadInChessBoardAndGetLocationOf(friendlyPieces[King]);
    int checkCount = GetNumOfChessPiecesThatCanMoveTo(kingLocation, kingLocation, enemyPieces);

    // PrintPiecesCheckingKing();
    if(checkCount > 0 && IsCheckMate()){
        printf("100\n");
    }
    else{
        printf("%d\n", checkCount);
    }

    return 0;
}
