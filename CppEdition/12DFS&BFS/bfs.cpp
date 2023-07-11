#include<bits/stdc++.h>
using namespace std;

struct edge {
	int u, v;
};

vector<int> e[100010];
vector<edge> s;
bool vis1[100010] = {0}, vis2[100010] = {0};

bool cmp(edge x, edge y) {
	if (x.v == y.v)	return x.u < y.u;
	else return x.v < y.v;
}

void bfs(int x) {
	queue<int> q;
	q.push(x);
	printf("%d ", x);
	vis2[x] = 1;
	while (!q.empty()) {
		int fro = q.front();
		for (int i = 0; i < e[fro].size(); i++) {
			int point = s[e[fro][i]].v;
			if (!vis2[point]) {
				q.push(point); 
				printf("%d ", point);
				vis2[point] = 1;
			}
		}
		q.pop();
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

	bfs(1);

    return 0;
}