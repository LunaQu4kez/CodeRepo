/*
题目描述
如题，你需要维护这样的一个长度为 N 的数组，支持如下几种操作：
-在某个历史版本上修改某一个位置上的值
-访问某个历史版本上的某一位置的值
此外，每进行一次操作（对于操作2，即为生成一个完全一样的版本，不作任何改动），就会生成一个新的版本。
版本编号即为当前操作的编号（从1开始编号，版本0表示初始状态数组）

输入格式
输入的第一行包含两个正整数 N,M，分别表示数组的长度和操作的个数。
第二行包含 N 个整数，依次为初始状态下数组各位的值（依次为 a_i）。
接下来 M 行每行包含 3 或 4 个整数，代表两种操作之一：
对于操作 1 ，格式为 v_i 1 loc value，即为在版本 v_i 的基础上，将 a_loc 修改为 value_i
对于操作2，格式为 v_i 2 loc，即访问版本 v_i 中的 a_loc 的值，生成一样版本的对象应为v_i

输出格式
输出包含若干行，依次为每个操作2的结果。
*/

#include<bits/stdc++.h>
using namespace std;

const int maxn = 1000010;
int n, m, a[maxn], root[maxn * 4], top, rt, opt, x, y;

struct tree_node {
	int l, r, val;
} tree[maxn * 4];

int clone(int node){
	top++;
	tree[top]=tree[node]; // 全部信息都传到新节点
	return top;
}

int maketree(int node,int begin,int end){
	node=++top;
	if(begin==end){
		tree[node].val=a[begin];
		return top;
	}
	int mid=(begin+end)>>1;
	tree[node].l=maketree(tree[node].l,begin,mid);
	tree[node].r=maketree(tree[node].r,mid+1,end);
	return node;
}

int update(int node,int begin,int end,int x,int val){
	node=clone(node);	//更新就要新建节点 
	if(begin==end){
		tree[node].val=val;
	}else{
		int mid=(begin+end)>>1;
		if(x<=mid)
			tree[node].l=update(tree[node].l,begin,mid,x,val);	//访问左子树 
		else
			tree[node].r=update(tree[node].r,mid+1,end,x,val);	//访问右子树 
	}
	return node;
}

int query(int node,int begin,int end,int x){
	if(begin==end){
		return tree[node].val;
	}else{
		int mid=(begin+end)>>1;
		if(x<=mid)
			return query(tree[node].l,begin,mid,x);	//访问左子树 
		else
			return query(tree[node].r,mid+1,end,x);	//访问右子树 
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++)scanf("%d", &a[i]);
	root[0]=maketree(0,1,n);	// root[i] 为 i 版本的根编号，刚开始编号为 0 
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&rt,&opt,&x);
		if(opt==1){
			scanf("%d",&y);
			root[i]=update(root[rt],1,n,x,y);
		}
		else{
			printf("%d\n",query(root[rt],1,n,x));
			root[i]=root[rt];
		}
	}

    return 0;
}