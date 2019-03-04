#include <stdio.h>

void printArray(int arr[], int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void merge(int arr[], int left, int middle, int right){

    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    int tempLeft[leftSize], tempRight[rightSize];

    int i;
    for(i = 0; i < leftSize; i++){
        tempLeft[i] = arr[left + i];
    }

    for(i = 0; i < rightSize; i++){
        tempRight[i] = arr[middle + 1 + i];
    }

    int leftIndex = 0;
    int rightIndex = 0;
    int arrIndex = left;
    while(leftIndex < leftSize && rightIndex < rightSize){
        if(tempLeft[leftIndex] < tempRight[rightIndex]){
            arr[arrIndex] = tempLeft[leftIndex];
            leftIndex++;
        }
        else{
            arr[arrIndex] = tempRight[rightIndex];
            rightIndex++;
        }
        arrIndex++;
    }

    while(leftIndex < leftSize){
        arr[arrIndex] = tempLeft[leftIndex];
        leftIndex++;
        arrIndex++;
    }

    while(rightIndex < rightSize){
        arr[arrIndex] = tempRight[rightIndex];
        arrIndex++;
        rightIndex++;
    }
}

void mergeSort(int arr[], int left, int right){
    int middle;

    if(left >= right) return;
    middle = (left + right) / 2;
    mergeSort(arr, left, middle);
    mergeSort(arr, middle+1, right);
    merge(arr, left, middle, right);
}


int main(){

    int n, i;
    scanf("%d\n", &n);

    int arr[n];
    for(i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    printArray(arr, n);
    mergeSort(arr, 0, n-1);
    printArray(arr, n);

    return 0;
}
