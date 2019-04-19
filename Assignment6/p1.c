#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int index;
    int value;
} Node_t;

int CompareNodes(const void *firstNode, const void *secondNode){
    const Node_t *fNode = (const Node_t *)firstNode;
    const Node_t *sNode = (const Node_t *)secondNode;

    return ( (fNode->index < sNode->index) ? false : true );
}

void LoadVectorWithInput(int size, Node_t vector[size]){
    int i;
    for(i = 0; i < size; i++)
        scanf(" %d %d", &vector[i].index, &vector[i].value);
}

void PrintVector(int size, Node_t vector[size]){
    if(size > 0){
        int i;
        for(i = 0; i < size; i++) printf("%d %d\n", vector[i].index, vector[i].value);
    }
    else
        printf("\n");
}

int MutliplyVectorsAndStore(int firstVectorSize, Node_t firstVector[], int secondVectorSize, Node_t secondVector[], int outputVectorSize, Node_t outputVector[]){
    int storeIndex = 0;
    int firstVectorIndex = 0, secondVectorIndex = 0;
    while(firstVectorIndex < firstVectorSize && secondVectorIndex < secondVectorSize){
        if(firstVector[firstVectorIndex].index == secondVector[secondVectorIndex].index){
            outputVector[storeIndex].index = firstVector[firstVectorIndex].index;
            outputVector[storeIndex].value = firstVector[firstVectorIndex].value * secondVector[secondVectorIndex].value;
            storeIndex++;
            firstVectorIndex++;
            secondVectorIndex++;
        }
        else if(firstVector[firstVectorIndex].index < secondVector[secondVectorIndex].index)
            firstVectorIndex++;
        else
            secondVectorIndex++;
    }

    return storeIndex;
}

bool IsVectorPerpendicular(int vectorSize, Node_t vector[]){
    int sum = 0;
    int i;
    for(i = 0; i < vectorSize; i++)
        sum += vector[i].value;

    return ((sum == 0) ? true : false);
}

int main(){

    int firstVectorSize, secondVectorSize, outputVectorSize;
    Node_t *firstVector, *secondVector, *outputVector;

    // Getting data for the first vector
    scanf("%d", &firstVectorSize);
    firstVector = (Node_t *) malloc(sizeof(Node_t) * firstVectorSize);
    LoadVectorWithInput(firstVectorSize, firstVector);
    qsort((void *)firstVector, firstVectorSize, sizeof(firstVector[0]), CompareNodes);

    // Getting data for the second vector
    scanf(" %d", &secondVectorSize);
    secondVector = (Node_t *) malloc(sizeof(Node_t) * secondVectorSize);
    LoadVectorWithInput(secondVectorSize, secondVector);
    qsort((void *)secondVector, secondVectorSize, sizeof(secondVector[0]), CompareNodes);

    // Filling output vector with data
    outputVectorSize = (firstVectorSize < secondVectorSize) ? secondVectorSize : firstVectorSize;
    outputVector = (Node_t *) malloc(sizeof(Node_t) * outputVectorSize);
    outputVectorSize = MutliplyVectorsAndStore(firstVectorSize, firstVector, secondVectorSize, secondVector, outputVectorSize, outputVector);

    PrintVector(outputVectorSize, outputVector);
    if(IsVectorPerpendicular(outputVectorSize, outputVector) == true)
        printf("perpendicular\n");
    else
        printf("not perpendicular");

    free(firstVector);
    free(secondVector);
    free(outputVector);

    return 0;
}
