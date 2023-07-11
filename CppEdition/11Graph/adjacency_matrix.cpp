/*
题目描述
给定一个 n 个顶点 m 条边的无向图。请以邻接矩阵的形式输出这一张图。

输入格式
第一行输入两个正整数 n 和 m，表示图的顶点数和边数。
第二行开始，往后 m 行，每行输入两个以空格隔开的正整数 u,v，表示 u,v 顶点之间有一条边直接相连。

输出格式
输出 n 行 n 列的矩阵，以空格隔开每一行之间的数表示邻接矩阵。第 i 行第 j 列的数为 1 则表示顶点 
i,j 之间有一条边直接相连；若为 0 则表示没有直接相连的边。
*/

#include<bits/stdc++.h>
using namespace std;

int g[1010][1010] = {0}, n, m;


int main()
{
    scanf("%d%d", &n, &m);
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x][y] = 1;
        g[y][x] = 1;  // 有向图去掉这一行
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }

    return 0;
}