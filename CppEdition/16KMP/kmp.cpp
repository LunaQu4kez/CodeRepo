/*
洛谷P3375（改）
题目描述
给出两个字符串 s_1 和 s_2 ，若 s_1 的区间 [l,r] 子串与 s_2 完全相同，则称 s_2 在 s_1 中出现了，其出现位置为 l。
现在请你求出 s_2 在 s_1 中所有出现的位置。

输入格式
第一行为一个字符串，即为 s_1 。
第二行为一个字符串，即为 s_2 。

输出格式
首先输出若干行，每行一个整数，按从小到大的顺序输出 s_2 在 s_1 中出现的位置

保证 1 ≤ |s_1|,|s_2| ≤ 10^6 , s_1, s_2 中均只含大写英文字母
*/

#include<bits/stdc++.h>
using namespace std;

int kmp[1000010];  // kmp[i] 用于记录当匹配到模式串的第 i 位之后失配,该跳转到模式串的哪个位置
int la, lb, j; 
char a[1000010], b[1000010];

int main()
{
    cin >> a + 1;
    cin >> b + 1;
    la = strlen(a + 1);
    lb = strlen(b + 1);
    for (int i = 2; i <= lb; i++) {     
	    while (j && b[i] != b[j + 1]) j = kmp[j];    
        if (b[j + 1] == b[i]) j++;
        kmp[i] = j;
    }
    j = 0;
    for (int i = 1; i <= la; i++) {
        while (j > 0 && b[j + 1] != a[i]) j = kmp[j];
        if (b[j + 1] == a[i]) j++;
        if (j == lb) {
            cout << i - lb + 1 << endl;
            j = kmp[j];
        }
    }

    return 0;
}