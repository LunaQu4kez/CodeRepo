/*
题目描述
给出一个 n 个点，m 条边的无向图，求图的割点。

输入格式
第一行输入两个正整数 n,m。
下面 m 行每行输入两个正整数 x,y 表示 x 到 y 有一条边。

输出格式
第一行输出割点个数。
第二行按照节点编号从小到大输出节点，用空格隔开。
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int n, m, R;
int dn, dfn[N], low[N], cnt, buc[N]; // dfn 是时间戳 d, low 是 g
vector<int> e[N];

void dfs(int id) {
    dfn[id] = low[id] = ++dn;
    int son = 0;
    for (int it : e[id]) {
        if (!dfn[it]) {
            son++, dfs(it), low[id] = min(low[id], low[it]);
            if (low[it] >= dfn[id] && id != R) cnt += !buc[id], buc[id] = 1;
        }
        else low[id] = min(low[id], dfn[it]);
    }
    if (son >= 2 && id == R) cnt += !buc[id], buc[id] = 1;
}

int main() {
  cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v), e[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) if(!dfn[i]) R = i, dfs(i);
    cout << cnt << endl;
    for (int i = 1; i <= n; i++) if(buc[i]) cout << i << " ";

    return 0;
}