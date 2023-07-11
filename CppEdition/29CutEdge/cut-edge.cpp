/*
题目描述
求所有割边

输入格式
第一行 n，m，分别表示有 n 个点，总共 m 条边。
以下 m 行,每行两个整数 a,b，表示 a 和 b 直接连接。

输出格式
输出有若干行。
每行包含两个数字 a，b，其中 a < b，表示 <a,b> 是 割边。
请注意：输出时，所有的数对 <a,b> 必须按照 a 从小到大排序输出；如果a 相同，则根据 b 从小到大排序。
*/

#include<bits/stdc++.h>
using namespace std;

const int maxn = 10010;

int n, m, x, y, index_, dfn[maxn], low[maxn], ans, a;  // index_代表当前的时间戳
// 遍历到这个节点的次序为这个节点的时间戳，用 dfn 表示
// 定义 low[i] 为不经过 i 和父节点的连边在 DFS 树上可以（直接或间接）访问到的最小的时间戳
vector<int> G[maxn];

struct Edge {
    int from, to;
} edge[maxn];

bool cmp(const Edge a, const Edge b) {
    if (a.from != b.from) return a.from < b.from;
    return a.to < b.to;
}

inline void add_edge(int x,int y) {
    edge[ans].from = min(x, y);
    edge[ans].to = max(x, y);
    ans++;
}

void dfs(int cur,int fa) {
    int child;
    dfn[cur] = ++index_;
    low[cur] = dfn[cur];
    bool vis = false; 
    for (int i = 0; i < G[cur].size(); i++) {
        child = G[cur][i];
        if (dfn[child]) {
			if (child == fa && !vis) vis = true;
			else low[cur] = min(low[cur], dfn[child]);
		}
        if(!dfn[child]) {
            dfs(child, cur);
            if (dfn[cur] < low[child]) add_edge(cur, child);
            low[cur] = min(low[cur], low[child]);
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) scanf("%d%d", &x, &y), G[x].push_back(y), G[y].push_back(x);
    for (int i = 1; i <= n; i++) if(!dfn[i]) dfs(i, i);
    sort(edge, edge + ans, cmp);
    for (int i = 0; i < ans; i++) printf("%d %d\n", edge[i].from, edge[i].to);

    return 0;
}