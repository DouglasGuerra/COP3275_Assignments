#include <stdlib.h>
#include <stdio.h>

void printArray(int arr[], int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertionSort(int arr[], int size){
    int i, j;

    for(i = 0; i < size-1; i++){

        while(i >= 0 && arr[i+1] < arr[i]){
            int temp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = temp;
            i--;
        }
    }
}

int main(){

    int *arr, *temp, n;

    scanf("%d", &n);
    arr = malloc(sizeof(int) * n);

    for(temp = arr; temp < arr+n; temp++){
        scanf("%d", temp);
    }

    printArray(arr, n);
    insertionSort(arr, n);
    printArray(arr, n);

    free(arr);

    return 0;
}
