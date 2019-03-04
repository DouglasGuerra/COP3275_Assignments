#include <stdio.h>

#define boardSize 8
#define True 1
#define False 0

int ValidPosition(int row, int col){
    if(row < 0 || row >= boardSize) return False;
    if(col < 0 || col >= boardSize) return False;
    return True;
}

int EmptyCell(char piece){
    return ((piece == '-') ? True : False);
}

void CheckForQueenAndRook(char chessPiece, int *checkCnt){
    if(chessPiece == 'Q' || chessPiece == 'R') *checkCnt = *checkCnt + 1;
}

void CheckForQueenAndBishop(char chessPiece, int *checkCnt){
    if(chessPiece == 'Q' || chessPiece == 'B') *checkCnt = *checkCnt + 1;
}

void CheckVerticallyUp(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;

    if(EmptyCell(chessBoard[row][col]) == True) CheckVerticallyUp(chessBoard, row-1, col, checkCnt);
    CheckForQueenAndRook(chessBoard[row][col], checkCnt);
}

void CheckVerticallyDown(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;

    if(EmptyCell(chessBoard[row][col]) == True) CheckVerticallyDown(chessBoard, row+1, col, checkCnt);
    CheckForQueenAndRook(chessBoard[row][col], checkCnt);
}

void CheckHorizontallyRight(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;

    if(EmptyCell(chessBoard[row][col]) == True) CheckHorizontallyRight(chessBoard, row, col+1, checkCnt);
    CheckForQueenAndRook(chessBoard[row][col], checkCnt);
}

void CheckHorizontallyLeft(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;

    if(EmptyCell(chessBoard[row][col]) == True) CheckHorizontallyLeft(chessBoard, row, col-1, checkCnt);
    CheckForQueenAndRook(chessBoard[row][col], checkCnt);
}

void CheckDiagonalUpRight(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;

    if(EmptyCell(chessBoard[row][col]) == True) CheckDiagonalUpRight(chessBoard, row-1, col+1, checkCnt);
    CheckForQueenAndBishop(chessBoard[row][col], checkCnt);
}

void CheckDiagonalUpLeft(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;

    if(EmptyCell(chessBoard[row][col]) == True) CheckDiagonalUpLeft(chessBoard, row-1, col-1, checkCnt);
    CheckForQueenAndBishop(chessBoard[row][col], checkCnt);
}

void CheckDiagonalDownRight(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;

    if(EmptyCell(chessBoard[row][col]) == True) CheckDiagonalDownRight(chessBoard, row+1, col+1, checkCnt);
    CheckForQueenAndBishop(chessBoard[row][col], checkCnt);
}

void CheckDiagonalDownLeft(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;

    if(EmptyCell(chessBoard[row][col]) == True) CheckDiagonalDownLeft(chessBoard, row+1, col-1, checkCnt);
    CheckForQueenAndBishop(chessBoard[row][col], checkCnt);
}

void CheckForPawn(char chessBoard[][boardSize], int kingRow, int kingCol, int *checkCnt){
    int index, pawnCheck = 2;
    int pawnRow[] = {1, 1}, pawnCol[] = {1, -1};

    for(index = 0; index < pawnCheck; index++){
        int row = pawnRow[index];
        int col = pawnCol[index];
        if(chessBoard[kingRow+row][kingCol+col] == 'P') *checkCnt = *checkCnt + 1;
    }
}

void CheckForKnight(char chessBoard[][boardSize], int kingRow, int kingCol, int *checkCnt){
    int index, knightCheck = 8;
    int knightRow[] = {-1,-1,1,1,2,2,2,2}, knightCol[] = {2, -2,2,-2,1,-1,1,-1};

    for(index = 0; index < knightCheck; index++){
        int row = knightRow[index];
        int col = knightCol[index];
        if(chessBoard[kingRow+row][kingCol+col] == 'N') *checkCnt = *checkCnt + 1;
    }
}

int main(){
    char temp;
    int row, col, checkCnt, kingRowIndex, kingColIndex;
    char chessBoard[boardSize][boardSize];

    // Reading chess board from console
    for(row = 0; row < boardSize; row++){
        for(col = 0; col < boardSize; col++){
            scanf("%c", &temp);
            chessBoard[row][col] = temp;
            if(temp == 'k'){
                kingRowIndex = row;
                kingColIndex = col;
            }
        }
        if(row != boardSize-1) scanf("%c", &temp);
    }

    checkCnt = 0;
    CheckVerticallyUp(chessBoard, kingRowIndex-1, kingColIndex, &checkCnt);
    CheckVerticallyDown(chessBoard, kingRowIndex+1, kingColIndex, &checkCnt);
    CheckHorizontallyRight(chessBoard, kingRowIndex, kingColIndex+1, &checkCnt);
    CheckHorizontallyLeft(chessBoard, kingRowIndex, kingColIndex-1, &checkCnt);

    CheckDiagonalUpLeft(chessBoard, kingRowIndex-1, kingColIndex-1, &checkCnt);
    CheckDiagonalUpRight(chessBoard, kingRowIndex-1, kingColIndex+1, &checkCnt);
    CheckDiagonalDownLeft(chessBoard, kingRowIndex+1, kingColIndex-1, &checkCnt);
    CheckDiagonalDownRight(chessBoard, kingRowIndex+1, kingColIndex+1, &checkCnt);

    CheckForPawn(chessBoard, kingRowIndex, kingColIndex, &checkCnt);
    CheckForKnight(chessBoard, kingRowIndex, kingColIndex, &checkCnt);

    printf("%d\n", checkCnt);

    return checkCnt;
}
