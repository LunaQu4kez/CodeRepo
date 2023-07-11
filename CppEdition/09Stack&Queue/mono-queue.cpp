/*
有一个长为 n 的序列 a，以及一个大小为 k 的窗口。
现在这个从左边开始向右滑动，每次滑动一个单位，求出每次滑动后窗口中的最大值。
输入格式
输入一共有两行，第一行有两个正整数 n, k。 
第二行 n 个整数，表示序列 a
输出格式
一行，为每次窗口滑动的最小值
*/
#include<bits/stdc++.h>
using namespace std;

int n, k;
struct node {
    int v, id;
} a[1000010];
deque<node> q;

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].v);
        a[i].id = i;
    }
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && q.back().v <= a[i].v) q.pop_back();
        q.push_back(a[i]);
        if (q.front().id == i - k) q.pop_front();
        if (i >= k) printf("%d ", q.front().v);
    }

    return 0;
}