/*
* Determine if a given string is properly parenthesized (every parenthesis has a matching one)
* Input: string conisting of opening and closing parenthesis
* Output: print to console either '1' or '0' if parenthised or not, respectively
*/

#include <stdio.h>
#include <stdlib.h>

int main(){

    int openParenthesisCount = 0;
    int valid = 1, index = 0;
    char *line = (char *) malloc(sizeof(char) * 255);

    scanf("%s", line);
    while(line[index] != '\n'){
        if(line[index] == '(') openParenthesisCount++;
        else if(line[index] == ')') openParenthesisCount--;
        else break;

        if(openParenthesisCount < 0){
            valid = 0;
            break;
        }
        index++;
    }

    if(openParenthesisCount != 0) valid = 0;

    printf("%d\n", valid);

    free(line);
    return 0;
}
