#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
}Node;

// 노드 하나를 생성해주는 함수
Node *makeNode(int data, Node *left, Node *right)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->left = left;
    newNode->right = right;
    newNode->data = data;

    return (newNode);
}

// 트리를 만드는 함수
Node *make_linked_tree()
{
    Node *root = makeNode(1, NULL, NULL);
    root->left = makeNode(2, makeNode(4, NULL, NULL), makeNode(5, NULL, NULL));
    //root->left = makeNode(2, makeNode(4, NULL, NULL), NULL);
    root->right = makeNode(3, makeNode(6, NULL, makeNode(8, NULL, NULL)), makeNode(7, NULL, NULL));

    return (root);
}

// 전위순회 재귀
void preOrder(Node *root)
{
    if (root == NULL)
        return ;
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

// 전위순회 재귀 프린트 포맷을 위한 함수
void pre_order(Node *root)
{
    printf("[Pre order] ");
    preOrder(root);
    printf("\n");
}

// 이진트리의 높이를 구하기 위한 함수
int cntHeight(Node *root)
{
    int height = 0;
    if (root)
        height = 1 + max(cntHeight(root->left), cntHeight(root->right));
    return (height);
}

// 노드로 이루어진 트리를 이용해 배열 트리로 만드는 함수
int *getTreeArray(Node *root)
{
    int h = cntHeight(root);
    int *arr = (int*)malloc(sizeof(int)*pow(2,h));
    for (int i = 0; i < pow(2,h); i++)
        arr[i] = 0; // 0으로 초기화
    int idx = 1;

    queue<Node*> q; // 노드를 저장하는 큐
    queue<int> qidx; // 그 노드의 인덱스를 저장하는 큐
    q.push(root);
    qidx.push(idx);
    arr[idx] = root->data;

    while (!q.empty())
    {
        Node *curr = q.front();
        int frontIdx = qidx.front();
        if (curr->left)
        {
            q.push(curr->left);
            qidx.push(frontIdx*2); // 왼쪽 자식은 root * 2
            arr[frontIdx*2] = curr->left->data;
        }
        if (curr->right)
        {
            q.push(curr->right);
            qidx.push(frontIdx*2+1); // 오른쪽 자식은 root * 2 + 1
            arr[frontIdx*2+1] = curr->right->data;
        }
        q.pop();
        qidx.pop();
    }

    return (arr);
}

// 트리의 최대 너비를 구하는 함수
int get_max_width(Node *root)
{
    int h = cntHeight(root); // 트리 높이
    int *arr = getTreeArray(root); // 배열 트리
    int width = 0;
    int maxWidth = 0;

    for (int i = 1; i <= h; i++)
    {
        for (int j = pow(2,i-1); j <= pow(2,i)-1; j++) // 동일한 레벨 내에서
        {
            if (arr[j] != 0)
                width++;
        }
        if (width > maxWidth)
        {
            maxWidth = width;
            width = 0;
        }
    }

    return (maxWidth);
}

// level order를 출력하는 함수
void print_leveled_view1(Node *root)
{
    int h = cntHeight(root); // 트리 높이
    int *arr = getTreeArray(root); // 배열 트리

    printf("[Leveled View1]");
    for (int i = 0; i < pow(2,h); i++)
    {
        for (int j = 1; j <= h; j++)
        {
            if (i == pow(2,j-1)) // 한 레벨의 시작 부분에서
                printf("\n%d: ", j);
        }
        if (arr[i] != 0)
            printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    Node *root = make_linked_tree();
    pre_order(root);

    int maxWidth = get_max_width(root);
    printf("[Max Width] = %d\n", maxWidth);

    print_leveled_view1(root);
    //print_leveled_view2(root);

    return (0);
}
