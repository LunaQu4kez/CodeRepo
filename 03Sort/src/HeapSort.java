import java.util.Arrays;

public class HeapSort {
    public static void main(String[] args) {
        int[] arr = new int[]{6, 5, 8, 4, 5, 6, 2, 7, 8, 3, 1, 2, 5};
        sort(arr);
        System.out.println(Arrays.toString(arr));
    }

    public static void sort(int[] pq) {
        int n = pq.length;

        for (int k = n / 2; k >= 1; k--)
            sink(pq, k, n);

        int k = n;
        while (k > 1) {
            swap(pq, 1, k--);
            sink(pq, 1, k);
        }
    }

    private static void sink(int[] pq, int k, int n) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && less(pq, j, j+1)) j++;
            if (!less(pq, k, j)) break;
            swap(pq, k, j);
            k = j;
        }
    }

    private static boolean less(int[] pq, int i, int j) {
        return pq[i-1] < pq[j-1];
    }

    private static void swap(int[] pq, int i, int j) {
        int temp = pq[i - 1];
        pq[i - 1] = pq[j - 1];
        pq[j - 1] = temp;
    }
}