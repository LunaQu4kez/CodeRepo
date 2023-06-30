import java.util.Scanner;

class UF {
    private int[] parent;  // parent[i] = parent of i
    private byte[] rank;   // rank[i] = rank of subtree rooted at i (never more than 31)
    private int count;     // number of components

    public UF(int n) {
        count = n;
        parent = new int[n];
        rank = new byte[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    private int find(int p) {
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;
    }

    public int count() {
        return count;
    }

    public boolean connected(int p, int q) {
        return find(p) == find(q);
    }

    private void union(int p, int q) {
        int r1 = find(p);
        int r2 = find(q);
        if (r1 == r2) return;

        if      (rank[r1] < rank[r2]) parent[r1] = r2;
        else if (rank[r1] > rank[r2]) parent[r2] = r1;
        else {
            parent[r2] = r1;
            rank[r1]++;
        }
        count--;
    }


    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        UF uf = new UF(n);
        for (int i = 0; i < m; i++) {
            int p = sc.nextInt();
            int q = sc.nextInt();
            if (uf.find(p) == uf.find(q)) continue;
            uf.union(p, q);
        }
        System.out.println(uf.count() + " components");
    }
}
