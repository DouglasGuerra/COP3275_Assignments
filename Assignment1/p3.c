/*
* Sacred Number
*
* A number is sacred if it has an even number of zeroes and is divisible by 13
* or it has odd number of zeroes and is divisible by 7
*/

#include <stdio.h>

int main(){

    int input, temp, zeroCount = 0, out = 0;
    scanf("%d", &input);

    //Counting the number of zeroes
    temp = input;
    while(temp != 0){
        if(temp % 10 == 0) zeroCount++;
        temp /= 10;
    }
    
    // Even number of zeroes and divisble by 13
    if(zeroCount % 2 == 0 && input % 13 == 0) out = 1;

    // Odd number of zeros and divisble by 7
    if(zeroCount % 2 == 1 && input % 7 == 0) out = 1;

    printf("%d\n", out);

    return 0;
}
