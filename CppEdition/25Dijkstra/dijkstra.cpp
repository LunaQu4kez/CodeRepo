/*
题目描述
给定一个 n 个点，m 条有向边的带非负权图，请你计算从 s 出发，到每个点的距离。
数据保证你能从 s 出发到任意点。

输入格式
第一行为三个正整数 n,m,s。 第二行起 m 行，每行三个非负整数 u_i, v_i, w_i，
表示从 u_i 到 v_i 有一条权值为 w_i 的有向边。

输出格式
输出一行 n 个空格分隔的非负整数，表示 s 到每个点的距离。
*/

#include<bits/stdc++.h>
using namespace std;

const int MaxN = 100010, MaxM = 500010;

struct edge {
    int to, dis, next;
};

edge e[MaxM];
int head[MaxN], dis[MaxN], cnt;
bool vis[MaxN];
int n, m, s;

inline void add_edge(int u, int v, int d) {
    cnt++;
    e[cnt].dis = d;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

struct node {
    int dis;
    int pos;
    bool operator <( const node &x )const {
        return x.dis < dis;
    }
};

priority_queue<node> q;

inline void dijkstra() {
    dis[s] = 0;
    q.push((node){0, s});
    while (!q.empty()) {
        node tmp = q.top();
        q.pop();
        int x = tmp.pos, d = tmp.dis;
        if (vis[x]) continue;
        vis[x] = 1;
        for (int i = head[x]; i; i = e[i].next) {
            int y = e[i].to;
            if(dis[y] > dis[x] + e[i].dis) {
                dis[y] = dis[x] + e[i].dis;
                if (!vis[y]) q.push((node){dis[y], y});
            }
        }
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= n; i++) dis[i] = 0x7fffffff;
    for (register int i = 0; i < m; i++) {
        register int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        add_edge(u, v, d);
    }
    dijkstra();
    for (int i = 1; i <= n; i++) printf("%d ", dis[i]);

    return 0;
}