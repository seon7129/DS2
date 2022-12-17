#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <sys/time.h>

//swap 교환
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

//Bubble Sort
void BubbleSort(int arr[], int n)
{
    int i, j, temp;
    for (i = n-1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (arr[j]>arr[j+1])
                SWAP(arr[j], arr[j+1], temp);
        }
    }
}

//Insertion Sort
void InsertionSort(int arr[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        for(j = i-1; j >= 0 && arr[j] > key; j--)
            arr[j+1] = arr[j];
        arr[j+1] = key;
    }
}

//Selection Sort
void SelectionSort(int arr[], int n)
{
    int i,j, least, temp;
    for (i = 0; i < n-1; i++)
    {
        least = i;
        for(j = i+1; j < n; j++)
            if(arr[j]<arr[least]) least = j;
        SWAP(arr[i], arr[least], temp);
    }
}

//시작 시간과 끝나는 시간을 받아서 걸린 시간을 구하는 함수
float checkTime(struct timeval * start, struct timeval * end)
{
    float result = (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec); // 초+마이크로초
    return (result);
}

//배열을 출력
void printArr(int arr[], int size)
{
    if (size <= 30) // 입력값이 30 이하일 경우
    {
        for (int i = 0; i < size; i++)
            printf("%d ", arr[i]);
    }
    else // 입력값이 30 초과일 경우
    {
        for (int i = 0; i < 10; i++)
            printf("%d ", arr[i]);
    }
    printf("\n");
}

//결과 출력
void showResult(int arr[], int size)
{
    struct timeval start, end;

    int *arr1 = (int*)malloc(sizeof(int)*size);
    memcpy(arr1, arr, sizeof(int)*size); // 랜덤하게 만든 배열을 복사
    gettimeofday(&start, NULL); //시작시간
    BubbleSort(arr1, size); //버블정렬
    gettimeofday(&end, NULL); //종료시간
    printf("Bubble Sort: %.3f초 ", checkTime(&start, &end)); //시간 출력
    printArr(arr1, size); //정렬된 배열 출력

    int *arr2 = (int*)malloc(sizeof(int)*size);
    memcpy(arr2, arr, sizeof(int)*size); // 랜덤하게 만든 배열을 복사
    gettimeofday(&start, NULL); //시간시간
    InsertionSort(arr2, size); //삽입정렬
    gettimeofday(&end, NULL); //종료시간
    printf("Insertion Sort: %.3f초 ", checkTime(&start, &end)); //시간 출력
    printArr(arr2, size); //정렬된 배열 출력

    int *arr3 = (int*)malloc(sizeof(int)*size);
    memcpy(arr3, arr, sizeof(int)*size); // 랜덤하게 만든 배열을 복사
    gettimeofday(&start, NULL); //시작시간
    SelectionSort(arr3, size); //선택정렬
    gettimeofday(&end, NULL); //종료시간
    printf("Selection Sort: %.3f초 ", checkTime(&start, &end)); //시간 출력
    printArr(arr3, size); //정렬된 배열 출력
}

//랜덤한 배열 생성
void makeSrandArr(int arr[], int size)
{
    srand(time(NULL));
    for(int i = 0; i < size; i++)
        arr[i] = rand()%(size+1); // 0이상 사용자입력값 이하

    printf("생성배열: ");
    printArr(arr, size); //생성된 배열 출력
}

int main()
{
    int size;
    printf("Input size: ");
    scanf("%d", &size); // 사용자 입력값 받기
ㅍㅍㅍㅍㅍㅍㅍㅍㅍㅍㅍ
    int arr[size];
    makeSrandArr(arr, size);
    showResult(arr, size);
}
