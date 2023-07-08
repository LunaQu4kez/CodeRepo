/*
洛谷P8306（改）
题目描述
给定 n 个模式串 s1, s2, … , sn 和 q 次询问，每次询问给定一个文本串 t_i ，
请回答 s1 ∼ sn 中有多少个字符串 sj 满足 t_i 是 sj 的前缀。

输入格式
第一行是两个整数，分别表示模式串的个数 n 和询问的个数 q。
接下来 n 行，每行一个字符串，表示一个模式串。
接下来 q 行，每行一个字符串，表示一次询问。

输出格式
输出一行一个整数表示答案。
*/

#include<bits/stdc++.h>
using namespace std;

int n, q, t[3000010][65], cnt[3000010], idx;
char s[3000010];

int getnum(char x) {
    if (x >= 'A' && x <= 'Z') return x - 'A';
    else if (x >= 'a' && x <= 'z') return x - 'a' + 26;
    else return x - '0' + 52;
}

void insert(char str[]) {
    int p = 0, len = strlen(str);
    for (int i = 0; i < len; i++) {
        int c = getnum(str[i]);
        if(!t[p][c]) t[p][c] = ++idx;
        p = t[p][c];
        cnt[p]++;
    }
}

int find(char str[]) {
    int p = 0, len = strlen(str);
    for (int i = 0; i < len; i++) {
        int c = getnum(str[i]);
        if (!t[p][c]) return 0;
        p = t[p][c];
    }
    return cnt[p];
}

int main()
{
    for (int i = 0; i <= idx; i++)
        for (int j = 0; j <= 122; j++)
            t[i][j] = 0;
    for (int i = 0; i <= idx; i++)
        cnt[i] = 0;
    idx = 0;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s);
        insert(s);
    }
    for (int i = 1; i <= q; i++) {
        scanf("%s", s);
        printf("%d\n", find(s));
    }
    
    return 0;
}