public class FastSlowPointer {
    public static void main(String[] args) {
        ListNode[] nodes = new ListNode[7];
        nodes[0] = new ListNode(0);
        for (int i = 1; i < nodes.length; i++) {
            nodes[i] = new ListNode(i);
            nodes[i - 1].next = nodes[i];
        }
        System.out.print("linked list: ");
        print(nodes[0]);
        System.out.println("mid: " + movePointer(nodes[0]).val);

        System.out.println();

        nodes = new ListNode[10];
        nodes[0] = new ListNode(1);
        for (int i = 1; i < nodes.length; i++) {
            nodes[i] = new ListNode(2*i + 1);
            nodes[i - 1].next = nodes[i];
        }
        System.out.print("linked list: ");
        print(nodes[0]);
        System.out.println("mid: " + movePointer(nodes[0]).val);
    }

    // node数为奇数，返回正中间的节点；node数为偶数，返回中间前一个节点
    public static ListNode movePointer(ListNode head) {
        ListNode fast = head;
        ListNode slow = head;
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }

    private static void print(ListNode head) {
        ListNode node = head;
        while (node.next != null) {
            System.out.print(node.val + " ");
            node = node.next;
        }
        System.out.println(node.val);
    }
}
