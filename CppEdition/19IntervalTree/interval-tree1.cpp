/*
题目描述
已知一个数列，你需要进行下面两种操作：
-将某区间每一个数加上 k
-求出某区间每一个数的和

输入格式
第一行包含两个正整数 n,m，分别表示该数列数字的个数和操作的总个数。
第二行包含 n 个用空格分隔的整数，其中第 i 个数字表示数列第 i 项的初始值。
接下来 m 行每行包含 3 或 4 个整数，表示一个操作，具体如下：
1 x y k 含义：将区间 [x,y] 内每个数加上 k
2 x y 含义：输出区间 [x,y] 内每个数的和

输出格式
输出包含若干行整数，即为所有操作 2 的结果。
*/

#include<bits/stdc++.h>
using namespace std;

int a[100010];

struct tree {  
    int l, r;  // l，r 代表该节点维护的区间范围
    long long pre, add;  // pre 代表该节点维护的值，add 表示 lazy 标记
} t[4*100010 + 2];

void bulid(int p, int l, int r) {
    t[p].l = l; t[p].r = r;  // 以 p 为编号的节点维护的区间为 l 到 r
    if (l == r) {
        t[p].pre = a[l];
        return;
    }
    int mid = l + r >> 1;
    bulid(2*p, l, mid);
    bulid(2*p + 1, mid + 1, r);
    t[p].pre = t[p*2].pre + t[p*2 + 1].pre;
}

void spread(int p) {
    if (t[p].add) {
        t[p*2].pre += t[p].add * (t[p*2].r - t[p*2].l + 1);
        t[p*2 + 1].pre += t[p].add * (t[p*2 + 1].r - t[p*2 + 1].l + 1);
        t[p*2].add += t[p].add;
        t[p*2 + 1].add += t[p].add;
        t[p].add = 0;
    }
}

void change(int p, int x, int y, int z) {  // 将 [x,y] 区间内每个数加上 z，初始 p 传入 1
    if (x <= t[p].l && y >= t[p].r) {
        t[p].pre += (long long)z * (t[p].r - t[p].l + 1);
        t[p].add += z;
        return;
    }
    spread(p);
    int mid = t[p].l + t[p].r >> 1;
    if (x <= mid) change(p*2, x, y, z);
    if (y > mid) change(p*2 + 1, x, y, z);
    t[p].pre = t[p*2].pre + t[p*2 + 1].pre;   
}

long long query(int p, int x, int y) {  // 查询 [x,y] 区间内每个数的和，初始 p 传入 1
    if (x <= t[p].l && y >= t[p].r) return t[p].pre;
    spread(p);
    int mid = t[p].l + t[p].r >> 1;
    long long ans = 0;
    if (x <= mid) ans += query(p*2, x, y);
    if (y > mid) ans += query(p*2 + 1, x, y);
    return ans;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    bulid(1, 1, n);
    for (int i = 1; i <= m; i++)
    {
        int opt, x, y, z;
        scanf("%d", &opt);
        if (opt == 1) {
            scanf("%d%d%d", &x, &y, &z);
            change(1, x, y, z);
        } else {
            scanf("%d%d", &x, &y);
            cout << query(1, x, y) << endl;
        }
    }

    return 0;
}