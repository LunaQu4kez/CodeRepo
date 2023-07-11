/*
题目描述
给出一张由 n 个点 m 条边组成的无向图。
求出所有点对 (i,j) 之间的最短路径。

输入格式
第一行为两个整数 n,m，分别代表点的个数和边的条数。
接下来 m 行，每行三个整数 u,v,w，代表 u,v 之间存在一条边权为 w 的边。

输出格式
输出 n 行每行 n 个整数。
第 i 行的第 j 个整数代表从 i 到 j 的最短路径。
*/

#include<bits/stdc++.h>
using namespace std;

const long long inf = 1e9;
long long dis[3010][3010];
int n, m, u, v, w;

int main()
{
	scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dis[i][j] = i == j ? 0 : inf;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		dis[u][v] = w;
		dis[v][u] = w;
	}
	for (int k = 1; k <= n; k++)
		for (int j = 1; j <= n; j++) 
			if (j != k)
			    for (int i = 1; i <= n; i++) 
				    if (i != j && i != k)
				        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) printf("%d ", dis[i][j]);
		printf("\n");
	}

	return 0;
}