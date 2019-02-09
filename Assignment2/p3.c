/*
* Write a program that tries to find the number in range [0, 512] that a user has.
* Guess a number and ask the user if the number is greater than or less than the number.
* A negative input by the user means the number the user has is less than the number you printed.
* A postive number means that the number the user has is greater that the number you printed.
* A zero means the program got the number and the program exists
*/

#include <stdio.h>

int main(){

    int mid, userInput = 1;
    int lower = 0, higher = 512;

    while(userInput != 0){
        mid = (higher + lower) / 2;
        printf("%d\n", mid);
        scanf("%d", &userInput);

        if(userInput < 0) higher = mid;
        if(userInput > 0) lower = mid;
    }

    return 0;
}
