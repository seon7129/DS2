#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <sys/time.h>
#include <algorithm>
using namespace std;

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
int *mSorted; // Merge sort에서 정렬된 리스트를 넣는 배열

// Bubble Sort
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

// Merge Sort에서 합치는 부분
void Merge(int arr[], int left, int mid, int right)
{
    int i, j, k, l; // i는 왼쪽 리스트, j는 오른쪽 리스트, k는 정렬된 리스트
    i = left;
    j = mid+1;
    k = left;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            mSorted[k++] = arr[i++]; // 작다면 왼쪽 리스트에서 가져와 정렬
        else
            mSorted[k++] = arr[j++]; // 크다면 오른쪽 리스트에서 가져와 정렬
    }

    // 남아있는 레코드 일괄 복사
    if (i > mid) // 오른쪽이 남아있으면
    {
        for (l = j; l <= right; l++)
            mSorted[k++] = arr[l];
    }
    else //왼쪽이 남아있으면
    {
        for (l = i; l <= mid; l++)
            mSorted[k++] = arr[l];
    }

    for (l = left; l <= right; l++)
        arr[l] = mSorted[l];
}

// Merge Sort
void MergeSort(int arr[], int left, int right)
{
    int mid;
    if (left < right)
    {
        mid = (left + right)/2;
        MergeSort(arr, left, mid);
        MergeSort(arr, mid+1, right);
        Merge(arr, left, mid, right);
    }
}

// Quick Sort에서 정렬하는 부분
int partition(int arr[], int left, int right)
{
    int pivot, temp;
    int low, high;

    low = left;
    high = right+1;
    pivot = arr[left];

    do{
        // arr[low]가 pivot보다 작으면 low 계속 증가
        do {
            low++;
        } while (low <= right && arr[low] < pivot);
        // arr[high]가 pivot보다 크면 high 계속 감소
        do {
            high--;
        } while (high >= left && arr[high] > pivot);
        // 교환
        if (low < high) {
            SWAP(arr[low], arr[high], temp);
        }
    } while (low < high);

    // 교환
    SWAP(arr[left], arr[high], temp);

    // pivot의 위치 반환
    return (high);
}

// Quick Sort
void QuickSort(int arr[], int left, int right)
{
    if (left < right)
    {
        // pivot을 기준으로 비균등 분할
        int q = partition(arr, left, right);
        QuickSort(arr, left, q-1);
        QuickSort(arr, q+1, right);
    }
}

// 걸리는 시간
float checkTime(struct timeval * start, struct timeval * end)
{
    float result = (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
    return (result);
}

// 배열 출력
void printArr(int arr[], int size)
{
    if (size <= 30)
    {
        for (int i = 0; i < size; i++)
            printf("%d ", arr[i]);
    }
    else
    {
        for (int i = 0; i < 10; i++)
            printf("%d ", arr[i]);
    }
    printf("\n");
}

// 결과 보여주는 함수
void showResult(int arr[], int size)
{
    struct timeval start, end;

    printf("정렬 시간:\n");

    int *arr1 = (int*)malloc(sizeof(int)*size);
    memcpy(arr1, arr, sizeof(int)*size);
    gettimeofday(&start, NULL);
    BubbleSort(arr1, size);
    gettimeofday(&end, NULL);
    float result1 = checkTime(&start, &end);
    printf("Bubble Sort: %.1f초 ", result1);
    printArr(arr1, size);

    int *arr2 = (int*)malloc(sizeof(int)*size);
    memcpy(arr2, arr, sizeof(int)*size);
    gettimeofday(&start, NULL);
    MergeSort(arr2, 0, size-1);
    gettimeofday(&end, NULL);
    float result2 = checkTime(&start, &end);
    printf("Merge Sort: %.1f초 ", result2);
    printArr(arr2, size);

    int *arr3 = (int*)malloc(sizeof(int)*size);
    memcpy(arr3, arr, sizeof(int)*size);
    gettimeofday(&start, NULL);
    QuickSort(arr3, 0, size-1);
    gettimeofday(&end, NULL);
    float result3 = checkTime(&start, &end);
    printf("Quick Sort: %.1f초 ", result3);
    printArr(arr3, size);

    int *arr4 = (int*)malloc(sizeof(int)*size);
    memcpy(arr4, arr, sizeof(int)*size);
    gettimeofday(&start, NULL);
    sort(arr4, arr4+size);
    gettimeofday(&end, NULL);
    float result4 = checkTime(&start, &end);
    printf("STL Sort: %.1f초 ", result4);
    printArr(arr4, size);


    printf("성능 비교:\n");

    if (result1 > result3)
        printf("Bubble Sort: 내가 구현한 Quick Sort보다 %f배 느림 (%f/%f=%f)\n", result1/result3, result1, result3, result1/result3);
    else
        printf("Bubble Sort: 내가 구현한 Quick Sort보다 %f배 빠름 (%f/%f=%f)\n", result3/result1, result3, result1, result3/result1);

    if (result2 > result3)
        printf("Merge Sort: 내가 구현한 Quick Sort보다 %f배 느림 (%f/%f=%f)\n", result2/result3, result2, result3, result2/result3);
    else
        printf("Merge Sort: 내가 구현한 Quick Sort보다 %f배 빠름 (%f/%f=%f)\n", result3/result2, result3, result2, result3/result2);

    if (result3 > result4)
        printf("STL Sort: 내가 구현한 Quick Sort보다 %f배 빠름 (%f/%f=%f)\n", result3/result4, result3, result4, result3/result4);
    else
        printf("STL Sort: 내가 구현한 Quick Sort보다 %f배 느림 (%f/%f=%f)\n", result4/result3, result4, result3, result4/result3);


    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
}


// 랜덤으로 배열 생성
void makeSrandArr(int arr[], int size)
{
    srand(time(NULL));
    for(int i = 0; i < size; i++)
        arr[i] = rand()%(size+1);

    printf("생성배열: ");
    printArr(arr, size);
}

int main()
{
    int size;
    printf("Input size: ");
    scanf("%d", &size);
    mSorted = (int *)malloc(sizeof(int)*size);

    int arr[size];
    makeSrandArr(arr, size);
    showResult(arr, size);

    free(mSorted);
    return (0);
}