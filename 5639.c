#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM 10000

typedef struct node
{
    int data;
    struct node *llink, *rlink;
}Node;

int *inputNum()
{
    int *arr = (int *)malloc(sizeof(int)*MAX_NUM);
    int num;
    for (int i = 0; i < MAX_NUM; i++)
    {
        // End of File or ctrl + Z 를 만났을 때까지 입력받도록 (문제에 반복 횟수가 없음)
        if (scanf("%d", &num) == EOF)
        {
            arr[i] = -1; // -1 입력
            break;
        }
        else
            arr[i] = num;
    }
    return (arr);
}

Node *makeNode(int *arr, int i)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = arr[i];
    newNode->llink = NULL;
    newNode->rlink = NULL;

    return (newNode);
}

Node *makeBTree(int *arr)
{
    Node *root = makeNode(arr, 0); // 루트 노드 생성

    for (int i = 1; i < MAX_NUM; i++)
    {
        if (arr[i] == -1)
            break;

        Node *newNode = makeNode(arr, i); // 새로운 노드 생성
        Node *curr = root;
        while (1) {
            if (newNode->data < curr->data) { // 새로운 값이 현재 노드 값보다 작으면 왼쪽으로
                if (curr->llink == NULL) {
                    curr->llink = newNode;
                    break;
                }
                curr = curr->llink;
            }
            else { // 새로운 값이 현재 노드 값보다 크면 오른쪽으로
                if (curr->rlink == NULL) {
                    curr->rlink = newNode;
                    break;
                }
                curr = curr->rlink;
            }
        }
    }
    free(arr);
    return (root);
}

void printPostOrder(Node *root)
{
    if (root == NULL)
        return ;
    printPostOrder(root->llink);
    printPostOrder(root->rlink);
    printf("%d\n", root->data);
}

int main(int argc, char *argv[])
{
    int *arr;
    Node *root;

    arr = inputNum(); // 값을 입력받아서 arr에 저장
    root = makeBTree(arr); // arr를 가지고 Binary Tree 만듦. root를 반환
    printPostOrder(root); // 만들어진 Binary Tree를 후위순회로 돌면서 출력

    return (0);
}