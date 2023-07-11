/*
P3369
题目描述
您需要写一种数据结构（可参考题目标题），来维护一些数，其中需要提供以下操作：
1、插入 x 数
2、删除 x 数(若有多个相同的数，应只删除一个)
3、查询 x 数的排名(排名定义为比当前数小的数的个数 + 1)
4、查询排名为 x 的数
5、求 x 的前驱(前驱定义为小于 x，且最大的数)
6、求 x 的后继(后继定义为大于 x，且最小的数)

输入格式
第一行为 n，表示操作的个数,下面 n 行每行有两个数 opt 和 x，opt 表示操作的序号(1 ≤ opt ≤ 6)

输出格式
对于操作 3, 4, 5, 6 每行输出一个数，表示对应答案
*/

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

int read() {
	int out = 0, flag = 1;
	char c = getchar();
    while (c < '0' || c >'9') {
		if (c == '-') flag = -1;
		c = getchar();
	}
    while (c >= '0' && c <= '9') {
		out = out * 10 + c - '0';
		c = getchar();
	}
    return flag * out;
}

// 平衡树，利用BST性质查询和修改，利用随机和堆优先级来保持平衡，把树的深度控制在log N，保证了操作效率
// 基本平衡树有以下几个比较重要的函数：新建，插入，删除，旋转
// 节点的基本属性有val(值)，dat(随机出来的优先级)
// 通过增加属性，结合BST的性质可以达到一些效果，如size(子树大小，查询排名)，cnt(每个节点包含的副本数)等

const int maxn = 1000019, INF = 1e9;
int na;
int ch[maxn][2];  // [i][0]代表i左儿子，[i][1]代表i右儿子
int val[maxn], dat[maxn];
int size[maxn], cnt[maxn];
int tot, root;

// 新增节点
int addNew(int v) { 
	val[++tot] = v;
	dat[tot] = rand();
	size[tot] = 1;
	cnt[tot] = 1;
	return tot;
}

// 和线段树的pushup更新一样
void pushup(int id) {
	size[id] = size[ch[id][0]] + size[ch[id][1]] + cnt[id]; // 本节点子树大小 = 左儿子子树大小 + 右儿子子树大小 + 本节点副本数
}

// 初始化
void build() {
	root = addNew(-INF),ch[root][1] = addNew(INF);
	pushup(root);
}

// id是根节点，引用传递，d(irection)为旋转方向，0为左旋，1为右旋
void rotate(int &id, int d) {
	int temp = ch[id][d ^ 1];
	ch[id][d ^ 1] = ch[temp][d];
	ch[temp][d] = id;
	id = temp;
	pushup(ch[id][d]), pushup(id);
}

// 插入节点
void insert(int &id, int v){
	if(!id){
		id = addNew(v);  // 若节点为空，则新建一个节点
		return ;
	}
	if (v == val[id]) cnt[id]++;
	else {
		int d = v < val[id] ? 0 : 1;  // d 代表方向，按照BST的性质，小于本节点则向左，大于向右
		insert(ch[id][d],v);
		if (dat[id] < dat[ch[id][d]]) rotate(id,d ^ 1);
	}
	pushup(id);
}

// 删除节点
void remove(int &id, int v){
	if (!id) return;
	if (v == val[id]) {
		if (cnt[id] > 1) {
			cnt[id]--, pushup(id);
			return;
		}
		if (ch[id][0] || ch[id][1]) {
			if (!ch[id][1] || dat[ch[id][0]] > dat[ch[id][1]]) rotate(id,1), remove(ch[id][1],v);
			else rotate(id,0), remove(ch[id][0],v);
			pushup(id);
		}
		else id = 0;
		return;
	}
	v < val[id] ? remove(ch[id][0],v) : remove(ch[id][1],v);
	pushup(id);
}

// 查询 v 的排名
int get_rank(int id, int v) {
	if (!id) return 0;
	if (v == val[id]) return size[ch[id][0]] + 1;
	else if (v < val[id]) return get_rank(ch[id][0],v);
	else return size[ch[id][0]] + cnt[id] + get_rank(ch[id][1],v);
}

// 查询排名为 rank 的数
int get_val(int id, int rank) {
	if (!id) return INF;
	if (rank <= size[ch[id][0]]) return get_val(ch[id][0],rank);
	else if (rank <= size[ch[id][0]] + cnt[id]) return val[id];
	else return get_val(ch[id][1],rank - size[ch[id][0]] - cnt[id]);
}

// 求 v 的前驱(前驱定义为小于 v ，且最大的数)
int get_pre(int v) {
	int id = root, pre;
	while (id) {
		if (val[id] < v) pre = val[id], id = ch[id][1];
		else id = ch[id][0];
	}
	return pre;
}

// 求 v 的后继(后继定义为大于 v ，且最小的数)
int get_next(int v) {
	int id = root, next;
	while(id) {
		if (val[id] > v) next = val[id], id = ch[id][0];
		else id = ch[id][1];
	}
	return next;
}


int main() {
	build();  // 不要忘记初始化(运行build()会连同root一并初始化，所以很重要)
	na = read();
	for (int i = 1; i <= na; i++) {
		int cmd = read(), x = read();
		if (cmd == 1) insert(root, x);  // 注意：需要递归的函数都从根开始，不需要递归的函数直接查询
		else if(cmd == 2) remove(root, x);
		else if(cmd == 3) printf("%d\n", get_rank(root, x) - 1);  // 注意：因为初始化时插入了INF和-INF,所以查询排名时要减1(-INF不是第一小，是“第零小”)
		else if(cmd == 4) printf("%d\n", get_val(root, x + 1));  // 同理，用排名查询值得时候要查 x + 1 名，因为第一名(其实不是)是-INF
		else if(cmd == 5) printf("%d\n", get_pre(x));
		else if(cmd == 6) printf("%d\n", get_next(x));
	}
	return 0;
}