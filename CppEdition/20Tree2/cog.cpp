/*
题目描述
有一个村庄居住着 n 个村民，有 n−1 条路径使得这 n 个村民的家联通，每条路径的长度都为 1。
现在村长希望在某个村民家中召开一场会议，村长希望所有村民到会议地点的距离之和最小，
那么村长应该要把会议地点设置在哪个村民的家中，并且这个距离总和最小是多少？若有多个节点都满足条件，
则选择节点编号最小的那个点。

输入格式
第一行，一个数 n，表示有 n 个村民。
接下来 n−1 行，每行两个数字 a 和 b，表示村民 a 的家和村民 b 的家之间存在一条路径。

输出格式
一行输出两个数字 x 和 y。
x 表示村长将会在哪个村民家中举办会议。
y 表示距离之和的最小值。
*/

#include<bits/stdc++.h>
using namespace std;

const int N = 50010;
int d[N], f[N], n, cnt, siz[N], vis[N], head[N];  // siz[i] 表示 i 与 i 的子树的结点个数之和，d[i] 表示在点 i 开会的距离和

struct edge {
    int to, nxt;
} e[N << 1];

void add(int x, int y) {
    e[++cnt].to = y;
    e[cnt].nxt = head[x];
    head[x] = cnt;
}

void dfs1(int now) {
    siz[now] = 1;
    for (int i = head[now]; i; i = e[i].nxt) {
        int to = e[i].to;
        if(d[to]) continue;
        d[to] = d[now] + 1;
        dfs1(to);
        siz[now] += siz[to];
    }
}

void dfs(int now, int fa) {
    f[now] = f[fa] + n - 2 * siz[now];
    for (int i = head[now]; i; i = e[i].nxt) {
        int to = e[i].to;
        if (to == fa) continue;
        dfs(to, now);
    }
}

int main() {
    scanf("%d", &n);
    for (int x, y, i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    d[1] = 1;
    dfs1(1);
    int maxn = 0, idx = 1;
    for (int i = 1; i <= n; i++) maxn += d[i];
    maxn -= n;
    f[1] = maxn;
    for (int i = head[1]; i; i = e[i].nxt) {
        int to = e[i].to;
        dfs(to, 1);
    }
    for (int i = 2; i <= n; i++) {
        if (f[i] < maxn) maxn = f[i], idx = i;
    }
    printf("%d %d", idx, maxn);

    return 0;
}