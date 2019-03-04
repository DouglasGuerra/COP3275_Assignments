#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int size){
    int index;
    for(index = 0; index < size; index++){
        printf("%d ", arr[index]);
    }
    printf("\n");
}

void selectionSort(int arr[], int size){
    int i, j, minIndex;

    for(i = 0; i < size-1; i++){
        minIndex = i;

        for(j = i+1; j < size; j++){
            if(arr[j] < arr[minIndex]) minIndex = j;
        }

        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }

}

int main(){

    int *arr, *tempArr, *temp, n;

    scanf("%d", &n);
    arr = malloc(sizeof(int) * n);
    tempArr = malloc(sizeof(int) * n);

    temp = arr;
    for(temp = arr; temp < arr+n; temp++){
        scanf("%d", temp);
    }

    printArray(arr, n);
    selectionSort(arr, n);
    printArray(arr, n);

    free(arr);
}
