import java.util.Arrays;

// 树上倍增
public class TreeDoubling {
    public static final int X = 16; // 根据最大节点数量决定  2^X 大于最大节点数量即可
    int[][] anc; // anc[i][j] 表示节点 i 的第 2^j 个祖先

    public TreeDoubling(int n, int[] parent) {
        anc = new int[n][X];
        for (int i = 0; i < n; i++) {
            Arrays.fill(anc[i], -1);
        }
        for (int i = 0; i < n; i++) {
            anc[i][0] = parent[i];
        }
        for (int j = 1; j < X; j++) {
            for (int i = 0; i < n; i++) {
                if (anc[i][j - 1] != -1) {
                    anc[i][j] = anc[anc[i][j - 1]][j - 1];
                }
            }
        }
    }

    // 查询 node 的第 k 个祖先
    public int getKthAncestor(int node, int k) {
        for (int j = 0; j < X; j++) {
            if (((k >> j) & 1) != 0) {
                node = anc[node][j];
                if (node == -1) {
                    return -1;
                }
            }
        }
        return node;
    }

}
