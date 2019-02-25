/*
* In this problem you are given a chess board and have to determine if black is on check, or not threatened
* Input:
*   8 lines of 8 characters
*   Uppercase letters stand for white and lower-case letters stand for black pieces
*   There will always be only one king of each color.
*   A hyphen "-" stands for an empty cell
* Output:
*   The number of opponent (white) pieces that can capture the black king
*/

#include <stdio.h>

int boardSize = 8;

void CheckPawn(int kingIndex[], int pawnIndex[], int *checkCnt){
    int kingRow = kingIndex[0], kingCol = kingIndex[1];
    int pawnRow = pawnIndex[0], pawnCol = pawnIndex[1];

    if(pawnRow-1 == kingRow){
        if(pawnCol-1 == kingCol || pawnCol+1 == kingCol) *checkCnt = *checkCnt + 1;
    }
}

void CheckKnight(int kingIndex[], int knightIndex[], int *checkCnt){
    int kingRow = kingIndex[0], kingCol = kingIndex[1];
    int knightRow = knightIndex[0], knightCol = knightIndex[1];

    if(knightRow-2 == kingRow || knightRow+2 == kingRow){
        if(knightCol-1 == kingCol || knightCol+1 == kingCol){
            *checkCnt = *checkCnt + 1;
        }
    }

    if(knightCol-2 == kingCol || knightCol+2 == kingCol){
        if(knightRow-1 == kingRow || knightRow+1 == kingRow) *checkCnt = *checkCnt + 1;
    }
}

void CheckDiagonalUpRight(char chessBoard[][boardSize], int rowIndex, int colIndex, int *checkCnt){
    if(rowIndex < 0 || rowIndex >= boardSize) return;
    if(colIndex < 0 || colIndex >= boardSize) return;

    if(chessBoard[rowIndex][colIndex] == 'k') *checkCnt = *checkCnt + 1;
    else if(chessBoard[rowIndex][colIndex] != '-') return;
    else CheckDiagonalUpRight(chessBoard, rowIndex-1, colIndex+1, checkCnt);
}

void CheckDiagonalUpLeft(char chessBoard[][boardSize], int rowIndex, int colIndex, int *checkCnt){
    if(rowIndex < 0 || rowIndex >= boardSize) return;
    if(colIndex < 0 || colIndex >= boardSize) return;

    if(chessBoard[rowIndex][colIndex] == 'k') *checkCnt = *checkCnt + 1;
    else if(chessBoard[rowIndex][colIndex] != '-') return;
    else CheckDiagonalUpLeft(chessBoard, rowIndex-1, colIndex-1, checkCnt);
}

void CheckDiagonalDownRight(char chessBoard[][boardSize], int rowIndex, int colIndex, int *checkCnt){
    if(rowIndex < 0 || rowIndex >= boardSize) return;
    if(colIndex < 0 || colIndex >= boardSize) return;

    if(chessBoard[rowIndex][colIndex] == 'k') *checkCnt = *checkCnt + 1;
    else if(chessBoard[rowIndex][colIndex] != '-') return;
    else CheckDiagonalDownRight(chessBoard, rowIndex+1, colIndex+1, checkCnt);
}

void CheckDiagonalDownLeft(char chessBoard[][boardSize], int rowIndex, int colIndex, int *checkCnt){
    if(rowIndex < 0 || rowIndex >= boardSize) return;
    if(colIndex < 0 || colIndex >= boardSize) return;

    if(chessBoard[rowIndex][colIndex] == 'k') *checkCnt = *checkCnt + 1;
    else if(chessBoard[rowIndex][colIndex] != '-') return;
    else CheckDiagonalDownLeft(chessBoard, rowIndex+1, colIndex-1, checkCnt);
}

