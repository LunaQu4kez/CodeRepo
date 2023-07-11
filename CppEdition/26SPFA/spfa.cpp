/*
题目描述
给定一个 n 个点，m 条有向边的带非负权图，请你计算从 s 出发，到每个点的距离。

输入格式
第一行为三个正整数 n,m,s。 第二行起 m 行，每行三个非负整数 u_i, v_i, w_i，
表示从 u_i 到 v_i 有一条权值为 w_i 的有向边。

输出格式
输出一行 n 个空格分隔的非负整数，表示 s 到每个点的距离。
*/

#include<bits/stdc++.h>
using namespace std;

inline int read() {
    int x = 0, f = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return x * f;
}

#define maxn 10010
#define maxm 500010
#define inf INT32_MAX
int n, m, s, tot, dis[maxn], head[maxn];
bool vis[maxn];
struct Edge {
    int next, to, w;
} h[maxm];

void add(int u, int v, int w) {
    h[++tot].next = head[u];
    h[tot].to = v;
    h[tot].w = w;
    head[u] = tot;
}

queue<int> q;

inline void spfa() {
    for (int i = 1; i <= n; i++) dis[i] = inf;
    int u, v;
    q.push(s);
    dis[s] = 0;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = h[i].next) {
            v = h[i].to;
            if (dis[v] > dis[u] + h[i].w) {
                dis[v] = dis[u] + h[i].w;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    n = read(), m = read(), s = read();
    for (int i = 1, u, v, w; i <= m; i++) {
        u = read(), v = read(), w = read();
        add(u, v, w);
    }
    spfa();
    for (int i = 1; i <= n; i++) printf("%d ", dis[i]);
    
    return 0;
}