#include <stdio.h>
#include <stdbool.h>

#define ChessBoardSize 8

typedef struct{
    int row;
    int col;
} ChessPieceLocation_t;

// Taking in input from the user
// Format is 8 lines with 8 characters (the board size)
// Every line is followed by a \n except for the last line
void ReadInChessBoard(char chessBoard[][ChessBoardSize]){
    int row, col;
    char chessBoardPiece;

    for(row = 0; row < ChessBoardSize; row++){
        for(col = 0; col < ChessBoardSize; col++){
            scanf("%c", &chessBoardPiece);
            chessBoard[row][col] = chessBoardPiece;
        }

        if(row < (ChessBoardSize-1)){
            scanf("%c", &chessBoardPiece);
        }
    }
}

// Takes in the chess piece and obtains the chess pieces location in the board
// Returns the chess piece location
ChessPieceLocation_t GetChessPieceLocation(char chessBoard[][ChessBoardSize], char chessPiece){
    int row, col;
    ChessPieceLocation_t chessPieceLocation;

    for(row = 0; row < ChessBoardSize; row++){
        for(col = 0; col < ChessBoardSize; col++){
            if(chessBoard[row][col] == chessPiece){
                chessPieceLocation.row = row;
                chessPieceLocation.col = col;
            }
        }
    }

    return chessPieceLocation;
}

// Check if a position in the chess board is valid
_Bool ValidChessBoardPosition(int row, int col){
    _Bool validPosition = true;

    if(row < 0 || row >= ChessBoardSize || col < 0 || col >= ChessBoardSize){
        // printf("Invalid Position: %d, %d\n", row, col);
        validPosition = false;
    }

    return validPosition;
}

// Check if position is an empty cell
_Bool EmptyChessBoardCell(char chessPiece){
    _Bool emptyCell = false;

    if(chessPiece == '-'){
        emptyCell = true;
    }

    return emptyCell;
}

// Check if found a chess piece that is valid
_Bool FoundChessPiece(char currentChessPiece, char desiredChessPiece){
    return ((currentChessPiece == desiredChessPiece) ? true : false);
}

// Checks for pieces placing the king in check that are horizontal from its position
// Takes in the location of the king and the char notation of the queen and the rook
// The queen and rook are the only pieces that can put threaten the king
int CheckHorizontallyFromTheKing(ChessPieceLocation_t kingLocation, char chessBoard[][ChessBoardSize], char queen, char rook){
    int checkKingCount = 0;
    char currentPiece;
    int row, col;

    // Checking horizontally left
    row = kingLocation.row;
    col = kingLocation.col - 1;
    while(ValidChessBoardPosition(row, col)){
        currentPiece = chessBoard[row][col];
        // printf("Checking horizontal left: %d, %d, %c\n", row, col, currentPiece);
        if(FoundChessPiece(currentPiece, queen) || FoundChessPiece(currentPiece, rook)){
            checkKingCount++;
            break;
        }
        else if(!EmptyChessBoardCell(currentPiece)){
            break;
        }

        col--;
    }

    // Checking horizontally right
    col = kingLocation.col + 1;
    while(ValidChessBoardPosition(row, col)){
        currentPiece = chessBoard[row][col];
        // printf("Checking horizontal right: %d, %d, %c\n", row, col, currentPiece);
        if(FoundChessPiece(currentPiece, queen) || FoundChessPiece(currentPiece, rook)){
            checkKingCount++;
            break;
        }
        else if(!EmptyChessBoardCell(currentPiece)){
            break;
        }

        col++;
    }

    return checkKingCount;
}

// Checks for pieces placing the king in check vertically from the king
// The queen and the rook are the only pieces that can place the king in check vertically
int CheckVerticallyFromTheKing(ChessPieceLocation_t kingLocation, char chessBoard[][ChessBoardSize], char queen, char rook){
    int checkKingCount = 0;
    char currentPiece;
    int row, col;

    // Checking vertically up
    row = kingLocation.row - 1;
    col = kingLocation.col;
    while(ValidChessBoardPosition(row, col)){
        currentPiece = chessBoard[row][col];
        // printf("Checking vertically up: %d, %d, %c\n", row, col, currentPiece);
        if(FoundChessPiece(currentPiece, queen) || FoundChessPiece(currentPiece, rook)){
            checkKingCount++;
            break;
        }
        else if(!EmptyChessBoardCell(currentPiece)){
            break;
        }

        row--;
    }

    // Checking vertically down
    row = kingLocation.row + 1;
    while(ValidChessBoardPosition(row, col)){
        currentPiece = chessBoard[row][col];
        // printf("Checking vertically down: %d, %d, %c\n", row, col, currentPiece);
        if(FoundChessPiece(currentPiece, queen) || FoundChessPiece(currentPiece, rook)){
            checkKingCount++;
            break;
        }
        else if(!EmptyChessBoardCell(currentPiece)){
            break;
        }

        row++;
    }

    return checkKingCount;
}

// Checking diagonally right from the king
// Only the queen and the bishop can check the king diagonally
int CheckDiagonallyRightFromTheKing(ChessPieceLocation_t kingLocation, char chessBoard[][ChessBoardSize], char queen, char bishop){
    int checkKingCount = 0;
    char currentPiece;
    int row, col;

    // Checking diagonal up right
    row = kingLocation.row - 1;
    col = kingLocation.col + 1;
    while(ValidChessBoardPosition(row, col)){
        currentPiece = chessBoard[row][col];
        // printf("Checking diagonally up right: %d, %d, %c\n", row, col, currentPiece);
        if(FoundChessPiece(currentPiece, queen) || FoundChessPiece(currentPiece, bishop)){
            checkKingCount++;
            break;
        }
        else if(!EmptyChessBoardCell(currentPiece)){
            break;
        }

        row--;
        col++;
    }

    // Checking diagonal down right
    row = kingLocation.row + 1;
    col = kingLocation.col + 1;
    while(ValidChessBoardPosition(row, col)){
        currentPiece = chessBoard[row][col];
        // printf("Checking diagonally down right: %d, %d, %c\n", row, col, currentPiece);
        if(FoundChessPiece(currentPiece, queen) || FoundChessPiece(currentPiece, bishop)){
            checkKingCount++;
            break;
        }
        else if(!EmptyChessBoardCell(currentPiece)){
            break;
        }

        row++;
        col++;
    }

    return checkKingCount;
}

