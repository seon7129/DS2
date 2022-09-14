//binary tree
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
    node->right = right;
    node->left = left;

    return (node);
}

void printTreeRecursive(Node *root) // 보다 느림
{
    if (root == NULL)
        return ;
    printf("%d ", root->data);
    printTreeRecursive(root->left);
    printTreeRecursive(root->right);
}

void printTreeIterative(Node *root)
{
    // stack을 이용해서 backtracking

    //stack<Node*> s;
    //print root
    //move curr pointer to left
    //move curr pointer to right
    //스스로 풀어보기

    //15일 목요일에 링크드리스트 시험
    //-> singlely list의 값을 추가하고 프린트하고

    if (root == NULL)
        return ;
    printf("%d ", root->data);
    printTreeIterative(root->left);
    printTreeIterative(root->right);
}

int main(void) {
    Node *root = AllocNewNode(2, NULL, NULL);
    root->left = AllocNewNode(1, NULL, NULL);
    root->right = AllocNewNode(3, NULL, NULL);
    root->left->left = AllocNewNode(4, NULL, NULL);
    root->left->right = AllocNewNode(5, NULL, AllocNewNode(6, NULL, NULL));

    printTreeRecursive(root);

    free(root);

    return (0);
}