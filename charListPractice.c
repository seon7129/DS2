#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *value;
    struct node *next;
    struct node *prev;
}Node;

Node *initNode()
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->prev = NULL;
    return (newNode);
}

Node *searchNode(Node *list, char *value)
{
    Node *prev = list;
    for (;prev->next != NULL; prev=prev->next)
    {
        if (strcmp(prev->next->value, value) > 0)
            break;
    }

    return (prev);
}

void addNode(Node *list, char *value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->value = (char *)malloc(strlen(value)+1);
    strcpy(newNode->value, value);

    Node *curr = searchNode(list, value);
    if (curr->next == NULL)
    {
        curr->next = newNode;
        newNode->prev = curr;
    }
    else
    {
        newNode->next = curr->next;
        curr->next->prev = newNode;
        newNode->prev = curr;
        curr->next = newNode;
    }
}

void printNode(Node *list)
{
    Node *curr = list;

    printf("[list] ");
    for (;curr->next != NULL; curr=curr->next)
    {
        printf("%s ", curr->next->value);
    }
    printf("\n[Reverse] ");
    for (;curr->prev != NULL; curr=curr->prev)
    {
        printf("%s ", curr->value);
    }
    printf("\n\n");
}

int main(void)
{
    Node *h = initNode();

    int num = 0;
    printf("1. 삽입 / 2. 삭제 / 3. 종료\n");
    scanf("%d", &num);
    char *value = "a";

    while (num != 3)
    {
        if (num == 1)
        {
            scanf("%s", value);
            addNode(h, value);
            printNode(h);
        }
        else if (num == 2)
        {

        }
        else
        {
            printf("다시 입력하세요\n\n");
        }
        scanf("%d", &num);
    }


    return 0;
}