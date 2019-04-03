/*
* This problem takes in a string and then outputs the string in reverse
* Input: char array
* Output: char array in reverse
*/

#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_STRING_LENGTH 1024
#define DEFAULT_WORDS_IN_A_STRING 2048

char wordsInString[DEFAULT_WORDS_IN_A_STRING][DEFAULT_STRING_LENGTH];
int wordsStoreIndex = 0;

void StoreAndClearString(char words[][DEFAULT_STRING_LENGTH], char string[], int stringSize){
    if(stringSize > 0){
        int i;
        for(i = 0; i < stringSize; i++){
            words[wordsStoreIndex][i] = string[i];
            string[i] = 0;
        }

        wordsStoreIndex++;
    }
}

int main(){

    char readInChar;
    char string[DEFAULT_STRING_LENGTH] = { 0 };
    char revString[DEFAULT_STRING_LENGTH] = { 0 };
    int stringSize = 0;

    // Reading in line and storing them in an array
    scanf("%c", &readInChar);
    while(readInChar != '\n'){
        if(readInChar == ' '){
            StoreAndClearString(wordsInString, string, stringSize);
            stringSize = 0;
        }
        else{
            string[stringSize++] = readInChar;
        }

        scanf("%c", &readInChar);
    }
    StoreAndClearString(wordsInString, string, stringSize);

    // Print out words in reverse order
    if(wordsStoreIndex > 0){
        int i;
        for(i = wordsStoreIndex-1; i >= 0; i--){
            printf("%s", wordsInString[i]);
            if(i > 0) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
