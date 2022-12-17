#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <memory.h>
#include <limits.h>
#include <algorithm>
using namespace std;
#define MAX_SIZE 100
#define V 11
int visited[MAX_SIZE] = {0};
int dfs_cnt = 0;
int mst_cnt = 0;

typedef struct GraphType
{
    int n;
    int arr[MAX_SIZE][MAX_SIZE];
}GraphType;

void init(GraphType *g)
{
    g->n = 0;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            g->arr[i][j] = 0;
        }
    }
}

int insert_ver(GraphType *g)
{
    if (g->n > 10)
    {
        printf("over 10\n");
        return (-1);
    }
    g->n++;
    return (g->n);
}

void insert_edge(GraphType *g, int n1, int n2, int w)
{
    //int cnt = insert_ver(g);
    //if (cnt != -1)
    //{
    g->n++;
    g->arr[n1][n2] = w;
    g->arr[n2][n1] = w;
    //}
}

void c_weight(GraphType *g, int n1, int n2, int w)
{
    if (g->arr[n1][n2] != 0)
    {
        g->arr[n1][n2] = w;
        g->arr[n2][n1] = w;
    }
}

void init_insert(GraphType *g)
{
    insert_edge(g,0,1,1);
    insert_edge(g,0,4,1);
    insert_edge(g,0,5,1);
    insert_edge(g,1,2,5);
    insert_edge(g,2,3,6);
    insert_edge(g,2,5,4);
    insert_edge(g,3,4,3);
}

void showmenu()
{
    printf("1. Edge 추가\n2. Weight 변경\n3. Weight 비교\n4. 종료\n입력: ");
}

void add_edge(GraphType *g)
{
    int n1, n2, w;
    int cnt = 0;
    while (1)
    {
        scanf("%d %d %d", &n1, &n2, &w);
        if (n1 == -1 && n2 == -1)
            break;
        insert_edge(g, n1, n2, w);
        cnt++;
    }
    printf("에지 %d개 추가 완료\n", cnt);
}

void change_weight(GraphType *g)
{
    int n1, n2, w;
    int cnt = 0;
    while (1)
    {
        scanf("%d %d %d", &n1, &n2, &w);
        if (n1 == -1 && n2 == -1 && w == -1)
            break;
        c_weight(g, n1, n2, w);
        cnt++;
    }
    printf("Weight %d개 변경 완료\n", cnt);
}

void dfs_print1(GraphType* g, int u, int v){
    visited[u] = 1;
    printf("%d ", u);
    for(int w = 0; w < g->n; w++)
    {
        if(g->arr[u][w] && !visited[w])
        {
            dfs_print1(g, w, v);
        }
    }
}


void dfs_print(GraphType *g, int n) // n이 시작점
{
    stack<int> s;
    s.push(n);
    visited[n] = 1;

    int w = 0;
    while (!s.empty())
    {
        n = s.top();
        s.pop();
        printf("%d ", n);

        for (w = 0; w < MAX_SIZE; w++)
        {
            if (g->arr[n][w] && !visited[w])
            {
                s.push(w);
                visited[w] = 1;

            }
        }
        //끝까지 갔는데 n2 못찾았으면 pop시키고 다시 탐색.
    }
    //stack에 경로만 담아두고 pop시키면서 출력하기
}


int minKey(int key[], bool mstSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
    {
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
        //printf("%d %d %d\n", v, min, min_index);
    }

    return min_index;
}

int parent[V];
int temp[100][100];
void printMST(int parent[], int n, GraphType *g)
{
    int cnt = 0;
    memset(temp, 0, sizeof(temp));

    //printf("Edge   Weight\n");
    for (int i = 1; i < V; i++)
    {
        //printf("%d ", i);
        //printf("%d - %d    %d \n", parent[i], i, g->arr[i][parent[i]]);
        int w = g->arr[i][parent[i]];
        if (w != 0)
        {
            //printf("%d %d\n", w, i);
            temp[w][i] = 1;
            cnt += w;
        }
    }

    //printf("%d ", n);
    for (int j = 0; j < 100; j++)
    {
        for (int k = 0; k < 100; k++)
        {
            if (temp[j][k] == 1)
                printf("%d ", k);
        }
    }
    printf("= %d\n", cnt);
}

void primMST(GraphType *g, int n) // n이 시작점
{
    //int parent[V];
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V-1; count++)
    {
        int u = minKey(key, mstSet);

        mstSet[u] = true;

        for (int v = 0; v < V; v++)

            if (g->arr[u][v] && mstSet[v] == false && g->arr[u][v] <  key[v])
                parent[v]  = u, key[v] = g->arr[u][v];
    }

    printf("%d ", n);
    printMST(parent, V, g);
}


void compare_weight(GraphType *g)
{
    int n;
    printf("시작점: ");
    scanf("%d", &n);

    printf("DFS: ");
    dfs_print1(g,g->n, n);
    printf("\n");

    printf("MST: ");
    primMST(g, n);
    printf("\n");
}

void menu(GraphType *g)
{
    int order;
    showmenu();
    while (1)
    {
        printf("입력: ");
        scanf("%d", &order);
        switch(order)
        {
            case 1:
                add_edge(g);
                break;
            case 2:
                change_weight(g);
                break;
            case 3:
                compare_weight(g);
                break;
            case 4:
                printf("BYE\n");
                return ;
            default:
                printf("wrong order\n");
        }
        printf("\n");
    }
}
int main()
{
    GraphType *g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    init_insert(g);
    menu(g);

    return (0);
}
