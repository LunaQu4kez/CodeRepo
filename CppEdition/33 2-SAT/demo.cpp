/*
题目描述
有 n 个布尔变量 x1 ∼ xn，另有 m 个需要满足的条件，每个条件的形式都是 
「xi 为 true / false 或 xj 为 true / false」。
比如 「x1 为真或 x3 为假」。
2-SAT 问题的目标是给每个变量赋值使得所有条件得到满足。

输入格式
第一行两个整数 n 和 m，意义如题面所述。
接下来 m 行每行 4 个整数 i, a, j, b，表示 「xi 为 a 或 xj 为 b」(a,b∈{0,1})

输出格式
如无解，输出 IMPOSSIBLE；否则输出 POSSIBLE。
下一行 n 个整数 x1 ∼ xn（xi ∈{0,1}），表示构造出的解。
*/

#include<bits/stdc++.h>
using namespace std;

long long read() {
    char ch = getchar();
    long long a = 0, x = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-') x = -x;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        a = (a << 1) + (a << 3) + (ch - '0');
        ch = getchar();
    }
    return a * x;
}

const int N = 4e6 + 10;

int n, m, a, b, x, y, tim, top, edge_sum, scc_sum;
int dfn[N], low[N], st[N], vis[N], scc[N], head[N];

struct node {
    int to, next;
} A[N];

void add(int from, int to) {
    edge_sum++;
    A[edge_sum].next = head[from];
    A[edge_sum].to = to;
    head[from] = edge_sum;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    st[++top] = u;
    vis[u] = 1;
    for (int i = head[u]; i; i = A[i].next) {
        int v = A[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        scc_sum++;
        while (st[top] != u) {
            scc[st[top]] = scc_sum;
            vis[st[top]] = 0;
            top--;
        }
        scc[st[top]] = scc_sum;
        vis[st[top]] = 0;
        top--;
    }
}

int main()
{
    n = read();
    m = read();
    for (int i = 1; i <= m; i++) {
        a = read(); x = read(); 
        b = read(); y = read();
        if (x == 0 && y == 0) {     // "如果第 a 个数为 0 或第 b 个数为 0"至少满足其一 
            add(a + n, b);     // a = 1 则 b = 0 
            add(b + n, a);     // b = 1 则 a = 0 
        }
        if (x == 0 && y == 1) {     // "如果第 a 个数为 0 或第 b 个数为 1"至少满足其一 
            add(a + n, b + n); // a = 1 则 b = 1 
            add(b, a);         // b = 0 则 a = 0 
        }
        if (x == 1 && y == 0) {     // "如果第 a 个数为 1 或第 b 个数为 0"至少满足其一
            add(a, b);         // a = 0 则 b = 0 
            add(b + n, a + n); // b = 1 则 a = 1 
        }
        if (x == 1 && y == 1) {     // "如果第 a 个数为 1 或第 b 个数为 1"至少满足其一
            add(a, b + n);     // a = 0 则 b = 1 
            add(b, a + n);     // b = 0 则 a = 1 
        }
    }
    for (int i = 1; i <= 2 * n; i++) if(!dfn[i]) tarjan(i);  // 对每个变量的每种取值进行 tarjan
    for (int i = 1; i <= n; i++) {   // 判断无解的情况
        if (scc[i] == scc[i + n]) {  // 同一变量的两种取值在同一强联通分量里,说明无解 
            printf("IMPOSSIBLE\n");
            return 0;
        }
    }
    printf("POSSIBLE\n");    // 否则就是有解 
    for (int i = 1; i <= n; i++) {
        if (scc[i] > scc[i + n]) printf("1 ");  // 强联通分量编号越小 -> 拓扑序越大 -> 越优 
        else printf("0 ");
    }

    return 0;
}