#include <stdio.h>

#define boardSize 8
#define True 1
#define False 0

int ValidPosition(int row, int col){
    if(row < 0 || row >= boardSize) return False;
    else if(col < 0 || col >= boardSize) return False;
    else return True;
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
    else if(EmptyCell(chessBoard[row][col]) == True) CheckVerticallyUp(chessBoard, row-1, col, checkCnt);
    else CheckForQueenAndRook(chessBoard[row][col], checkCnt);
}

void CheckVerticallyDown(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;
    else if(EmptyCell(chessBoard[row][col]) == True) CheckVerticallyDown(chessBoard, row+1, col, checkCnt);
    else CheckForQueenAndRook(chessBoard[row][col], checkCnt);
}

void CheckHorizontallyRight(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;
    else if(EmptyCell(chessBoard[row][col]) == True) CheckHorizontallyRight(chessBoard, row, col+1, checkCnt);
    else CheckForQueenAndRook(chessBoard[row][col], checkCnt);
}

void CheckHorizontallyLeft(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;
    else if(EmptyCell(chessBoard[row][col]) == True) CheckHorizontallyLeft(chessBoard, row, col-1, checkCnt);
    else CheckForQueenAndRook(chessBoard[row][col], checkCnt);
}

void CheckDiagonalUpRight(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;
    else if(EmptyCell(chessBoard[row][col]) == True) CheckDiagonalUpRight(chessBoard, row-1, col+1, checkCnt);
    else CheckForQueenAndBishop(chessBoard[row][col], checkCnt);
}

void CheckDiagonalUpLeft(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;
    else if(EmptyCell(chessBoard[row][col]) == True) CheckDiagonalUpLeft(chessBoard, row-1, col-1, checkCnt);
    else CheckForQueenAndBishop(chessBoard[row][col], checkCnt);
}

void CheckDiagonalDownRight(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;
    else if(EmptyCell(chessBoard[row][col]) == True) CheckDiagonalDownRight(chessBoard, row+1, col+1, checkCnt);
    else CheckForQueenAndBishop(chessBoard[row][col], checkCnt);
}

void CheckDiagonalDownLeft(char chessBoard[][boardSize], int row, int col, int *checkCnt){
    if(ValidPosition(row, col) == False) return;
    else if(EmptyCell(chessBoard[row][col]) == True) CheckDiagonalDownLeft(chessBoard, row+1, col-1, checkCnt);
    else CheckForQueenAndBishop(chessBoard[row][col], checkCnt);
}

void CheckForPawn(char chessBoard[][boardSize], int kingRow, int kingCol, int *checkCnt){
    int index, pawnCheck = 2;
    int pawnRow[] = {1, 1}, pawnCol[] = {1, -1};

    for(index = 0; index < pawnCheck; index++){
        int row = pawnRow[index] + kingRow;
        int col = pawnCol[index] + kingCol;
        if(ValidPosition(row, col) == True){
            if(chessBoard[row][col] == 'P') *checkCnt = *checkCnt + 1;
        }
    }
}

void CheckForKnight(char chessBoard[][boardSize], int kingRow, int kingCol, int *checkCnt){
    int index, knightCheck = 8;
    int knightRow[] = {-1,-1,1,1,2,2,-2,-2}, knightCol[] = {2,-2,2,-2,1,-1,1,-1};

    for(index = 0; index < knightCheck; index++){
        int row = knightRow[index] + kingRow;
        int col = knightCol[index] + kingCol;
        if(ValidPosition(row, col) == True){
            if(chessBoard[row][col] == 'N') *checkCnt = *checkCnt + 1;
        }
    }
}

int main(){
    char temp;
    int row, col, checkCnt, kingRowIndex, kingColIndex;
    char chessBoard[boardSize][boardSize];

    // Reading chess board from console
    kingRowIndex = -1;
    kingColIndex = -1;
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
    printf("%d, %d\n", kingRowIndex, kingColIndex);
    checkCnt = 0;
    if(kingRowIndex != -1 && kingColIndex != -1){
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
    }

    printf("%d\n", checkCnt);

    return 0;
}
