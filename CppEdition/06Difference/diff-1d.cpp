#include<bits/stdc++.h>
using namespace std;

int a[5000010], d[5000010], n, m;

void diff()
{
    for (int i = 1; i <= n; i++) d[i] = a[i] - a[i - 1];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    diff(); // 差分
	for (int i = 0; i < m; i++) {
		int x, y, z; // 给第 x 到第 y 个数加上 z
        scanf("%d%d%d", &x, &y, &z);
		d[x] += z;
		d[y + 1] -= z;
	}

	for (int i = 1; i <= n; i++)
	{
		a[i] = a[i - 1] + d[i];
		printf("%d ", a[i]);
	}
	
    return 0;
}