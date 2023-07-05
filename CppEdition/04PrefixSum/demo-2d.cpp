#include<bits/stdc++.h>
using namespace std;

int n, m, a[200][200], sum[200][200], pre[200][200]; 
// sum[i][j] 是 a[1][1] 到 a[i][j] 矩形的和 
// pre[i][j] 指的是第 i 行前 j 个数的前缀和
 
void prefixSum2d()
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pre[i][j] = pre[i][j - 1] + a[i][j];
            sum[i][j] = pre[i][j] + sum[i - 1][j];
        }
    }
}

int query(int x1, int y1, int x2, int y2)
{
    return sum[x2][y2] + sum[x1 - 1][y1 - 1] - sum[x2][y1 - 1] - sum[x1 - 1][y2];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    prefixSum2d();

    scanf("%d", &m);
    int x1, y1, x2, y2;
    while (m--) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        printf("%d\n", query(x1, y1, x2, y2));
    }

	return 0;
}

/*
5
1 2 1 1 2
2 0 1 1 1 
1 2 2 2 1
2 2 1 0 1
1 2 0 1 1
*/