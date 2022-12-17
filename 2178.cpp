#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;

typedef struct GraphType {
    int **visited;
    char **mat;
}GraphType;

int minDist[101][101];
int n,m = 0;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

GraphType *makeMat(int n, int m)
{
    GraphType *g = (GraphType*)malloc(sizeof(GraphType));
    g->mat = (char**)malloc(sizeof(char*)*n);
    g->visited = (int**)malloc(sizeof(int*)*n);

    int i, j;
    char input;
    for (i = 0; i < n; i++)
    {
        g->mat[i] = (char*)malloc(sizeof(char)*m);
        g->visited[i] = (int*)malloc(sizeof(int)*m);
        for (j = 0; j < m; j++)
        {
            scanf(" %c", &input); // 엔터 받지 않게
            g->mat[i][j] = input;
            g->visited[i][j] = 0;
        }
    }
    return (g);
}

// DFS는 모든 경로를 다 탐색하고 그 중 가장 작은 것을 골라야하기 때문에 비효율적
void BFS(GraphType *g, int x, int y)
{
    minDist[x][y] = 1;
    g->visited[x][y] = 1;

    //pair 써도 될 듯
    queue<int> qx;
    queue<int> qy;
    qx.push(x);
    qy.push(y);

    while (!qx.empty())
    {
        x = qx.front();
        y = qy.front();
        qx.pop();
        qy.pop();

        for (int i = 0; i < 4; i++)
        {
            int tmpX = x + dx[i];
            int tmpY = y + dy[i];

            if (tmpX < 0 || tmpY < 0 || tmpX >= n || tmpY >= m) continue;// 범위 벗어났을 떄
            if (!g->visited[tmpX][tmpY] && g->mat[tmpX][tmpY] == '1')
            {
                minDist[tmpX][tmpY] = minDist[x][y] + 1;
                if (tmpX == n-1 && tmpY == m-1)
                    return ;
                g->visited[tmpX][tmpY] = 1;
                qx.push(tmpX);
                qy.push(tmpY);
            }
        }
    }
}

void freeAll(GraphType *g)
{
    for (int i = 0; i < n; i++)
    {
        free(g->mat[i]);
        free(g->visited[i]);
    }
    free(g);
}

int main()
{
    scanf("%d %d", &n, &m); //행 열

    GraphType *g;
    g = makeMat(n, m);

    BFS(g, 0, 0);
    printf("%d", minDist[n-1][m-1]);

    freeAll(g);

    return (0);
}