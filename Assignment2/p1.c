/*
* Determine if a given string is properly parenthesized (every parenthesis has a matching one)
* Input: string conisting of opening and closing parenthesis
* Output: print to console either '1' or '0' if parenthised or not, respectively
*/

#include <stdio.h>

int main(){

    int openParenthesisCount = 0;
    int valid = 1;
    char current;

    while((scanf("%c", &current)), current != '\n'){
        if(current == '(') openParenthesisCount++;
        else if(current == ')') openParenthesisCount--;

        if(openParenthesisCount < 0){
            valid = 0;
            break;
        }
    }

    if(openParenthesisCount != 0) valid = 0;

    printf("%d\n", valid);

    return 0;
}
