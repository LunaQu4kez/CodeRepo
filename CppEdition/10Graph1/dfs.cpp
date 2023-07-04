#include<bits/stdc++.h>
using namespace std;

struct edge {
	int u, v;
};

vector<int> e[100010];
vector<edge> s;
bool vis1[100010] = {0};

bool cmp(edge x, edge y) {
	if (x.v == y.v)	return x.u < y.u;
	else return x.v < y.v;
}

void dfs(int x) {
	vis1[x] = 1;
	printf("%d ", x);
	for (int i = 0; i < e[x].size(); i++) {
		int point = s[e[x][i]].v;
		if (!vis1[point]) dfs(point);
	}
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m); 
	for (int i = 0; i < m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		s.push_back((edge){x, y}); 
	}
	sort(s.begin(), s.end(), cmp);
	for (int i = 0; i < m; i++) e[s[i].u].push_back(i); 
    
	dfs(1);

    return 0;
}