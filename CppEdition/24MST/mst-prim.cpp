/*
题目描述
给出一个无向图，求出最小生成树。

输入格式
第一行包含两个整数 N,M，表示该图共有 N 个结点和 M 条无向边。
接下来 M 行每行包含三个整数 X_i, Y_i, Z_i，表示有一条长度为 Z_i 的无向边连接结点 X_i, Y_i。

输出格式
输出一个整数表示最小生成树的各边的长度之和。
*/

#include<bits/stdc++.h>
using namespace std;

inline int read() {
    int x = 0, f = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return x * f;
}

#define inf 2147483647
#define maxn 5010
#define maxm 200010

struct edge
{
	int v, w, next;
} e[maxm << 1];  // 注意是无向图，开两倍数组

int head[maxn], dis[maxn], cnt, n, m, tot, now = 1, ans;  // dis 已经加入最小生成树的的点到没有加入的点的最短距离
bool vis[maxn];

// 链式前向星加边
inline void add(int u, int v, int w) {
	e[++cnt].v = v;
	e[cnt].w = w;
	e[cnt].next = head[u];
	head[u] = cnt;
}

// 读入数据
inline void init() {
    n = read(), m = read();
    for (int i = 1, u, v, w; i <= m; i++) {
        u = read(), v = read(), w = read();
        add(u, v, w), add(v, u, w);
    }
}

inline int prim() {
	for (int i = 2; i <= n; i++) dis[i] = inf;
	for (int i = head[1]; i; i = e[i].next) dis[e[i].v] = min(dis[e[i].v], e[i].w);
    while (++tot < n) {
        int minn = inf;
        vis[now] = 1;
        for (int i = 1; i <= n; i++) {
            if (!vis[i] && minn > dis[i]) {
                minn = dis[i];
				now = i;
            }
        }
        ans += minn;
        for (int i = head[now]; i; i = e[i].next) {
        	int v = e[i].v;
        	if (dis[v] > e[i].w && !vis[v]) dis[v] = e[i].w;
		}
    }
    return ans;
}

int main()
{
    init();
    printf("%d", prim());

    return 0;
}