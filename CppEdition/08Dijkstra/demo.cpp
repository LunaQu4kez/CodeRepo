#include<bits/stdc++.h>
using namespace std;

int graph[100][100];

/**
 * 朴素 Dijkstra 算法  时间复杂度O(n^2)
 *
 * @param src   起始点
 * @param graph 邻接矩阵表示的图
 * @return src到所有点的最短路径权值和
 */
int* dijkstra(int src, int n) {
    int* dist = new int[n];
    for (int i = 0; i < n; i++) dist[i] = INT32_MAX / 2;
    bool vis[n];
    dist[src] = 0;
    for (int round = 0; round < n - 1; ++round) {
        int u = -1;
        for (int i = 0; i < n; ++i) {
            if (!vis[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        vis[u] = true;
        for (int v = 0; v < n; ++v) {
            if (!vis[v] && graph[u][v] != -1) {
                dist[v] = min(dist[v], dist[u] + graph[u][v]);
            }
        }
    }
    return dist;
}

int main()
{
    graph[0][0] = 0;
    graph[0][1] = 1;
    graph[0][2] = 100000;
    graph[1][0] = 1;
    graph[1][1] = 0;
    graph[1][2] = 2;
    graph[2][0] = 100000;
    graph[2][1] = 2;
    graph[2][2] = 0;
    int* p = dijkstra(0, 3);
    for (int i = 0; i < 3; i++) cout << p[i] << " ";

    return 0;
}