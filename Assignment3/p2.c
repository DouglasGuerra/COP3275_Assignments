/*
* Compute the number of white pieces have placed the black king in check
* White pieces are denoted by K = king, Q = queen, N = knight, P = pawn, B = bishop, R = rook
* Black pieces are denoted by k = king, q = queen, n = knight, p = pawn, b = bishop, r = rook
*/

#include <stdio.h>
#include <stdbool.h>

#define BoardSize 8
#define Invalid -1
#define ArraySize(array) (sizeof(array) / sizeof(array[0]))

typedef struct{
    int row;
    int col;
} ChessPieceLocation_t;

ChessPieceLocation_t kingLocation;
char chessBoard[BoardSize][BoardSize] = { '-' };

void ReadInChessBoard(){
    int row, col;

    for(row = 0; row < BoardSize; row++){
        for(col = 0; col < BoardSize; col++){
            scanf(" %c", &chessBoard[row][col]);
        }
    }
}

void PrintChessBoard(){
    int row, col;

    printf("\nPrinting Board: \n");
    for(row = 0; row < BoardSize; row++){
        for(col = 0; col < BoardSize; col++){
            printf("%c", chessBoard[row][col]);
        }
        printf("\n");
    }
}

_Bool FoundChessPiece(ChessPieceLocation_t pieceLocation, char desiredPiece){
    if(chessBoard[pieceLocation.row][pieceLocation.col] == desiredPiece) return true;
    else return false;
}

_Bool EmptyChessBoardCell(ChessPieceLocation_t chessPieceLocation){
    if(chessBoard[chessPieceLocation.row][chessPieceLocation.col] == '-') return true;
    else return false;
}

_Bool ValidChessBoardPosition(ChessPieceLocation_t chessPieceLocation){
    _Bool validPosition = true;

    if(chessPieceLocation.row < 0 || chessPieceLocation.col >= BoardSize) validPosition = false;
    if(chessPieceLocation.col < 0 || chessPieceLocation.col >= BoardSize) validPosition = false;

    return validPosition;
}

_Bool CurrentlyAtKingLocation(ChessPieceLocation_t chessPieceLocation){
    if((chessPieceLocation.row == kingLocation.row) && (chessPieceLocation.col == kingLocation.col))
        return true;
    else
        return false;
}

ChessPieceLocation_t GetChessPieceLocation(char chessPiece){
    ChessPieceLocation_t chessPieceLocation;
    ChessPieceLocation_t tempLocation;
    tempLocation.row = Invalid;
    tempLocation.col = Invalid;
    chessPieceLocation = tempLocation;

    int row, col;
    for(row = 0; row < BoardSize; row++){
        for(col = 0; col < BoardSize; col++){
            tempLocation.row = row;
            tempLocation.col = col;

            if(FoundChessPiece(tempLocation, chessPiece)){
                chessPieceLocation = tempLocation;
            }
        }
    }

    return chessPieceLocation;
}

_Bool CheckVerticallyUpFromTheKing(ChessPieceLocation_t checkLocation, const char queen, const char rook){

    if(ValidChessBoardPosition(checkLocation)){
        if(EmptyChessBoardCell(checkLocation) || CurrentlyAtKingLocation(checkLocation)){
            checkLocation.row -= 1;
            return CheckVerticallyUpFromTheKing(checkLocation, queen, rook);
        }
        else if(FoundChessPiece(checkLocation, queen) || FoundChessPiece(checkLocation, rook)){
            return true;
        }
    }

    return false;
}

_Bool CheckVerticallyDownFromTheKing(ChessPieceLocation_t checkLocation, const char queen, const char rook){

    if(ValidChessBoardPosition(checkLocation)){
        if(EmptyChessBoardCell(checkLocation) || CurrentlyAtKingLocation(checkLocation)){
            checkLocation.row += 1;
            return CheckVerticallyDownFromTheKing(checkLocation, queen, rook);
        }
        else if(FoundChessPiece(checkLocation, queen) || FoundChessPiece(checkLocation, rook)){
            return true;
        }
    }

    return false;
}

_Bool CheckHorizontallyRightFromTheKing(ChessPieceLocation_t checkLocation, const char queen, const char rook){

    if(ValidChessBoardPosition(checkLocation)){
        if(EmptyChessBoardCell(checkLocation) || CurrentlyAtKingLocation(checkLocation)){
            checkLocation.col += 1;
            return CheckHorizontallyRightFromTheKing(checkLocation, queen, rook);
        }
        else if(FoundChessPiece(checkLocation, queen) || FoundChessPiece(checkLocation, rook)){
            return true;
        }
    }

    return false;
}

