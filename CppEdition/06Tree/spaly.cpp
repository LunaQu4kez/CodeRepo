/*
P3369
题目描述
您需要写一种数据结构（可参考题目标题），来维护一些数，其中需要提供以下操作：
1、插入 x 数
2、删除 x 数(若有多个相同的数，应只删除一个)
3、查询 x 数的排名(排名定义为比当前数小的数的个数 + 1)
4、查询排名为 x 的数
5、求 x 的前驱(前驱定义为小于 x，且最大的数)
6、求 x 的后继(后继定义为大于 x，且最小的数)

输入格式
第一行为 n，表示操作的个数,下面 n 行每行有两个数 opt 和 x，opt 表示操作的序号(1 ≤ opt ≤ 6)

输出格式
对于操作 3, 4, 5, 6 每行输出一个数，表示对应答案
*/

#include<bits/stdc++.h>
using namespace std;

int n, k=0, root;
const int maxn = 100010;
const int inf = 0x7f7f7f7f;
struct node {
	int ch[2], fa, val, cnt, size;
} tree[maxn];

void updata(int x)
{
	tree[x].size = tree[tree[x].ch[0]].size + tree[tree[x].ch[1]].size + tree[x].cnt;
}

void rotate(int x)
{
	int y = tree[x].fa;
	int z = tree[y].fa;
	int ki = tree[y].ch[1] == x;
	tree[z].ch[tree[z].ch[1] == y] = x;
	tree[x].fa = z;
	tree[y].ch[ki] = tree[x].ch[ki ^ 1];
	tree[tree[x].ch[ki ^ 1]].fa = y;
	tree[x].ch[ki^1] = y;
	tree[y].fa = x;
	updata(y);
    updata(x);
}

void splay(int x,int goal)
{
	while (tree[x].fa != goal)
	{
		int y = tree[x].fa;
		int z = tree[y].fa;
		if (z != goal)
		{
			(tree[z].ch[0] == y) ^ (tree[y].ch[0] == x) ? rotate(x) : rotate(y);
		}
		rotate(x);
	}
	if (goal == 0) root = x;
}

void insert(int x)
{
	int now = root, fa = 0;
	while (now && tree[now].val != x)
	{
		fa = now;
		now = tree[now].ch[x > tree[now].val]; 
	}
	if (now) tree[now].cnt++;
	else
	{
		now = ++k;
		if (fa) tree[fa].ch[x > tree[fa].val] = now; 
		tree[k].fa = fa;
		tree[k].val = x;
		tree[k].size = tree[k].cnt = 1;
	}
	splay(now, 0);
}

void search(int x)
{
	int now = root;
	if (!now) return;
	while (tree[now].ch[x > tree[now].val] && x != tree[now].val) now=tree[now].ch[x>tree[now].val];
	splay(now, 0); 
}

int pre(int x)
{
	search(x);
	int now = tree[root].ch[0];
	while (tree[now].ch[1]) now = tree[now].ch[1];
	return now;
}

int net(int x)
{
	search(x);
	int now = tree[root].ch[1];
	while (tree[now].ch[0]) now = tree[now].ch[0];
	return now;
}

int find(int x)
{
	int now = root;
	while (1)
	{
		if (x <= tree[tree[now].ch[0]].size) now = tree[now].ch[0];
		else
		{
			x -= (tree[tree[now].ch[0]].size + tree[now].cnt);
			if (x <= 0) return now;
			else now = tree[now].ch[1];
		}
	}
}

void del(int x)
{
	int p_fa = pre(x);
	int n_fa = net(x);
	splay(p_fa, 0); 
	splay(n_fa, p_fa); 
	int tmp = tree[n_fa].ch[0];
	if (tree[tmp].cnt > 1) 
	{
		tree[tmp].cnt--;
		splay(tmp,0);
	}
	else tree[n_fa].ch[0] = 0; 
}

int main(){
	scanf("%d",&n);
	int opt, x;
	insert(inf);
    insert(-inf);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d%d", &opt, &x);
		if (opt==1) insert(x);
		else if (opt==2) del(x);
		else if (opt==3)
		{
			search(x);
			printf("%d\n", tree[tree[root].ch[0]].size);
		}
		else if (opt == 4)
		{
			printf("%d\n", tree[find(x+1)].val);
		}
		else if (opt == 5)
		{
			insert(x);
			printf("%d\n",tree[pre(x)].val);
			del(x);
		}
		else if (opt == 6)
		{
			insert(x);
			printf("%d\n",tree[net(x)].val);
			del(x);
		}
	}

	return 0;
}