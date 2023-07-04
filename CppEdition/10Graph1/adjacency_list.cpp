/*
题目描述
给定一个 n 个顶点 m 条边的无向图。请以邻接矩阵的形式输出这一张图。

输入格式
第一行输入两个正整数 n 和 m，表示图的顶点数和边数。
第二行开始，往后 m 行，每行输入两个以空格隔开的正整数 u,v，表示 u,v 顶点之间有一条边直接相连。

输出格式
输出 n 行。第 i 行首先先输出一个整数 d_i，表示这个顶点的度数，再按照从小到大的顺序，依次输出
与顶点 i 直接相连的所有顶点。
*/

/*
用一个结构体vector（为了节省空间，用vector来存）存储每个边的起点和终点，然后用一个二维vector（也就是一个vector数组）存储边的信息。
这个存储方法可能有点难理解，不过其实也没那么难：我们用 e[a][b] = c，来表示顶点 a 的第 b 条边是第 c 号边。
*/

#include<bits/stdc++.h>
using namespace std;

struct edge {
	int u, v;  // 起点、终点
    //int u, v, w;  // 起点、终点、权值
}; 

vector<int> e[100001];
vector<edge> s;

bool cmp(edge x, edge y) {
	if (x.v == y.v) return x.u < y.u;
	else return x.v < y.v;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		s.push_back((edge){x, y});
        s.push_back((edge){y, x}); 
	}
    sort(s.begin(), s.end(), cmp);
	for (int i = 0; i < s.size(); i++) e[s[i].u].push_back(i);

    for (int i = 1; i <= n; i++) {
        printf("%d ", e[i].size());
        for (int j = 0; j < e[i].size(); j++) {
            printf("%d ", s[e[i][j]].v);
        }
        printf("\n");
    }
}