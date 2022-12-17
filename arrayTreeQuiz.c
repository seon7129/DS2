#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h> //memset

int heightAsk()
{
    int h;
    printf("tree height? ");
    scanf("%d", &h);

    return (h);
}

int* makeTree(int h)
{
    int* arr = (int*)malloc(sizeof(int) * pow(2,h)); // 인덱스가 1 부터 시작해서 2^h-1이 아니라 2^h
    memset(arr, 0, sizeof(int)*pow(2,h));
    printf("트리 데이터 입력을 시작합니다.\n");
    int pos;
    int data;

    for (int i = 1; i < pow(2,h) ; i++)
    {
        printf("pos, data = ? ");
        scanf("%d %d", &pos, &data);
        if (pos == 0 && data == 0)
            break;
        arr[pos] = data;
    }

    printf("트리 데이터 입력이 완료되었습니다.\n");
    return (arr);
}

void printSpace(int num)
{
    for (int i = 0; i < num; i++)
        printf("   "); // space 3칸
}

void printTree(int *arr, int h)
{
    for (int i = 1; i <= h; i++)
    {
        int cnt = 0;
        for(int idx = 0; idx < h-i; idx++)
            cnt = cnt*2+1; // 0 1 3 7 15 ...

        // 숫자 출력
        printf("Lev%d:  ", i);
        for (int j = pow(2, i-1); j < pow(2, i); j++)
        {
            printSpace(cnt);
            if(j == pow(2,i-1))
                cnt = cnt*2+1;
            if (arr[j] == 0)
                printf(" - ");
            else
                printf(" %d", arr[j]);
        }
        printf("\n");

        cnt = (cnt-1)/2;
        // 엣지 출력
        int k = 0;
        for (; k < pow(2,i-1) && i != h; k++)
        {
            if (k == 0)
                printf("    ");
            printSpace(cnt);
            if(k == 0)
                cnt = cnt*2+1;
            printf("/ ");
            printf("\\");
        }
        if (k != 0)
            printf("\n");
    }
}

void printData(int *arr, int i, int h)
{
    printf("%d: 부모 = ", arr[i]);
    if (i == 1 || arr[i/2] == 0)
        printf("없음");
    else
        printf("%d", arr[i/2]);

    printf(", 왼쪽자식 = ");
    if (arr[i*2] == 0 || i*2 > pow(2,h))
        printf("없음");
    else
        printf("%d", arr[i*2]);

    printf(", 오른쪽 자식 = ");
    if (arr[i*2+1] == 0 || i*2+1 > pow(2,h))
        printf("없음");
    else
        printf("%d", arr[i*2+1]);

    printf(", 형제노드 = ");
    if (i == 1) // 루트 노드
        printf("없음\n");
    else if (i % 2 == 0 && arr[i+1] == 0) // i가 짝수
        printf("없음\n");
    else if (i % 2 == 0 && arr[i+1] != 0)
        printf("%d\n", arr[i+1]);
    else if (i % 2 == 1 && arr[i-1] == 0) // i가 홀수
        printf("없음\n");
    else
        printf("%d\n", arr[i-1]);
}

void endQuiz(int *arr, int h)
{
    int num;

    while (1)
    {
        printf("정보를 알고 싶은 데이터를 입력하세요 (종료 = 999) : ");
        scanf("%d", &num);
        if (num == 999)
            break;
        int i = 1;
        for (; i < pow(2,h) ; i++)
        {
            if (arr[i] == num)
            {
                printData(arr, i, h);
                break;
            }
        }
        if (i == pow(2,h))
            printf("%d: 노드가 존재하지 않습니다.\n", num);
    }
    printf("종료합니다.\n");
    free(arr);
}

void solveQuiz()
{
    int h;
    int *arr;
    h = heightAsk(); // tree의 높이를 입력받음
    arr = makeTree(h); // 데이터를 입력받아 트리를 만듦
    printTree(arr, h); // 트리 모양을 출력함
    endQuiz(arr, h); // 부모, 왼쪽자식, 오른쪽자식, 형제노드에 대한 정보를 출력함

}

int main(int argc, char *argv[])
{
    solveQuiz();
    return (0);
}