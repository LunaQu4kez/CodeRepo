#include<bits/stdc++.h>
using namespace std;

const int INF=0x7fffffff;
int cnt = 0; // 值的种类数（值可以重复）
struct node
{
    int val, size, cnt, ls, rs; 
    // val 是权值，ls/rs 是左/右孩子的下标，cnt 是当前的权值出现了几次，size 是子树大小和自己的大小的和
} tree[1000010];


// 向根节点为 x 的树中添加 v
inline void add(int x, int v)
{
    tree[x].size++;
    if (tree[x].val == v)
    {
        tree[x].cnt++;
        return;
    }
    if (tree[x].val > v)
    {
        if (tree[x].ls != 0) add(tree[x].ls, v);
        else
        {
            cnt++;
            tree[cnt].val = v;
            tree[cnt].size = tree[cnt].cnt = 1;
            tree[x].ls = cnt;
        }
    }
    else
    {
        if (tree[x].rs != 0) add(tree[x].rs, v);
        else
        {
            cnt++;
            tree[cnt].val = v;
            tree[cnt].size = tree[cnt].cnt = 1;
            tree[x].rs = cnt;
        }
    }
}


// 查询根节点为 x 的树中，val 的前驱（小于 val，且最大的数）
// ans 传入 -INF
int front(int x, int val, int ans) {
    if (tree[x].val >= val)
    {
        if (tree[x].ls == 0) return ans;
        else return front(tree[x].ls, val, ans);
    }
    else
    {
        if (tree[x].rs == 0) return tree[x].val;
        else return front(tree[x].rs, val, tree[x].val);
    }
}


// 查询根节点为 x 的树中，val 的后继（大于 val，且最小的数）
// ans 传入 INF
int next(int x, int val, int ans) {
    if (tree[x].val <= val)
    {
        if (tree[x].rs == 0) return ans;
        else return next(tree[x].rs, val, ans);
    }
    else
    {
        if (tree[x].ls == 0) return tree[x].val;
        else return next(tree[x].ls, val, tree[x].val);
    }
}


// 查询根节点为 x 的树中，排名为 k 的数
int rank_kth(int x, int k)
{
    if (x == 0) return INF;
    if (tree[tree[x].ls].size >= k) return rank_kth(tree[x].ls, k);
    if (tree[tree[x].ls].size + tree[x].cnt >= k) return tree[x].val;
    return rank_kth(tree[x].rs, k - tree[tree[x].ls].size - tree[x].cnt);
}


// 查询根节点为 x 的树中，val 的排名（排名定义为比当前数小的数的个数+1）
int rank_val(int x, int val)
{
    if (x == 0) return 0;
    if (val == tree[x].val) return tree[tree[x].ls].size;
    if (val < tree[x].val) return rank_val(tree[x].ls, val);
    return rank_val(tree[x].rs, val) + tree[tree[x].ls].size + tree[x].cnt;
}


int main()
{
    n = read();
    while (n--)
    {
        opt = read();
        x = read();
        if (opt == 1) printf("%d\n", rank_val(1, x) + 1);
        else if (opt == 2) printf("%d\n", rank_kth(1, x));
        else if (opt == 3) printf("%d\n", front(1, x, -INF));
        else if (opt == 4) printf("%d\n", next(1, x, INF));
        else
        {
            if (cnt == 0)
            {
                cnt++;
                tree[cnt].cnt=tree[cnt].size = 1;
                tree[cnt].val = x;
            }
            else add(1, x);
        }
    }

    return 0;
}