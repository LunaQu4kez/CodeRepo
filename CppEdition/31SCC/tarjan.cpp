/*
题目描述
有一个 n 个点，m 条边的有向图，请求出这个图点数大于 1 的强连通分量个数。

输入格式
第一行为两个整数 n 和 m。
第二行至 m + 1 行，每一行有两个整数 a 和 b，表示有一条从 a 到 b 的有向边。

输出格式
仅一行，表示点数大于 1 的强连通分量个数。
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10;

stack<int> S;
vector<int> G[MAXN]; // 存图 

// n：点数 m：边数 deep：深度 sum：强连通块个数  ans：答案个数 
int n, m, deep, sum, ans;  
// col：第 x 个点染的什么颜色 
int dfn[MAXN], low[MAXN], col[MAXN]; 
int cnt[MAXN]; // 颜色为 x 的个数 
bool vis[MAXN]; // 判断有没有访问过 

void Tarjan(int now) {
	vis[now] = true; // 标记为访问过
	S.push(now); // 将该点压入栈中 
	dfn[now] = low[now] = ++deep;  // 记录时间戳
	for(int i=0; i<G[now].size(); i++) {  // 搜索与该点联通的点 
		int To = G[now][i];  // 下一个将要访问的点 
		if(!dfn[To]) {  // 如果没有被搜过 
			Tarjan(To);  // 开始搜索 
			low[now] = min(low[now], low[To]);  // 回溯更新 low 值 
		}
		else if(vis[To]) low[now] = min(low[now], low[To]);  // 搜过了 直接更新 low 
	}
	if(dfn[now] == low[now]) {  // 找到一个强连通块的根 
		col[now] = ++sum;   // 染色 
		vis[now] = false;  
		while(true) {  // 将搜索栈中该点以上的点弹出 他们都是在这个强联通块中 
			int x = S.top(); S.pop();
			col[x] = sum;  // 该强联通块染成第 sum种颜色 
			vis[x] = false;
			if(now == x) break;  // 将根弹出后 结束循环 
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i=1; i<=m; i++) {  // 读入有向图 
		int x, y;
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
	}
	for(int i=1; i<=n; i++)  // 遍历 n个点 
		if(!dfn[i])  // 如果这个点没有被搜过 开始Tarjan 
			Tarjan(i);
	for(int i=1; i<=n; i++)  // 记录第 i 种颜色的点有几个 
		cnt[col[i]] ++;
	for(int i=1; i<=sum; i++)  // 如果是第 i 种颜色的点大于 1 则就是一个强联通块
		if(cnt[i] > 1)
			ans ++;
	printf("%d\n", ans);  // 输出答案 
	return 0;
}