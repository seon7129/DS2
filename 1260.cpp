#include <stdio.h>
#include <queue>
#include <memory.h>
#include <stdlib.h>
#define MAX_SIZE 1001
using namespace std;

int visited[MAX_SIZE] = {0};

typedef struct GraphType
{
    int mat[MAX_SIZE][MAX_SIZE];
}GraphType;

void init(GraphType *g)
{
    memset(g, 0, sizeof(*g));
}

void setNums(GraphType *g, int m)
{
    int x,y;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &x, &y); // 간선이 연결하는 두 정점의 번호
        g->mat[x][y] = 1;
        g->mat[y][x] = 1;
    }
}

void dfs(GraphType *g, int n, int v)
{
    printf("%d ", v);
    visited[v] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (g->mat[v][i] && !visited[i]) //현재 정점의 인접정점이고 방문x 라면

            dfs(g, n, i);
    }
}

void bfs(GraphType *g, int n, int v)
{
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(v);
    visited[v] = 1;

    while (!q.empty())
    {
        v = q.front();
        printf("%d ", v);
        q.pop();

        for (int i = 1; i <= n; i++)
        {
            if (g->mat[v][i] && !visited[i]) //현재 정점의 인접정점이고 방문x 라면

            {
                q.push(i);
                visited[i] = 1;
            }
        }
    }
}

int main()
{
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    init(g); // g 초기화

    int n,m,v;
    scanf("%d %d %d", &n, &m, &v); // 정점의 개수, 간선의 개수, 탐색 시작 정점 번호 입력
    setNums(g, m); // 값 입력. v는 탐색 시작 정점 번호

    dfs(g, n, v); // dfs 출력
    printf("\n");
    bfs(g, n, v); // bfs 출력
    printf("\n");

    return (0);
}