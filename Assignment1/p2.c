/*
* Fibonnaci Number
*
* Input is the first and second number of the sequence
* Followed by the Nth element to print out to user
*/

#include <stdio.h>

int main(){

    int fib[2];
    int elem;

    scanf("%d %d", &fib[0], &fib[1]);
    scanf("%d", &elem);

    if(elem == 1) printf("%d\n", fib[0]);
    else if(elem == 2) printf("%d\n", fib[1]);
    else{
        int i;
        for(i = 3; i <= elem; i++){
            int temp = fib[0];
            fib[0] = fib[1];
            fib[1] = temp + fib[1];
        }
        printf("%d\n", fib[1]);
    }


    return 0;
}
