import java.util.HashSet;

public class Cycle {
    public static void main(String[] args) {
        ListNode n1 = new ListNode(1);
        ListNode n2 = new ListNode(2);
        ListNode n3 = new ListNode(3);
        ListNode n4 = new ListNode(4);
        ListNode n5 = new ListNode(5);
        ListNode n6 = new ListNode(6);
        n1.next = n2;
        n2.next = n3;
        n3.next = n4;
        n4.next = n5;
        n5.next = n6;
        System.out.println(cycleBegin(n1));

        n6.next = n3;
        System.out.println(cycleBegin(n1).val);
    }

    public static ListNode cycleBegin(ListNode head){
        ListNode temp = head;
        HashSet<ListNode> set = new HashSet<>();
        set.add(temp);
        while (temp.next != null) {
            temp = temp.next;
            if (set.contains(temp)) return temp;
            set.add(temp);
        }
        return null;
    }
}