_Bool CheckHorizontallyLeftFromTheKing(ChessPieceLocation_t checkLocation, const char queen, const char rook){

    if(ValidChessBoardPosition(checkLocation)){
        if(EmptyChessBoardCell(checkLocation) || CurrentlyAtKingLocation(checkLocation)){
            checkLocation.col -= 1;
            return CheckHorizontallyLeftFromTheKing(checkLocation, queen, rook);
        }
        else if(FoundChessPiece(checkLocation, queen) || FoundChessPiece(checkLocation, rook)){
            return true;
        }
    }

    return false;
}

_Bool CheckDiagonallyUpLeftFromTheKing(ChessPieceLocation_t checkLocation, const char queen, const char bishop){

    if(ValidChessBoardPosition(checkLocation)){
        if(EmptyChessBoardCell(checkLocation) || CurrentlyAtKingLocation(checkLocation)){
            checkLocation.row -= 1;
            checkLocation.col -= 1;
            return CheckDiagonallyUpLeftFromTheKing(checkLocation, queen, bishop);
        }
        else if(FoundChessPiece(checkLocation, queen) || FoundChessPiece(checkLocation, bishop)){
            return true;
        }
    }

    return false;
}

_Bool CheckDiagonallyUpRightFromTheKing(ChessPieceLocation_t checkLocation, const char queen, const char bishop){

    if(ValidChessBoardPosition(checkLocation)){
        if(EmptyChessBoardCell(checkLocation) || CurrentlyAtKingLocation(checkLocation)){
            checkLocation.row -= 1;
            checkLocation.col += 1;
            return CheckDiagonallyUpRightFromTheKing(checkLocation, queen, bishop);
        }
        else if(FoundChessPiece(checkLocation, queen) || FoundChessPiece(checkLocation, bishop)){
            return true;
        }
    }

    return false;
}

_Bool CheckDiagonallyDownLeftFromTheKing(ChessPieceLocation_t checkLocation, const char queen, const char bishop){

    if(ValidChessBoardPosition(checkLocation)){
        if(EmptyChessBoardCell(checkLocation) || CurrentlyAtKingLocation(checkLocation)){
            checkLocation.row += 1;
            checkLocation.col -= 1;
            return CheckDiagonallyDownLeftFromTheKing(checkLocation, queen, bishop);
        }
        else if(FoundChessPiece(checkLocation, queen) || FoundChessPiece(checkLocation, bishop)){
            return true;
        }
    }

    return false;
}

_Bool CheckDiagonallyDownRightFromTheKing(ChessPieceLocation_t checkLocation, const char queen, const char bishop){

    if(ValidChessBoardPosition(checkLocation)){
        if(EmptyChessBoardCell(checkLocation) || CurrentlyAtKingLocation(checkLocation)){
            checkLocation.row += 1;
            checkLocation.col += 1;
            return CheckDiagonallyDownRightFromTheKing(checkLocation, queen, bishop);
        }
        else if(FoundChessPiece(checkLocation, queen) || FoundChessPiece(checkLocation, bishop)){
            return true;
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

int main(){

    char blackPieces[] = { 'k', 'q', 'r', 'b', 'n', 'p' };
    char whitePieces[] = { 'K', 'Q', 'R', 'B', 'N', 'P' };
    int checkCount = 0;

    ReadInChessBoard();
    // PrintChessBoard();
    kingLocation = GetChessPieceLocation(blackPieces[0]);

    if(kingLocation.row != Invalid && kingLocation.col != Invalid){
        if(CheckVerticallyUpFromTheKing(kingLocation, whitePieces[1], whitePieces[2])) checkCount++;
        if(CheckVerticallyDownFromTheKing(kingLocation, whitePieces[1], whitePieces[2])) checkCount++;

        if(CheckHorizontallyRightFromTheKing(kingLocation, whitePieces[1], whitePieces[2])) checkCount++;
        if(CheckHorizontallyLeftFromTheKing(kingLocation, whitePieces[1], whitePieces[2])) checkCount++;

        if(CheckDiagonallyUpLeftFromTheKing(kingLocation, whitePieces[1], whitePieces[3])) checkCount++;
        if(CheckDiagonallyUpRightFromTheKing(kingLocation, whitePieces[1], whitePieces[3])) checkCount++;
        if(CheckDiagonallyDownLeftFromTheKing(kingLocation, whitePieces[1], whitePieces[3])) checkCount++;
        if(CheckDiagonallyDownRightFromTheKing(kingLocation, whitePieces[1], whitePieces[3])) checkCount++;

        checkCount += CheckForPawns(kingLocation, whitePieces[5]);
        checkCount += CheckForKnights(kingLocation, whitePieces[4]);
        checkCount += CheckForKing(kingLocation, whitePieces[0]);
    }

    printf("%d\n", checkCount);

    return 0;
}
