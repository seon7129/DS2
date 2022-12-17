#include <stdio.h>
#include <stdlib.h>

int **arr;
int whiteCnt = 0;
int blueCnt = 0;

int checkColorSame(int x, int y, int size)
{
    int cnt = 0; //1의 개수를 센다
    for (int i = x; i < x+size; i++)
    {
        for (int j = y; j < y+size; j++)
        {
            cnt += arr[i][j];
        }
    }
    return (cnt);
}

void divideArr(int x, int y, int size)
{
    int cnt = checkColorSame(x,y,size);

    if (cnt == 0) // 모두 다 0
        whiteCnt++;
    else if (cnt == size*size) // 모두 다 1
        blueCnt++;
    else //색이 섞여있을 경우 나누어줌
    {
        divideArr(x, y, size/2);
        divideArr(x, y+size/2, size/2);
        divideArr(x+size/2, y, size/2);
        divideArr(x+size/2, y+size/2, size/2);
    }
}

void inputData(int size)
{
    int data;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            scanf("%d", &data);
            arr[i][j] = data;
        }
    }
}

int main()
{
    int size;
    scanf("%d", &size);
    arr = (int **)malloc(sizeof(int*)*size);
    for(int i = 0; i < size; i++)
        arr[i] = (int *)malloc(sizeof(int)*size);

    inputData(size);
    divideArr(0,0,size);
    printf("%d\n%d\n", whiteCnt, blueCnt);

    for(int i = 0; i < size; i++)
        free(arr[i]);
    free(arr);
    return (0);
}
