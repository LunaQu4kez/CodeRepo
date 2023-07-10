/*
题目描述
一棵包含 N 个结点的树（连通且无环），每个节点上包含一个数值，需要支持以下操作：
1 x y z，表示将树从 x 到 y 结点最短路径上所有节点的值都加上 z。
2 x y，表示求树从 x 到 y 结点最短路径上所有节点的值之和。
3 x z，表示将以 x 为根节点的子树内所有节点值都加上 z。
4 x 表示求以 x 为根节点的子树内所有节点值之和

输入格式
第一行包含 4 个正整数 N,M,R,P，分别表示树的结点个数、操作个数、根节点序号和取模数（即所有的输出结果均对此取模）。
接下来一行包含 N 个非负整数，分别依次表示各个节点上初始的数值。
接下来 N−1 行每行包含两个整数 x,y，表示点 x 和点 y 之间连有一条边（保证无环且连通）。
接下来 M 行每行包含若干个正整数，每行表示一个操作。

输出格式
输出包含若干行，分别依次表示每个操作 2 或操作 4 所得的结果（对 P 取模）。
*/

#include<bits/stdc++.h>
#define N 100003
#define inf 0x3f3f3f3f
#define ll long long
using namespace std;

vector<int> adj[N];
int n, m, r, p, cnt;
int son[N], depth[N], fa[N], siz[N];  // 重儿子编号、深度、父节点编号、子树大小
int id[N], top[N], w[N];  // 第几个被遍历，所在重链顶点，节点上的初始值
ll c1[N], c2[N];

//以下为树状数组
inline int lowbit(int x){
    return x&(-x);
}

inline void add(int l,int r,int x){
    x %= p;
    int ad1 = (ll)(l-1)*x%p;
    int ad2 = (ll)r*x%p;
    for(int t=l;t<=n;t+=lowbit(t)){
        c1[t] = (c1[t]+x)%p;
        c2[t] = (c2[t]+ad1)%p;
    }
    for(int t=r+1;t<=n;t+=lowbit(t)){
        c1[t] = (c1[t]-x)%p;
        c1[t] = (c1[t]+p)%p;
        c2[t] = (c2[t]-ad2)%p;
        c2[t] = (c2[t]+p)%p;
    }
}

inline int qwq(int i){ //qwq
    int res = 0;
    for(int t=i;t>0;t-=lowbit(t)){
        res = (res+(ll)i*c1[t]%p)%p;
        res = (res-c2[t])%p;
        res = (res+p)%p;
    }
    return res;
}

inline int query(int l,int r){
    int res = (qwq(r)-qwq(l-1))%p;
    return (res+p)%p;
}
//以上树状数组

inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9'){
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
}

void print(int x){
    if(x>9) print(x/10);
    putchar(x%10+'0');
}

void dfs1(int u,int f){
    fa[u] = f;
    siz[u] = 1;
    depth[u] = depth[f]+1;
    int v,t = -1,l = adj[u].size();
    for(int i=0;i<l;++i){
        v = adj[u][i];
        if(v==f) continue;
        dfs1(v,u);
        siz[u] += siz[v];
        if(siz[v]>t){
            t = siz[v];
            son[u] = v;
        }
    }
}

void dfs2(int u,int f){
    top[u] = f;
    id[u] = ++cnt;
    if(w[u]!=0)
        add(id[u],id[u],w[u]);
    if(son[u]==0) return;
    dfs2(son[u],f);
    int v,l = adj[u].size();
    for(int i=0;i<l;++i){
        v = adj[u][i];
        if(v==son[u]||v==fa[u]) continue;
        dfs2(v,v);
    }
}

int queryPath(int u,int v){
    int res = 0;
    while(top[u]!=top[v]){
        if(depth[top[u]]<depth[top[v]])
            swap(u,v);
        res = (res+query(id[top[u]],id[u]))%p;
        u = fa[top[u]];
    }
    if(depth[u]>depth[v]) swap(u,v);
    res = (res+query(id[u],id[v]))%p;
    return res;
}

void addPath(int u,int v,int k){
    k %= p;
    while(top[u]!=top[v]){
        if(depth[top[u]]<depth[top[v]])
            swap(u,v);
        add(id[top[u]],id[u],k);    
        u = fa[top[u]];
    }
    if(depth[u]>depth[v]) swap(u,v);
    add(id[u],id[v],k);
}

int querySon(int u){
    return query(id[u],id[u]+siz[u]-1);
}

void addSon(int u,int k){
    k %= p;
    add(id[u],id[u]+siz[u]-1,k);
}

int main(){
    int u,v;
    read(n),read(m),read(r),read(p);
    for(int i=1;i<=n;++i)
        read(w[i]);
    for(int i=1;i<n;++i){
        read(u),read(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }    
    dfs1(r,0);
    dfs2(r,r);
    int ans,op,x,y,z;
    while(m--){
        read(op),read(x);
        if(op==1){
            read(y),read(z);
            addPath(x,y,z);
            continue;
        }
        if(op==2){
            read(y);
            ans = queryPath(x,y);
            print(ans);
            putchar('\n');
            continue;
        }
        if(op==3){
            read(z);
            addSon(x,z);
            continue;
        }
        ans = querySon(x);
        print(ans);
        putchar('\n');
    }
    return 0;
}

inline int lca(int u,int v){
	while(top[u]!=top[v]){
    	if(depth[top[u]]<depth[top[v]])
        	swap(u,v);
        u = fa[top[u]];    
    }
    if(depth[u]<depth[v]) return u;
    return v;
}