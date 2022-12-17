#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF 999999
#define MAX_VERTEX 20001
#define MAX_EDGE 300001

int dist[MAX_VERTEX];
vector<pair<int, int> > graph[MAX_EDGE]; //weight, n2

void printDist(int v)
{
    for (int i = 1; i <= v; i++)
    {
        if (dist[i] == INF)
            printf("INF\n");
        else
            printf("%d\n", dist[i]);
    }
}

void shortest_path(int start)
{
    dist[start] = 0;
    priority_queue<pair<int, int> > pq; // weight, 도착 노드. 정렬기준 weight
    pq.push(make_pair(0, start)); // 시작노드의 weigh와 도착노드 삽입

    while (!pq.empty())
    {
        //GetMinDist
        //가중치가 가장 작은 간선 꺼내기
        int d = -pq.top().first; //가중치
        int i = pq.top().second; //현재 노드
        pq.pop();

        if (dist[i] < d)
            continue;
        //UpdateDist
        for (int k = 0; k < graph[i].size(); k++)
        {
            int n_d = d + graph[i][k].first; //가중치
            int n_i = graph[i][k].second; //다음 노드

            if (dist[n_i] > n_d)
            {
                dist[n_i] = n_d; //dist 업데이트
                pq.push(make_pair(-n_d, n_i));
            }
        }
    }
}

void init(int v)
{
    for (int i = 1; i <= v; i++)
        dist[i] = INF;
}

void get_input(int e)
{
    int n1, n2, w;
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d %d", &n1, &n2, &w);
        graph[n1].push_back(make_pair(w, n2));
    }
}

int main(void)
{
    int v, e, start;
    scanf("%d %d %d", &v, &e, &start);

    init(v);
    get_input(e);
    shortest_path(start);
    printDist(v);

    return (0);
}