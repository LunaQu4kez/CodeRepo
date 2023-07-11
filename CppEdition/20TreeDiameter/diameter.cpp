#include<bits/stdc++.h>
using namespace std;

const int N = 10010;

struct edge {
    int v, w;  //  v 相连的点，w 边权
};

int n, c, d[N];
vector<edge> E[N];

void dfs(int u, int fa) {
    for (edge e : E[u]) {
        if (e.v == fa) continue;
        d[e.v] = d[u] + e.w;
        if (d[e.v] > d[c]) c = e.v;
        dfs(e.v, u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        E[u].push_back((edge){v, w}), E[v].push_back((edge){u, w});
    }
    dfs(1, 0);
    d[c] = 0, dfs(c, 0);
    printf("%d\n", d[c]);
    
    return 0;
}