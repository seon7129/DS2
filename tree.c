//tree
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int data;
  struct node *left;
  struct node *mid;
  struct node *right;
}Node;

Node *AllocNewNode(int value, Node *left, Node *mid, Node *right)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = value;
  node->right = right;
  node->mid = mid;
  node->left = left;

  return (node);
}

int main(void) {
  Node *root = AllocNewNode(1, NULL, NULL, NULL);
  root->left = AllocNewNode(2, AllocNewNode(5, NULL, NULL, NULL), NULL, AllocNewNode(6, NULL, NULL, NULL));
  root->mid = AllocNewNode(3, NULL, NULL, NULL);
  root->right = AllocNewNode(4, NULL, NULL, NULL);

  printf("left %d, ptr %d, right %d\n6 %d\n", root->left->data, root->data, root->right->data, root->left->right->data);

  free(root);

  return (0);
}