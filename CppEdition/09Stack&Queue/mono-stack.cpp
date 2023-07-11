/*
题目描述
给出项数为 n 的整数数列 a_(1…n)。 定义函数 f(i) 代表数列中第 i 个元素之后第一个大于 a_i 的元素的下标，
即 f(i) = min{j} (i < j ≤ n, a_j > a_i)。若不存在，则 f(i) = 0 .试求出 f(1…n)。

输入格式
第一行一个正整数 n。
第二行 n 个正整数 a_(1…n) 

输出格式
一行 n 个整数, f(1…n) 的值。
*/

#include<bits/stdc++.h>
using namespace std;
int n, a[3000010], f[3000010]; // a--输入，f--存储答案
stack<int> s;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = n; i >= 1; i--)
	{
		while (!s.empty() && a[s.top()] <= a[i]) s.pop();
		f[i] = s.empty() ? 0 : s.top();
		s.push(i);//压入当前元素
	}
	for (int i = 1; i <= n; i++) printf("%d ", f[i]);

	return 0;
}