/*
ST 表经典题————静态区间最大值
题目描述
给定一个长度为 N 的数列，和 M 次询问，求出每一次询问的区间内数字的最大值。

输入格式
第一行包含两个整数 N,M，分别表示数列的长度和询问的个数。
第二行包含 N 个整数（记为 a_i），依次表示数列的第 i 项。
接下来 M 行，每行包含两个整数 l_i, r_i，表示查询的区间为 [l_i, r_i]。

输出格式
输出包含 M 行，每行一个整数，依次表示每一次询问的结果。
*/

#include<bits/stdc++.h>
using namespace std;

int st[1000010][21], n, m;

int query(int l, int r)
{
    int k = log2(r - l + 1); 
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &st[i][0]);
    for (int j = 1; j <= 21; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++) 
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]); 
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r));
    }

    return 0;
}