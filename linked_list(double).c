//doubled linked list
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
}Node;

Node *AllocNewNode(int value, Node *left, Node *right)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->right = left;
    node->left = right;

    return (node);
}

int main(void) {
    Node *head = AllocNewNode(2, NULL, NULL);
    head->right = AllocNewNode(3, head, NULL);
    head->left = AllocNewNode(1, NULL, head);

    printf("left %d, ptr %d, right %d\n", node->left->data, node->data, node->right->data);

    free(head);

    return (0);
}