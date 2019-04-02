/*
* In this assignment input is <cmd>whitespace<value>
* <cmd> can be 1 (append) or (-1) prepend <value> to the linked list
* <cmd> 0 is to reverse the linked list
* Output is the linked list in reverse
*/

#include <stdio.h>
#include <stdlib.h>

#define PREPEND_COMMAND -1
#define APPEND_COMMAND 1
#define REVERSE_LINKEDLIST_COMMAND 0

// Creating a linked list node struct
struct LinkedList_t{
    struct LinkedList_t *next;
    int data;
};
typedef struct LinkedList_t Node_t;

Node_t * Create_Node(int data){
    Node_t *node = malloc(sizeof(Node_t));
    node->next = NULL;
    node->data = data;
    return node;
}

void Print_LinkedList(Node_t *head){
    Node_t *temp = head->next;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void Reverse_LinkedList(Node_t *head){
    Node_t *current = head->next;
    Node_t *prev = NULL, *ahead = NULL;

    while(current != NULL){
        ahead = current->next;
        current->next = prev;

        prev = current;
        current = ahead;
    }

    head->next = prev;
}

void Append_Node(Node_t *head, int value){
    Node_t *newNode = Create_Node(value);
    Node_t *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
}

void Prepend_Node(Node_t *head, int value){
    Node_t *newNode = Create_Node(value);
    newNode->next = head->next;
    head->next = newNode;
}

int main(){

    Node_t *head = Create_Node(0);
    // printf("head: %p\n", head);
    int command, value;

    do {
        scanf(" %d", &command);
        if(command == APPEND_COMMAND || command == PREPEND_COMMAND){
            scanf("%d", &value);
            if(command == APPEND_COMMAND) Append_Node(head, value);
            if(command == PREPEND_COMMAND) Prepend_Node(head, value);
        }
        // Print_LinkedList(head);
    } while(command != REVERSE_LINKEDLIST_COMMAND);

    Reverse_LinkedList(head);
    Print_LinkedList(head);

    return 0;
}
