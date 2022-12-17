#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 100001
int parent[MAX];

typedef struct
{
    int u;    // 정점 1
    int v;    // 정점 2
    int weight;  // 간선의 가중치
} element;

typedef struct
{
    element mat[MAX*2];
    int n;
}   GraphType;


void set_init(int n)
{
    int i;
    for (i = 0; i < n; i++)
        parent[i] = -1;
}

int set_find(int curr)
{
    if (parent[curr] == -1)
        return (curr);

    while (parent[curr] != -1)
        curr = parent[curr];
    return (curr);
}

void set_union(int n1, int n2)
{
    int root1 = n1;
    int root2 = n2;
    if (root1 != root2)
        parent[root1] = root2;
}

void graph_init(GraphType *g)
{
    g->n = 1;
    for (int i = 0; i < MAX*2; i++)
    {
        g->mat[i].u = 0;
        g->mat[i].v = 0;
        g->mat[i].weight = INT_MAX;
    }
}

void insert_edge(GraphType *g, int u, int v, int weight)
{
    g->mat[g->n].u = u;
    g->mat[g->n].v = v;
    g->mat[g->n].weight = weight;
    g->n++;
}


int compare(const void *n1, const void *n2)
{
    element *x = (element *)n1;
    element *y = (element *)n2;
    return (x->weight - y->weight);
}

void get_input(GraphType *g)
{
    int node, edge;
    scanf("%d %d", &node, &edge);

    int u,v,w;
    for (int i = 0; i < edge; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        if (u != v)
            insert_edge(g, u, v, w);
    }
}

void kruskal(GraphType *g)
{
    int edge_accepted = 0;  // 현재까지 선택된 간선의 수
    int uset, vset;
    long long int cnt = 0;
    element e;

    set_init(g->n);
    qsort(g->mat, g->n, sizeof(element), compare);

    int i = 0;
    while (edge_accepted < (g->n - 1))
    {
        e = g->mat[i];
        if (e.weight == INT_MAX)
            break;
        uset = set_find(e.u);
        vset = set_find(e.v);

        if (uset != vset)
        {
            cnt += e.weight;
            edge_accepted++;
            set_union(uset, vset);
        }
        i++;
    }
    printf("%lld", cnt);
}

int main()
{
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    graph_init(g);

    get_input(g);
    kruskal(g);

    free(g);
    return 0;
}
