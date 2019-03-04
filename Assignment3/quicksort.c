#include <stdio.h>
#include <stdlib.h>

void printArray(int *arr, int size){
    int *temp = arr;

    for(temp = arr; temp < arr+size; temp++){
        printf("%d\n", *temp);
    }
}

int partition(int arr[], int left, int right){

    int partNum = arr[left];

    while(left < right){
        while(arr[right] >= partNum && left < right){
            right--;
        }
        if(left >= right) break;
        arr[left++] = arr[right];

        while(arr[left] <= partNum && left < right){
            left++;
        }
        if(left >= right) break;
        arr[right--] = arr[left];
    }

    arr[left] = partNum;

    return left;
}

void quicksort(int arr[], int left, int right){
    int partIndex;

    if(left >= right) return;
    partIndex = partition(arr, left, right);
    quicksort(arr, left, partIndex-1);
    quicksort(arr, partIndex+1, right);
}

int main(){

    int *arr, *temp, n, i;
    scanf("%d", &n);

    arr = malloc(sizeof(int)*n);
    for(temp = arr; temp < arr+n; temp++){
        scanf("%d", temp);
    }

    printArray(arr, n);
    quicksort(arr, 0, n-1);
    printArray(arr, n);

    return 0;
}
