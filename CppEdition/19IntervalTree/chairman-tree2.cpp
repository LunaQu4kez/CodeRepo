/*
可持久化权值线段树入门题——静态区间第 k 小

题目描述
如题，给定 n 个整数构成的序列 a，将对于指定的闭区间 [l,r] 查询其区间内的第 k 小值。

输入格式
第一行包含两个整数，分别表示序列的长度 n 和查询的个数 m。
第二行包含 n 个整数，第 i 个整数表示序列的第 i 个元素 a_i。
接下来 m 行每行包含三个整数 l,r,k , 表示查询区间 [l,r] 内的第 k 小值。

输出格式
对于每次询问，输出一行一个整数表示答案。
*/

#include<bits/stdc++.h>
#define mid (l + r) / 2
using namespace std;

const int N = 200010;
int n, q, m, cnt = 0;
int a[N], b[N], T[N];
int sum[N<<5], L[N<<5], R[N<<5];

inline int build(int l, int r)
{
    int rt = ++ cnt;
    sum[rt] = 0;
    if (l < r){
        L[rt] = build(l, mid);
        R[rt] = build(mid+1, r);
    }
    return rt;
}

inline int update(int pre, int l, int r, int x)
{
    int rt = ++ cnt;
    L[rt] = L[pre]; R[rt] = R[pre]; sum[rt] = sum[pre]+1;
    if (l < r){
        if (x <= mid) L[rt] = update(L[pre], l, mid, x);
        else R[rt] = update(R[pre], mid+1, r, x);
    }
    return rt;
}

inline int query(int u, int v, int l, int r, int k)
{
    if (l >= r) return l;
    int x = sum[L[v]] - sum[L[u]];
    if (x >= k) return query(L[u], L[v], l, mid, k);
    else return query(R[u], R[v], mid+1, r, k-x);
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i ++){
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b+1, b+1+n);
    m = unique(b+1, b+1+n)-b-1;
    T[0] = build(1, m);
    for (int i = 1; i <= n; i ++){
        int t = lower_bound(b+1, b+1+m, a[i])-b;
        T[i] = update(T[i-1], 1, m, t);
    }
    while (q --){
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        int t = query(T[x-1], T[y], 1, m, z);
        printf("%d\n", b[t]);
    }
    return 0;
}