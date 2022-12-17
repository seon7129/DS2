#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char data;
    struct node *next;
    struct node *prev;
}Node;

Node *initNode(); // head 초기화
void inputNode(int i, Node *h); // 입력받을 때. add, delete와 연결됨
void addNode(Node *curr, char data); // 노드 추가
Node *deleteNode(Node *curr); // 노드 삭제. 현재 커서 위치 반환
void printFreeNode(Node *h); // 결과 출력하고 노드 전체 삭제

int main(int argc, char *argv[])
{
    int num;
    scanf("%d", &num);
    for (int i = 0; i < num; i++)
    {
        Node *h = initNode();
        inputNode(i, h);
        printFreeNode(h);
    }

    return (0);
}

Node *initNode()
{
    Node *head = (Node *)malloc(sizeof(Node));
    head->next = NULL;
    head->prev = NULL;

    return (head);
}

void inputNode(int i, Node *h)
{
    Node *curr = h; // 커서

    while (1)
    {
        char data;
        if (i == 0) // 제일 처음 숫자 입력받을 때 개행이 data로 입력되는 것 방지
        {
            scanf(" %c", &data);
            i++;
        }
        else
            scanf("%c", &data);
        if (data == 10) // enter 이라면
            break;
        else if (data == 60) // < 이라면
        {
            if (curr->prev != NULL)
                curr = curr->prev;
        }
        else if (data == 62) // > 이라면
        {
            if (curr->next != NULL)
                curr = curr->next;
        }
        else if (data == 45) // - 이라면
        {
            curr = deleteNode(curr);
        }
        else    // 그외 영어 대소문자, 숫자 라면
        {
            addNode(curr, data);
            curr = curr->next;
        }
    }
}

void addNode(Node *curr, char data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->data = data;

    if (curr->next == NULL) // 커서가 맨 마지막 노드에 위치해 있을 때
    {
        curr->next = newNode;
        newNode->prev = curr;
    }
    else // 커서가 중간에 위치해 있을 떄
    {
        curr->next->prev = newNode;
        newNode->next = curr->next;
        curr->next = newNode;
        newNode->prev = curr;
    }
}

Node *deleteNode(Node *curr)
{
    Node *prevNode = curr;

    if (prevNode->prev != NULL) // 커서가 헤더를 가리키지 않을 때
    {
        prevNode = prevNode->prev;
        if (prevNode->next->next == NULL) // 커서(curr)가 맨 마지막 노드에 위치해 있을 때
        {
            curr->prev = NULL;
            prevNode->next = NULL;
            free(curr);
        }
        else    // 커서(curr)가 중간 노드에 위치해 있을 때
        {
            prevNode->next = curr->next;
            curr->next->prev = prevNode;
            curr->next = NULL;
            curr->prev = NULL;
            free(curr);
        }
    }
    return (prevNode);

}

void printFreeNode(Node *h)
{
    Node *curr = h->next;

    if (curr != NULL)
    {
        while (1)
        {
            printf("%c", curr->data);
            if (curr->next == NULL)
            {
                printf("\n");
                break;
            }
            else
            {
                curr = deleteNode(curr);
                curr = curr->next;
            }
        }
    }
    free(h);
}