#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>
using namespace std;
#define MAX_SIZE 100
int INF = INT_MAX; // int의 최댓값. weight의 초기값.
int visited[MAX_SIZE] = {0}; // dfs에서 방문했는지 체크하는 배열.
int dfs_cnt = 0; // dfs의 합
int selected[MAX_SIZE]; // mst에서 방문했는지 체크하는 배열
int distancee[MAX_SIZE]; // mst에서 거리를 저장하는 배열

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
            g->arr[i][j] = INF; // INF로 weight 초기화
        }
    }
}

// 엣지 삽입
void insert_edge(GraphType *g, int n1, int n2, int w)
{
    g->n++;
    g->arr[n1][n2] = w;
    g->arr[n2][n1] = w;
}

// weight 변경
void c_weight(GraphType *g, int n1, int n2, int w)
{
    if (g->arr[n1][n2] != INF)
    {
        g->arr[n1][n2] = w;
        g->arr[n2][n1] = w;
    }
}

// 초기 그래프 세팅
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

// 메뉴 출력
void showmenu()
{
    printf("1. Edge 추가\n2. Weight 변경\n3. Weight 비교\n4. 종료\n");
}

// 엣지 추가
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

// weight 변경 입력 함수 -> c_weight
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

// DFS 출력
void dfs_print(GraphType* g, int v) // v가 시작
{
    visited[v] = 1;
    printf("%d ", v);
    for(int w = 0; w < g->n; w++)
    {
        if(g->arr[v][w] != INF && !visited[w])
        {
            dfs_cnt += g->arr[v][w];
            dfs_print(g, w);
        }
    }
}

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n)
{
    int v, i;
    for (i = 0; i <n; i++)
        if (!selected[i]) {
            v = i;
            break;
        }
    for (i = 0; i < n; i++)
        if (!selected[i] && (distancee[i] < distancee[v])) v = i;
    return (v);
}

// prim mst 출력
void primMST(GraphType* g, int s)
{
    int i, u, v;
    int cnt = 0;

    for (u = 0; u<g->n; u++)
        distancee[u] = INF;
    distancee[s] = 0;
    for (i = 0; i<g->n; i++) {
        u = get_min_vertex(g->n);
        selected[u] = 1;
        if (distancee[u] == INF)
        {
            printf("= %d", cnt); // prim mst의 weight 합 출력
            return;
        }
        printf("%d ", u);
        cnt += distancee[u];
        for (v = 0; v<g->n; v++)
            if (g->arr[u][v] != INF)
                if (!selected[v] && g->arr[u][v]< distancee[v])
                    distancee[v] = g->arr[u][v];
    }
}

// weight 비교 함수
void compare_weight(GraphType *g)
{
    int n;
    printf("시작점: ");
    scanf("%d", &n);

    printf("DFS: ");
    dfs_print(g, n);
    printf("= %d", dfs_cnt); // dfs의 weight 합 출력
    printf("\n");

    printf("MST: ");
    primMST(g, n);
    printf("\n");

    //초기화
    dfs_cnt = 0;
    memset(visited, 0, sizeof(visited));
    memset(distancee, 0, sizeof(distancee));
    memset(selected, 0, sizeof(selected));
}

// 메뉴 함수
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

// 메인 함수
int main()
{
    GraphType *g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    init_insert(g);
    menu(g);

    return (0);
}