void CheckVerticallyUp(char chessBoard[][boardSize], int rowIndex, int colIndex, int *checkCnt){
    if(rowIndex < 0 || rowIndex >= boardSize) return;
    if(colIndex < 0 || colIndex >= boardSize) return;

    if(chessBoard[rowIndex][colIndex] == 'k') *checkCnt = *checkCnt + 1;
    else if(chessBoard[rowIndex][colIndex] != '-') return;
    else CheckVerticallyUp(chessBoard, rowIndex-1, colIndex, checkCnt);
}

void CheckVerticallyDown(char chessBoard[][boardSize], int rowIndex, int colIndex, int *checkCnt){
    if(rowIndex < 0 || rowIndex >= boardSize) return;
    if(colIndex < 0 || colIndex >= boardSize) return;

    if(chessBoard[rowIndex][colIndex] == 'k') *checkCnt = *checkCnt + 1;
    else if(chessBoard[rowIndex][colIndex] != '-') return;
    else CheckVerticallyDown(chessBoard, rowIndex+1, colIndex, checkCnt);
}

void CheckHorizontallyLeft(char chessBoard[][boardSize], int rowIndex, int colIndex, int *checkCnt){
    if(rowIndex < 0 || rowIndex >= boardSize) return;
    if(colIndex < 0 || colIndex >= boardSize) return;

    if(chessBoard[rowIndex][colIndex] == 'k') *checkCnt = *checkCnt + 1;
    else if(chessBoard[rowIndex][colIndex] != '-') return;
    else CheckHorizontallyLeft(chessBoard, rowIndex, colIndex-1, checkCnt);
}

void CheckHorizontallyRight(char chessBoard[][boardSize], int rowIndex, int colIndex, int *checkCnt){
    if(rowIndex < 0 || rowIndex >= boardSize) return;
    if(colIndex < 0 || colIndex >= boardSize) return;

    if(chessBoard[rowIndex][colIndex] == 'k') *checkCnt = *checkCnt + 1;
    else if(chessBoard[rowIndex][colIndex] != '-') return;
    else CheckHorizontallyRight(chessBoard, rowIndex, colIndex+1, checkCnt);
}

int main(){

    int row, col, checkCnt, kingIndex[2], chessPieceIndex[2];
    char chessBoard[boardSize][boardSize], temp;

    // Reading in chess board
    for(row = 0; row < boardSize; row++){
        for(col = 0; col < boardSize; col++){
            scanf("%c", &temp);
            chessBoard[row][col] = temp;
            if(temp == 'k'){
                kingIndex[0] = row;
                kingIndex[1] = col;
            }
        }
        if(row != boardSize-1) scanf("%c", &temp);
    }

    // Traversing through the chess board
    for(row = 0; row < boardSize; row++){
        for(col = 0; col < boardSize; col++){
            temp = chessBoard[row][col];
            chessPieceIndex[0] = row;
            chessPieceIndex[1] = col;

            if(temp == 'P') CheckPawn(kingIndex, chessPieceIndex, &checkCnt);
            if(temp == 'N') CheckKnight(kingIndex, chessPieceIndex, &checkCnt);
            if(temp == 'B' || temp == 'Q'){
                CheckDiagonalUpLeft(chessBoard, row-1, col-1, &checkCnt);
                CheckDiagonalUpRight(chessBoard, row-1, col+1, &checkCnt);
                CheckDiagonalDownLeft(chessBoard, row+1, col-1, &checkCnt);
                CheckDiagonalDownRight(chessBoard, row+1, col+1, &checkCnt);
            }
            if(temp == 'R' || temp == 'Q'){
                CheckVerticallyUp(chessBoard, row-1, col, &checkCnt);
                CheckVerticallyDown(chessBoard, row+1, col, &checkCnt);
                CheckHorizontallyRight(chessBoard, row, col+1, &checkCnt);
                CheckHorizontallyLeft(chessBoard, row, col-1, &checkCnt);
            }
        }
    }

    printf("%d\n", checkCnt);

    return 0;
}
