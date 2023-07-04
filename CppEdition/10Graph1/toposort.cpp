/*
题目描述
有个人的家族很大，辈分关系很混乱，请你帮整理一下这种关系。给出每个人的后代的信息。输出一个序列，使得每个人的后辈都比那个人后列出。

输入格式
第 1 行一个整数 N（1≤N≤100），表示家族的人数。接下来 N 行，第 i 行描述第 i 个人的后代编号 a_(i,j)，表示 a_(i,j) 是 i 的后代。
每行最后是 0 表示描述完毕。

输出格式
输出一个序列，使得每个人的后辈都比那个人后列出。如果有多种不同的序列，输出任意一种即可。

输入 #1
5
0
4 5 1 0
1 0
5 3 0
3 0

输出 #1
2 4 5 3 1
*/

#include<bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {if (ch=='-') f = -1; ch = getchar();}
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}

const int MAXN = 500010;

int deg[MAXN];
vector<int> g[MAXN];
queue<int> q;
vector<int> ans;

int main() 
{
	int n = read();
	for (int i = 1; i <= n; i++) {
		while (int y = read()) {
			if (!y) break;
			g[i].push_back(y);
            deg[y]++;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (deg[i] == 0) {
			q.push(i);
            ans.push_back(i);
		}
	}
	while (!q.empty()) {
		int rhs = q.front();
		q.pop();
		for (int i = 0; i < g[rhs].size(); i++) {
			int u = g[rhs][i];
			deg[u]--;
			if (deg[u] == 0) {
                q.push(u);
                ans.push_back(u);
            } 
		}
	}
    for (int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);

	return 0;
}