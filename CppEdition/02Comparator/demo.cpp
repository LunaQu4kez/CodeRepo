#include<bits/stdc++.h>
using namespace std;

int n;

struct node
{
	int a, b;
	friend bool operator < (const node &n1,const node &n2)
	{
		return n1.b < n2.b;
	}
} e[10010];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &e[i].a, &e[i].b);
	sort(e + 1, e + 1 + n);
	for (int i = 1; i <= n; i++) {
		printf("%d %d\n", e[i].a, e[i].b);
	}

	return 0;
}