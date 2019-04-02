/*
* This program provides two inputs N and M, where N represents the number of nodes
* and M represents the number of edges
* The output is the sum of connected components, if there are multiple components then
* separate their sums by a space.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NEIGHBORS 21

// Node structure
struct Node_t {
    int value;
    bool visited;
    int numNeighbors;
    struct Node_t *neighbors[MAX_NEIGHBORS];
};
typedef struct Node_t Node;

int Get_SumOfConnectedNodes(Node *node){
    // printf("visiting node at location: %p\n", node);
    int sum = 0;
    if(node->visited == false){
        // printf("has not been visited\n");
        sum = node->value;
        node->visited = true;

        int nodeIndex;
        for(nodeIndex = 0; nodeIndex < node->numNeighbors; nodeIndex++){
            sum += Get_SumOfConnectedNodes(node->neighbors[nodeIndex]);
        }
    }

    return sum;
}

bool AreNeighbors(Node *node1, Node *node2){
    int i;
    for(i = 0; i < node1->numNeighbors; i++){
        if(node1->neighbors[i] == node2){
            return true;
        }
    }
    return false;
}

int main(){

    // Getting the number of nodes and edges in the graph
    int numNodes, numEdges;
    scanf("%d %d", &numNodes, &numEdges);

    Node *nodes[numNodes];

    // Filling initial node values as provided by input
    int nodeIndex, nodeValue;
    for(nodeIndex = 0; nodeIndex < numNodes; nodeIndex++){
        scanf(" %d", &nodeValue);
        nodes[nodeIndex] = malloc(sizeof(Node));
        nodes[nodeIndex]->value = nodeValue;
        nodes[nodeIndex]->numNeighbors = 0;
    }

    // Filling out nodes with their given neighbors, as provided by the edge graph
    int startNode, endNode;
    Node *tempStartNode, *tempEndNode;
    for(nodeIndex = 0; nodeIndex < numEdges; nodeIndex++){
        scanf(" %d %d", &startNode, &endNode);
        if(startNode >= 0 && startNode < numNodes && endNode >= 0 && endNode < numNodes && startNode != endNode){
            tempStartNode = nodes[startNode];
            tempEndNode = nodes[endNode];

            if(!AreNeighbors(tempStartNode, tempEndNode) && tempStartNode->numNeighbors < MAX_NEIGHBORS){
                tempStartNode->neighbors[tempStartNode->numNeighbors] = tempEndNode;
                tempStartNode->numNeighbors += 1;
            }

            if(!AreNeighbors(tempEndNode, tempStartNode) && tempEndNode->numNeighbors < MAX_NEIGHBORS){
                tempEndNode->neighbors[tempEndNode->numNeighbors] = tempStartNode;
                tempEndNode->numNeighbors += 1;
            }
        }
    }

    // Iterating through nodes to get the sum of connected components
    bool firstPrint = true;
    for(nodeIndex = 0; nodeIndex < numNodes; nodeIndex++){
        if(nodes[nodeIndex]->visited == false){
            if(firstPrint) firstPrint = false;
            else printf(" ");

            printf("%d", Get_SumOfConnectedNodes(nodes[nodeIndex]));
        }
    }
    printf("\n");

    return 0;
}
