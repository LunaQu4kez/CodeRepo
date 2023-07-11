/*
题目描述
已知一个数列，你需要进行下面两种操作：
-将某区间每一个数加上 x
-求出某一个数的值

输入格式
第一行包含两个正整数 n,m，分别表示该数列数字的个数和操作的总个数。
第二行包含 n 个用空格分隔的整数，其中第 i 个数字表示数列第 i 项的初始值。
接下来 m 行每行包含 2 或 4 个整数，表示一个操作，具体如下：
1 x y k 含义：将区间 [x,y] 内每个数加上 k
2 x 含义：输出第 x 个数的值

输出格式
输出包含若干行整数，即为所有操作 2 的结果。
*/

#include<bits/stdc++.h>
using namespace std;

int n, m;
int a[500010];
int tree[500010];

int lowbit(int x)
{
    return x & -x;
}

void add(int x, int k)  // 第 x 个数开始以后的每个数 + k
{
    while (x <= n)
    {
        tree[x] += k;
        x += lowbit(x);
    }
}

int search(int x)  // 目前 a[x] 相较于初始 a[x] 的变化量
{
    int ans = 0;
    while (x != 0)
    {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
    {
        int opt;
        scanf("%d", &opt);
        if (opt == 1)
        {
            int x, y, k;
            scanf("%d%d%d", &x, &y, &k);
            add(x, k);
            add(y + 1, -k);
        }
        if (opt == 2)
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", a[x] + search(x));
        }
    }

    return 0;
}