// Checking diagonally left from the king
// Only the queen and the bishop can check the king diagonally
int CheckDiagonallyLeftFromTheKing(ChessPieceLocation_t kingLocation, char chessBoard[][ChessBoardSize], char queen, char bishop){
    int checkKingCount = 0;
    char currentPiece;
    int row, col;

    // Checking diagonal up left
    row = kingLocation.row - 1;
    col = kingLocation.col - 1;
    while(ValidChessBoardPosition(row, col)){
        currentPiece = chessBoard[row][col];
        // printf("Checking diagonally up left: %d, %d, %c\n", row, col, currentPiece);
        if(FoundChessPiece(currentPiece, queen) || FoundChessPiece(currentPiece, bishop)){
            checkKingCount++;
            break;
        }
        else if(!EmptyChessBoardCell(currentPiece)){
            break;
        }

        row--;
        col--;
    }

    // Checking diagonal down right
    row = kingLocation.row + 1;
    col = kingLocation.col - 1;
    while(ValidChessBoardPosition(row, col)){
        currentPiece = chessBoard[row][col];
        // printf("Checking diagonally down left: %d, %d, %c\n", row, col, currentPiece);
        if(FoundChessPiece(currentPiece, queen) || FoundChessPiece(currentPiece, bishop)){
            checkKingCount++;
            break;
        }
        else if(!EmptyChessBoardCell(currentPiece)){
            break;
        }

        row++;
        col--;
    }

    return checkKingCount;
}

// Checks if a knight has put the king in check
int CheckForAKnight(ChessPieceLocation_t kingLocation, char chessBoard[][ChessBoardSize], char knight){
    char currentPiece;
    int checkKingCount = 0, knightPositions = 8;
    int knightRowPositions[] = {-1,-1,1,1,2,2,-2,-2};
    int knightColPositions[] = {2,-2,2,-2,1,-1,1,-1};
    int row, col, index;

    for(index = 0; index < knightPositions; index++){
        row = kingLocation.row + knightRowPositions[index];
        col = kingLocation.col + knightColPositions[index];

        if(ValidChessBoardPosition(row, col)){
            currentPiece = chessBoard[row][col];
            // printf("Checking for knight positions: %d, %d, %c\n", row, col, currentPiece);
            if(FoundChessPiece(currentPiece, knight)){
                checkKingCount++;
            }
        }
    }

    return checkKingCount;
}

// Checks if a pawn has put the king in check
int CheckForAPawn(ChessPieceLocation_t kingLocation, char chessBoard[][ChessBoardSize], char pawn){
    char currentPiece;
    int checkKingCount = 0, pawnPositions = 2;
    int pawnRowPositions[] = {1, 1};
    int pawnColPositions[] = {1, -1};
    int row, col, index;

    for(index = 0; index < pawnPositions; index++){
        row = kingLocation.row + pawnRowPositions[index];
        col = kingLocation.col + pawnColPositions[index];

        if(ValidChessBoardPosition(row, col)){
            currentPiece = chessBoard[row][col];
            // printf("Checking for pawn positions: %d, %d, %c\n", row, col, currentPiece);
            if(FoundChessPiece(currentPiece, pawn)){
                checkKingCount++;
            }
        }
    }

    return checkKingCount;
}

// Function looking for pieces that put the king in check
// Takes in the location of the king, and the char notation of the other chess pieces
int GetCheckCount(ChessPieceLocation_t kingLocation, char chessBoard[][ChessBoardSize], char queen, char rook, char bishop, char knight, char pawn){
    int checkCnt;

    checkCnt = CheckHorizontallyFromTheKing(kingLocation, chessBoard, queen, rook);
    checkCnt += CheckVerticallyFromTheKing(kingLocation, chessBoard, queen, rook);
    checkCnt += CheckDiagonallyLeftFromTheKing(kingLocation, chessBoard, queen, bishop);
    checkCnt += CheckDiagonallyRightFromTheKing(kingLocation, chessBoard, queen, bishop);
    checkCnt += CheckForAKnight(kingLocation, chessBoard, knight);
    checkCnt += CheckForAPawn(kingLocation, chessBoard, pawn);

    return checkCnt;
}

int main(){

    int checkCount;
    char chessBoard[ChessBoardSize][ChessBoardSize];
    char whitePieces[] = { 'K', 'Q', 'R', 'B', 'N', 'P' };
    char blackPieces[] = { 'k', 'q', 'r', 'b', 'n', 'p' };
    ChessPieceLocation_t blackKingLocation;

    ReadInChessBoard(chessBoard);
    blackKingLocation = GetChessPieceLocation(chessBoard, blackPieces[0]);

    // printf("king location: %d, %d", blackKingLocation.row, blackKingLocation.col);
    checkCount = GetCheckCount(blackKingLocation, chessBoard, whitePieces[1], whitePieces[2], whitePieces[3], whitePieces[4], whitePieces[5]);

    printf("%d\n", checkCount);

    return checkCount;
}
