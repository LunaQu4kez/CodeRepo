/*
题目描述
已知一个数列，你需要进行下面 3 种操作：
-将某区间每一个数乘上 k
-将某区间每一个数加上 k
-求出某区间每一个数的和

输入格式
第一行包含三个正整数 n,q,m，分别表示该数列数字的个数，操作的总个数和模数。
第二行包含 n 个用空格分隔的整数，其中第 i 个数字表示数列第 i 项的初始值。
接下来 q 行每行包含 3 或 4 个整数，表示一个操作，具体如下：
1 x y k 含义：将区间 [x,y] 内每个数乘上 k
2 x y k 含义：将区间 [x,y] 内每个数加上 k
3 x y 含义：输出区间 [x,y] 内每个数的和对 m 取模所得的结果

输出格式
输出包含若干行整数，即为所有操作 3 的结果。
*/


#include <bits/stdc++.h>

#define MAXN 100010
#define ll long long

using namespace std;

int n, m, mod;
int a[MAXN];

struct tree_node {
	ll sum, add, mul;
	int l, r;
} s[MAXN * 4];

void update(int pos) {
	s[pos].sum = (s[pos << 1].sum + s[pos << 1 | 1].sum) % mod;
    return;
}

void pushdown(int pos) { // pushdown维护
	s[pos << 1].sum = (s[pos << 1].sum * s[pos].mul + s[pos].add * (s[pos << 1].r - s[pos << 1].l + 1)) % mod;
	s[pos << 1 | 1].sum = (s[pos << 1 | 1].sum * s[pos].mul + s[pos].add * (s[pos << 1 | 1].r - s[pos << 1 | 1].l + 1)) % mod;
	
	s[pos << 1].mul = (s[pos << 1].mul * s[pos].mul) % mod;
	s[pos << 1 | 1].mul = (s[pos << 1 | 1].mul * s[pos].mul) % mod;
	
	s[pos << 1].add = (s[pos << 1].add * s[pos].mul + s[pos].add) % mod;
	s[pos << 1 | 1].add = (s[pos << 1 | 1].add * s[pos].mul + s[pos].add) % mod;
		
	s[pos].add = 0;
	s[pos].mul = 1;
	return; 
}

void build_tree(int pos, int l, int r) { // 建树
	s[pos].l = l;
	s[pos].r = r;
	s[pos].mul = 1;
	
	if (l == r) {
		s[pos].sum = a[l] % mod;
		return;
	}
	
	int mid = (l + r) >> 1;
	build_tree(pos << 1, l, mid);
	build_tree(pos << 1 | 1, mid + 1, r);
	update(pos);
	return;
}

void mul(int pos, int x, int y, int k) { // 区间乘法
	if (x <= s[pos].l && s[pos].r <= y) {
		s[pos].add = (s[pos].add * k) % mod;
		s[pos].mul = (s[pos].mul * k) % mod;
		s[pos].sum = (s[pos].sum * k) % mod;
		return;
	}
	
	pushdown(pos);
	int mid = (s[pos].l + s[pos].r) >> 1;
	if (x <= mid) mul(pos << 1, x, y, k);
	if (y > mid) mul(pos << 1 | 1, x, y, k);
	update(pos);
	return;
}

void add(int pos, int x, int y, int k) { // 区间加法
	if (x <= s[pos].l && s[pos].r <= y) {
		s[pos].add = (s[pos].add + k) % mod;
		s[pos].sum = (s[pos].sum + k * (s[pos].r - s[pos].l + 1)) % mod;
		return;
	}
	
	pushdown(pos);
	int mid = (s[pos].l + s[pos].r) >> 1;
	if (x <= mid) add(pos << 1, x, y, k);
	if (y > mid) add(pos << 1 | 1, x, y, k);
	update(pos);
	return;
}

ll query(int pos, int x, int y) { // 区间询问
	if (x <= s[pos].l && s[pos].r <= y) {
		return s[pos].sum;
	}
	
	pushdown(pos);
	ll val = 0;
	int mid = (s[pos].l + s[pos].r) >> 1;
	if (x <= mid) val = (val + query(pos << 1, x, y)) % mod;
	if (y > mid) val = (val + query(pos << 1 | 1, x, y)) % mod;
	return val;
}

int main() {
	scanf("%d%d%d", &n, &m, &mod);
	
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	
	build_tree(1, 1, n);
	
	for (int i = 1; i <= m; i++) {
		int opt, x, y;
		scanf("%d%d%d", &opt, &x, &y);
		if (opt == 1) {
			int k;
			scanf("%d", &k);
			mul(1, x, y, k);
		}
		if (opt == 2) {
			int k;
			scanf("%d", &k);
			add(1, x, y, k);
		}
		if (opt == 3) {
			printf("%lld\n", query(1, x, y));
		}
	}
    
	return 0;
}