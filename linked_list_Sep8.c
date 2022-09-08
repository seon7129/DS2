#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
    struct node *prev;
}Node;

void printList(Node* list)
{
    for(Node *curr = list; curr != NULL; curr = curr->next)
        printf("%d ", curr->data);
    printf("\n");
}

void printListReverse(Node* list)
{
    Node *curr = list;
    for(; curr->next != NULL; curr = curr->next);
    for (; curr != NULL; curr = curr->prev)
        printf("%d ", curr->data);
    printf("\n");
}

Node *creat_node(int value)
{
    Node *newNode;
    newNode = (Node*) malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    return (newNode);
}

void addList(Node *list, int value)
{
    Node* curr = list;
    //가장 끝까지 간다
    for (;curr != NULL; curr = curr->next);
    //만들고 붙인다
    curr->next = creat_node(value);
    curr->next->prev = curr;
}

int main(int argc, char *argv[])
{
    Node *list = creat_node(10);
    addList(list, 20);
    addList(list, 30);
    addList(list, 40);
    addList(list, 50);

    printList(list);
    printListReverse(list);

    return (0);
}