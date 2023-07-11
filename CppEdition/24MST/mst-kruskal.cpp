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

struct Edge {
	int u, v, w;
} edge[200010];

int fa[5010], n, m, ans, eu, ev, cnt;

inline bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}

inline int find(int x) {
    while (x != fa[x]) x = fa[x] = fa[fa[x]];
    return x;
}

inline void kruskal() {
    sort(edge, edge + m, cmp);
    for (int i = 0; i < m; i++) {
        eu = find(edge[i].u), ev = find(edge[i].v);
        if (eu == ev) continue;  // 若出现两个点已经联通了，则说明这一条边不需要了
        ans += edge[i].w;  // 将此边权计入答案
        fa[ev] = eu;  // 将eu、ev合并
        if (++cnt == n - 1) break;
    }
}

int main()
{
    n=read(), m=read();
    for (int i = 1; i <= n; i++) fa[i]=i;
    for (int i = 0; i < m; i++) edge[i].u = read(), edge[i].v = read(), edge[i].w = read();
    kruskal();
    printf("%d", ans);

    return 0;
}