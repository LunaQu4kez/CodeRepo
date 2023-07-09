/*
题目描述
您需要写一种数据结构（可参考题目标题），来维护一个有序数列，其中需要提供以下操作：
-查询 k 在区间内的排名
-查询区间内排名为 k 的值
-修改某一位值上的数值
-查询 k 在区间内的前驱（前驱定义为严格小于 x，且最大的数，若不存在输出 -2147483647）
-查询 k 在区间内的后继（后继定义为严格大于 x，且最小的数，若不存在输出 2147483647）

输入格式
第一行两个数 n,m，表示长度为 n 的有序序列和 m 个操作。
第二行有 n 个数，表示有序序列。
下面有 m 行，opt 表示操作标号。
若 opt=1，则为操作 1，之后有三个数 l r k，表示查询 k 在区间 [l,r] 的排名。
若 opt=2，则为操作 2，之后有三个数 l r k，表示查询区间 [l,r] 内排名为 k 的数。
若 opt=3，则为操作 3，之后有两个数 pos k，表示将 pos 位置的数修改为 k。
若 opt=4，则为操作 4，之后有三个数 l r k，表示查询区间 [l,r] 内 k 的前驱。
若 opt=5，则为操作 5，之后有三个数 l r k，表示查询区间 [l,r] 内 k 的后继。

输出格式
对于操作 1,2,4,5，各输出一行，表示查询结果。
*/

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 100;
int n, m;
int a[MAXN];

namespace Treap
{
	struct balanced
	{
		int w;
		int sz;
		int num;
		int fix;
		int ch[2];
	};
	int tot;
	balanced tree[MAXN * 20];
	int newnode(int w)
	{
		++tot;
		tree[tot].w = w;
		tree[tot].fix = rand();
		tree[tot].num = 1;
		tree[tot].ch[0] = tree[tot].ch[1] = 0;
		tree[tot].sz = 1;
		return tot;
	}
	void pushup(int p)
	{
		tree[p].sz = tree[tree[p].ch[0]].sz + tree[tree[p].ch[1]].sz + tree[p].num;
	}
	void rotate(int &p, int d)
	{
		int y = tree[p].ch[d];
		tree[p].ch[d] = tree[y].ch[d ^ 1];
		tree[y].ch[d ^ 1] = p;
		pushup(p);
		pushup(y);
		p = y;
	}
	void insert(int &p, int w)
	{
		if (!p)
			p = newnode(w);
		else if (tree[p].w == w)
			++tree[p].num;
		else 
		{
			if (tree[p].w > w)
			{
				insert(tree[p].ch[0], w);
				if (tree[tree[p].ch[0]].fix > tree[p].fix)
					rotate(p, 0);
			}
			else
			{
				insert(tree[p].ch[1], w);
				if (tree[tree[p].ch[1]].fix > tree[p].fix)
					rotate(p, 1);
			}
		}
		pushup(p);
	}
	void remove(int &p, int w)
	{
		if (tree[p].w > w)
			remove(tree[p].ch[0], w);
		else if (tree[p].w < w)
			remove(tree[p].ch[1], w);
		else
		{
			if (tree[p].num > 1)
				--tree[p].num;
			else
			{
				if (!tree[p].ch[0] && !tree[p].ch[1])
					p = 0;
				else if (!tree[p].ch[0])
				{
					rotate(p, 1);
					remove(tree[p].ch[0], w);
				}
				else if (!tree[p].ch[1])
				{
					rotate(p, 0);
					remove(tree[p].ch[1], w);
				}
				else
				{
					if (tree[tree[p].ch[0]].fix > tree[tree[p].ch[1]].fix)
					{
						rotate(p, 0);
						remove(tree[p].ch[1], w);
					}
					else
					{
						rotate(p, 1);
						remove(tree[p].ch[0], w);
					}
				}
			}
		}
		if (p)
			pushup(p);
	}
	int queryrank(int p, int k) // return the highest rank of value 'k'
	{
		if (!p)
			return 0;
		if (tree[p].w > k)
			return queryrank(tree[p].ch[0], k);
		else if (tree[p].w == k)
			return tree[tree[p].ch[0]].sz;
		else
			return tree[tree[p].ch[0]].sz + tree[p].num + queryrank(tree[p].ch[1], k);
	}
	int querynum(int p, int k) // return the value of kth rank node
	{
		if (tree[tree[p].ch[0]].sz + 1 == k)
			return tree[p].w;
		else if (tree[tree[p].ch[0]].sz + 1 < k)
			return querynum(tree[p].ch[1], k - 1 - tree[tree[p].ch[0]].sz);
		else	
			return querynum(tree[p].ch[0], k);
	}
	int querypre(int p, int k) // return the prefix of value k
	{
		if (!p) 
			return -2147483647;
		if (tree[p].w >= k)
			return querypre(tree[p].ch[0], k);
		else
			return max(tree[p].w, querypre(tree[p].ch[1], k));
	}
	int querysuf(int p, int k) // return the suffix of value k
	{
		if (!p)
			return 2147483647;
		if (tree[p].w <= k)
			return querysuf(tree[p].ch[1], k);
		else
			return min(tree[p].w, querysuf(tree[p].ch[0], k));
	}
	void listall(int p)
	{
		if (tree[p].ch[0])
			listall(tree[p].ch[0]);
		cerr << tree[p].w << ",sz=" << tree[p].num << "   ";
		if (tree[p].ch[1])
			listall(tree[p].ch[1]);
	}
}
using Treap::listall;

