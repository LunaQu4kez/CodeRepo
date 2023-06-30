#include <bits/stdc++.h>
using namespace std;

int fa[1000010], n, m, x, y; // n 结点数，m 边数，x y 临时变量

int find(int x)
{
    if (x != fa[x]) fa[x] = find(fa[x]);
    return fa[x];
}

void unity(int x, int y)
{
    int r1 = find(x);
    int r2 = find(y);
    fa[r1] = r2;
}

bool is_connect(int x, int y) // 查询 x 和 y 是否连通
{
    return find(x) == find(y);
}

int count() // 返回连通分量的个数
{
    int cnt = 0;
    for (int i = 1; i <= n; i++) if (fa[i] == i) cnt++;
    return cnt;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
	    scanf("%d %d", &x, &y);
	    unity(x, y);
	}

    return 0;
}