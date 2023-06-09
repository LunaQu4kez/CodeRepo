import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;

public class Demo {

    /**
     * 朴素 Dijkstra 算法  时间复杂度O(n^2)
     *
     * @param src   起始点
     * @param graph 邻接矩阵表示的图
     * @return src到所有点的最短路径权值和
     */
    public int[] dijkstra(int src, int[][] graph) {
        int n = graph.length;
        int[] dist = new int[n];
        Arrays.fill(dist, Integer.MAX_VALUE / 2);
        boolean[] vis = new boolean[n];
        dist[src] = 0;

        for (int round = 0; round < n - 1; ++round) {
            int u = -1;
            for (int i = 0; i < n; ++i) {
                if (!vis[i] && (u == -1 || dist[i] < dist[u])) {
                    u = i;
                }
            }
            vis[u] = true;
            for (int v = 0; v < n; ++v) {
                if (!vis[v] && graph[u][v] != -1) {
                    dist[v] = Math.min(dist[v], dist[u] + graph[u][v]);
                }
            }
        }
        return dist;
    }


    /**
     * 优化的 Dijkstra 算法  时间复杂度O(e*loge) 其中e为边数
     *
     * @param src   起始点
     * @param dst   目标点
     * @param graph 邻接矩阵表示的图
     * @return src到dst的最短路径权值和
     */
    public int dijkstra(int src, int dst, int[][] graph) {
        int n = graph.length;
        boolean[] vis = new boolean[n];
        PriorityQueue<Node> pq = new PriorityQueue<>(new Node());
        pq.add(new Node(src, 0));
        while (!pq.isEmpty()) {
            Node t = pq.poll();
            if (t.node == dst)
                return t.cost;
            if (!vis[t.node]) {
                vis[t.node] = true;
                for (int i = 0; i < n; i++) {
                    if (graph[t.node][i] != 0 && !vis[i]) {
                        pq.add(new Node(i, t.cost + graph[t.node][i]));
                    }
                }
            }
        }
        return -1;
    }

    class Node implements Comparator<Node> {
        int node;
        int cost;

        public Node() {
        }

        public Node(int node, int cost) {
            this.node = node;
            this.cost = cost;
        }

        @Override
        public int compare(Node node1, Node node2) {
            return node1.cost - node2.cost;
        }
    }
}
