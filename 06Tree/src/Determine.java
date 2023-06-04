import java.util.ArrayList;
import java.util.List;

public class Determine {
    public static void main(String[] args) {

    }



    // Binary Search Tree搜索二叉树：左边都比当前节点小，右边都比当前节点大
    public static boolean isBST(Node root) {
        return isBST(root, Integer.MIN_VALUE, Integer.MAX_VALUE);
    }

    private static boolean isBST(Node node, int lower, int upper) {
        if (node == null) {
            return true;
        }
        if (node.val <= lower || node.val >= upper) {
            return false;
        }
        return isBST(node.left, lower, node.val) && isBST(node.right, node.val, upper);
    }



    // Complete Binary Tree完全二叉树：一个堆，必须从左往右依次填
    public static boolean isCompleteBT(Node root) {
        List<ANode> nodes = new ArrayList<>();
        nodes.add(new ANode(root, 1));
        int i = 0;
        while (i < nodes.size()) {
            ANode anode = nodes.get(i++);
            if (anode.node != null) {
                nodes.add(new ANode(anode.node.left, anode.code * 2));
                nodes.add(new ANode(anode.node.right, anode.code * 2 + 1));
            }
        }

        return nodes.get(i - 1).code == nodes.size();
    }

    static class ANode {
        Node node;
        int code;

        ANode(Node node, int code) {
            this.node = node;
            this.code = code;
        }
    }



    // Balanced BST平衡二叉树：每个节点的左右两个子树的高度差的绝对值不超过1的二叉树
    public boolean isBalancedBT(Node root) {
        if (root == null) {
            return true;
        } else {
            return Math.abs(height(root.left) - height(root.right)) <= 1 && isBalancedBT(root.left) && isBalancedBT(root.right);
        }
    }

    private int height(Node root) {
        if (root == null) {
            return 0;
        } else {
            return Math.max(height(root.left), height(root.right)) + 1;
        }
    }



    // Full BT满二叉树：k层有2^k-1个节点
    public static boolean isFullBT(Node head) {
        if (head == null) {
            return true;
        }
        Info data = f(head);
        return data.nodes == ((1 << data.height) - 1);
    }

    private static Info f(Node x) {
        if (x == null) {
            return new Info(0, 0);
        }
        Info leftData = f(x.left);
        Info rightData = f(x.right);
        int height = Math.max(leftData.height, rightData.height) + 1;
        int nodes = leftData.nodes + rightData.nodes + 1;
        return new Info(height, nodes);
    }

    static class Info {
        int height;
        int nodes;

        public Info(int height, int nodes) {
            this.height = height;
            this.nodes = nodes;
        }
    }


}
