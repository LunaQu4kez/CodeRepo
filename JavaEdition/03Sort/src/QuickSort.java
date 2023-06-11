import java.util.Arrays;

public class QuickSort {
    public static void main(String[] args) {
        int[] arr = new int[]{6, 5, 8, 4, 5, 6, 2, 7, 8, 3, 1, 2, 5};
        sort(arr);
        System.out.println(Arrays.toString(arr));
    }

    public static void sort(int[] a) {
        sort(a, 0, a.length - 1);
    }

    private static void sort(int[] a, int lo, int hi) {
        if (hi <= lo) return;
        int le = lo, ri = hi;
        int i = lo + 1;
        while (i <= ri) {
            int cmp = a[i] - a[lo];
            if      (cmp < 0) swap(a, le++, i++);
            else if (cmp > 0) swap(a, i, ri--);
            else              i++;
        }

        // a[lo..le-1] < v = a[le..ri] < a[ri+1..hi].
        sort(a, lo, le-1);
        sort(a, ri+1, hi);
    }

    private static void swap(int[] a, int i, int j) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}