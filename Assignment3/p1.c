/*
* Compute the elementwise muliplication of two vectors. Then determine if the given vectors are
* perpendicular to each other.
*
* Input:
*   Two int arrays of the same length
* Output:
*   Print to console the elementwise multiplication of the int arrays
*   Print if the arrays are perpendicular
*/

#include <stdio.h>
#include <stdlib.h>

int main(){

    int size, index, temp, sum = 0;
    int *vector;

    scanf("%d", &size);
    vector = (int *) malloc(sizeof(int) * size);

    // First pass getting the values of the first array
    for(index = 0; index < size; index++){
        scanf("%d", &vector[index]);
    }

    // Second pass getting the values of the second array and storing the elementwise multiplication
    for(index = 0; index < size; index++){
        scanf("%d", &temp);
        vector[index] = temp*vector[index];
    }

    // Printing out the vector and keeping the sum of the values
    for(index = 0; index < size; index++){
        sum += vector[index];
        printf("%d", vector[index]);
        if(index != size-1) printf(" ");
    }
    printf("\n");

    if(sum == 0) printf("perpendicular\n");
    else printf("not perpendicular\n");

    return 0;
}