namespace SEG
{
	struct segment
	{
		int l;
		int r;
		int root;
	};
	segment tree[MAXN * 8];
	void build(int p, int l, int r)
	{
		tree[p].l = l;
		tree[p].r = r;
		for (int i = l; i < r + 1; ++i)
			Treap::insert(tree[p].root, a[i]);
		if (l != r)
		{
			int mid = (l + r) / 2;
			build(p * 2, l, mid);
			build(p * 2 + 1, mid + 1, r);
		}
	}
	void modify(int p, int x, int y)
	{
		Treap::remove(tree[p].root, a[x]);
		Treap::insert(tree[p].root, y);
		if (tree[p].l == tree[p].r)
			return;
		int mid = (tree[p].l + tree[p].r) / 2;
		if (x > mid)
			modify(p * 2 + 1, x, y);
		else
			modify(p * 2, x, y);
	}
	int queryrank(int p, int l, int r, int k) // query the highest rank of value 'k'
	{
		if (tree[p].l > r || tree[p].r < l)
			return 0;
		if (tree[p].l >= l && tree[p].r <= r)
			return Treap::queryrank(tree[p].root, k);
		else
			return queryrank(p * 2, l, r, k) + queryrank(p * 2 + 1, l, r, k);
	}
	int querynum(int u, int v, int k) // query the value of kth num
	{
		int l = 0, r = 1e8;
		while (l < r)
		{
			int mid = (l + r + 1) / 2;
			if (queryrank(1, u, v, mid) < k)
				l = mid;
			else
				r = mid - 1;
		}
		return r;
	}
	int querypre(int p, int l, int r, int k)
	{
		if (tree[p].l > r || tree[p].r < l)
			return -2147483647;
		if (tree[p].l >= l && tree[p].r <= r)
			return Treap::querypre(tree[p].root, k);
		else
			return max(querypre(p * 2, l, r, k), querypre(p * 2 + 1, l, r, k));
	}
	int querysuf(int p, int l, int r, int k)
	{
		if (tree[p].l > r || tree[p].r < l)
			return 2147483647;
		if (tree[p].l >= l && tree[p].r <= r)
			return Treap::querysuf(tree[p].root, k);
		else
			return min(querysuf(p * 2, l, r, k), querysuf(p * 2 + 1, l, r, k));
	}
}

int read()
{
	char ch = getchar();
	int x = 0, flag = 1;
	while (ch != '-' && (ch < '0' || ch > '9'))
		ch = getchar();
	if (ch == '-')
	{
		ch = getchar();
		flag = -1;
	}
	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * flag;
}

int main()
{
	n = read();
	m = read();
	for (int i = 1; i < n + 1; ++i)
		a[i] = read();
	SEG::build(1, 1, n);
	for (int i = 0; i < m; ++i)
	{
		int opt = read();
		if (opt == 3)
		{
			int x = read(), y = read();
			SEG::modify(1, x, y);
			a[x] = y;
		}
		else
		{
			int l = read(), r = read(), k = read();
			if (opt == 1)
				printf("%d\n", SEG::queryrank(1, l, r, k) + 1);
			else if (opt == 2)
				printf("%d\n", SEG::querynum(l, r, k));
			else if (opt == 4)
				printf("%d\n", SEG::querypre(1, l, r, k));
			else
				printf("%d\n", SEG::querysuf(1, l, r, k));
		}
	}
	return 0;
}