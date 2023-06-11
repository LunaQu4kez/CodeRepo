// 求后继节点（在线索化二叉树的后一个节点）
public class SuccessorNode {
    public static Node getSuccessorNode(Node node) {
        if (node == null) return node;
        if (node.right != null) {
            return getLeftMost(node.right);
        } else {
            Node parent = node.parent;
            while (parent != null && parent.left != node) {
                node = parent;
                parent = node.parent;
            }
            return parent;
        }
    }

    private static Node getLeftMost(Node node) {
        if (node == null) return node;
        while (node.left != null) node = node.left;
        return node;
    }

    public static class Node {
        int val;
        Node left;
        Node right;
        Node parent;

        public Node(int val) {
            this.val = val;
        }
    }
}
