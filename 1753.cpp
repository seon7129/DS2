#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define INF 999999
#define MAX_SIZE 20001

typedef struct GraphType {
    int n;
    int weight[MAX_SIZE][MAX_SIZE];
} GraphType;

int GetMinDistIdx(GraphType *g, int dist[], int s[]) {
    int foundIdx = -1;
    int minValue = INT_MAX;
    for (int i = 1; i <= g->n; i++)
    {
        if (s[i] == TRUE)
            continue;
        if (minValue > dist[i])
        {
            minValue = dist[i];
            foundIdx = i;
        }
    }
    return (foundIdx);
}

void UpdateDist(GraphType *g,int u, int dist[])
{
    for(int i = 1; i <= g->n; i++)
    {
        if(dist[i] > dist[u] + g->weight[u][i])
            dist[i] = dist[u] + g->weight[u][i];
    }
}

void PrintDist(GraphType *g, int dist[], int start)
{
    for (int i = 1; i <= g->n; i++)
    {
        if (start == i)
            printf("0\n");
        else if (dist[i] == INF)
            printf("INF\n");
        else
            printf("%d\n", dist[i]);
    }
}

void shortest_path(GraphType *g, int start)
{
    int s[MAX_SIZE] = {FALSE, };
    int dist[MAX_SIZE] = {INT_MAX, };
    for (int i = 1; i <= g->n; i++)
        dist[i] = g->weight[start][i];
    for(int i = 0; i < g->n; i++)
    {
        int u = GetMinDistIdx(g, dist, s);
        s[u] = TRUE;

        UpdateDist(g, u, dist);
    }

    PrintDist(g, dist, start);
}

void init(GraphType *g)
{
    for (int i = 1; i <= g->n; i++)
    {
        for (int j = 1; j <= g->n; j++)
            g->weight[i][j] = INF;
    }
}

void set_graph(GraphType *g, int n1, int n2, int w)
{
    if (g->weight[n1][n2] == INF)
        g->weight[n1][n2] = w;
}

void get_input(GraphType *g, int e)
{
    int n1, n2, w;
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d %d", &n1, &n2, &w);
        set_graph(g, n1, n2, w);
    }
}

int main(void)
{
    GraphType *g = (GraphType *)malloc(sizeof(GraphType));

    int v, e, start;
    scanf("%d %d %d", &v, &e, &start);
    g->n = v;

    init(g);
    get_input(g, e);

    shortest_path(g, start);

    return (0);
}
