/*
题目描述
已知一个数列，你需要进行下面两种操作：
-将某一个数加上 x
-求出某区间每一个数的和

输入格式
第一行包含两个正整数 n,m，分别表示该数列数字的个数和操作的总个数。
第二行包含 n 个用空格分隔的整数，其中第 i 个数字表示数列第 i 项的初始值。
接下来 m 行每行包含 3 个整数，表示一个操作，具体如下：
1 x k 含义：将第 x 个数加上 k
2 x y 含义：输出区间 [x,y] 内每个数的和

输出格式
输出包含若干行整数，即为所有操作 2 的结果。
*/

#include<bits/stdc++.h>
using namespace std;

int n, m, tree[2000010];

int lowbit(int k) {
    return k & -k;
}

void add(int x, int k) {  // 将第 x 个数加上 k
    while (x <= n) {
        tree[x] += k;
        x += lowbit(x);
    }
}

int sum(int x) {  // 第 1 到第 x 个数的和
    int ans = 0;
    while (x != 0) {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int num;
        scanf("%d", &num);
        add(i, num);
    }
    for (int i = 1; i <= m; i++) {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1) add(x, y);
        if (opt == 2) printf("%d\n", sum(y) - sum(x - 1));
    }

    return 0;
}