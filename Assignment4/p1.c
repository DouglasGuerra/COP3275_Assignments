/*
* This problem takes in a string and then outputs the string in reverse
* Input: char array
* Output: char array in reverse
*/

#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_STRING_LENGTH 255
#define DEFAULT_WORDS_IN_A_STRING 100

void EmptyOutStrings(char *string, int size){
    int index;
    for(index = 0; index < size; index++)
        string[index] = 0;
}

int main(){

    char readInChar;
    char string[DEFAULT_STRING_LENGTH];
    char wordsInString[DEFAULT_WORDS_IN_A_STRING][DEFAULT_STRING_LENGTH];
    int stringSize = 0, wordsStored = 0;

    // Reading in line and storing them in an array
    EmptyOutStrings(string, DEFAULT_STRING_LENGTH);
    scanf("%c", &readInChar);
    while(readInChar != '\n'){
        if(readInChar == ' '){
            sprintf(wordsInString[wordsStored++], "%s", string);
            EmptyOutStrings(string, stringSize);
            stringSize = 0;
        }
        else{
            string[stringSize++] = readInChar;
        }
        scanf("%c", &readInChar);
    }
    if(stringSize > 0) sprintf(wordsInString[wordsStored++], "%s", string);
    EmptyOutStrings(string, DEFAULT_STRING_LENGTH);

    // Reversing the words in the string
    int index = 0;
    sprintf(string, "%s", wordsInString[wordsStored-1]);
    for(index = wordsStored-2; index >= 0; index--)
        sprintf(string, "%s %s", string, wordsInString[index]);

    printf("%s\n", string);
    return 0;
}
