/*
题目描述
给定一个 n 个点的有向图，请求出图中是否存在从顶点 1 出发能到达的负环。
负环的定义是：一条边权之和为负数的回路。

输入格式
本题单测试点有多组测试数据。
输入的第一行是一个整数 T，表示测试数据的组数。对于每组数据的格式如下：
第一行有两个整数，分别表示图的点数 n 和接下来给出边信息的条数 m。
接下来 m 行，每行三个整数 u,v,w。
若 w ≥ 0，则表示存在一条从 u 至 v 边权为 w 的边，还存在一条从 v 至 u 边权为 w 的边。
若 w < 0，则只表示存在一条从 u 至 v 边权为 w 的边。

输出格式
对于每组数据，输出一行一个字符串，若所求负环存在，则输出 YES，否则输出 NO。
*/

#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN=2010;
const int MAXM=3010;
int n, m;

int en = -1, eh[MAXN];
struct edge {
	int u, v, w, next;
	edge(int U = 0, int V = 0, int W = 0, int N = 0): u(U), v(V), w(W), next(N){}
} e[MAXM << 1];

inline void add_edge(int u, int v, int w) {
	e[++en] = edge(u, v, w, eh[u]);
    eh[u] = en;
}

void input() {
	scanf("%d %d", &n, &m);
	en = -1;
	memset(eh,-1,sizeof(eh));
	int u, v, w;
	for (int i = 1; i <= m; i++) { 
		scanf("%d %d %d", &u, &v, &w);
		add_edge(u, v, w);
		if (w >= 0) add_edge(v, u, w);
	}
}

int dis[MAXN], cnt[MAXN];
bool vis[MAXN];
queue<int> q;

void spfa() {
	fill(dis + 1, dis + n + 1, inf);
	memset(cnt, 0, sizeof(cnt));
	memset(vis, 0, sizeof(vis));
	
	while (!q.empty()) q.pop();
	dis[1] = 0;
    vis[1] = 1;
    q.push(1);
	
	int u, v, w;
	while (!q.empty()) {
		u = q.front();
        vis[u] = 0;
        q.pop();
		for (int i = eh[u]; i != -1; i = e[i].next) {
			v = e[i].v;
            w = e[i].w;
			if (dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				if (!vis[v]) {
					if (++cnt[v] >= n) {
						printf("YES\n");
                        return;
					}
					vis[v] = 1;
                    q.push(v);
				}
			}
		}
	}
	printf("NO\n");
}

int main()
{
	int t;
	scanf("%d",&t);
	for (int i = 1; i <= t; i++) {
		input();
		spfa();
	}

	return 0;
}