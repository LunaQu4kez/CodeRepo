import java.util.Arrays;

public class BinarySearch {
    public static void main(String[] args) {
        int[] arr = new int[]{1, 3, 9, 15, 15, 15, 19, 19, 26, 31, 33, 36, 40};
        int n = arr.length;
        int[] keys = new int[]{0, 15, 19, 32, 41};
        System.out.println(Arrays.toString(arr));
        System.out.println("length of arr: " + n);
        System.out.println("binary search left bound");
        for (int key : keys) {
            System.out.println("key: " + key + "  index: " + binarySearchLeBd(arr, key, 0, n));
        }
        System.out.println("binary search right bound");
        for (int key : keys) {
            System.out.println("key: " + key + "  index: " + binarySearchRiBd(arr, key, 0, n));
        }
    }

    // 标准二分查找
    // key：待寻找的值  lo：左边界（包含）  hi：右边界（不包含）
    public static int binarySearch(int[] arr, int key, int lo, int hi) {
        int le = lo;
        int ri = hi - 1;
        while (le <= ri) {
            int mid = (le + ri) >> 1; // 防止溢出
            if (arr[mid] == key) {
                return mid;
            } else if (arr[mid] < key) {
                le = mid + 1;
            } else {
                ri = mid - 1;
            }
        }
        return -1; // 若没有，则返回-1
    }

    // 若找到了key，返回key的下标最小的index
    // 若没找到，返回大于key的最小index
    public static int binarySearchLeBd(int[] arr, int key, int lo, int hi) {
        int le = lo;
        int ri = hi; // 注意
        while (le < ri) { // 注意
            int mid = (le + ri) >> 1;
            if (arr[mid] == key) {
                ri = mid;
            } else if (arr[mid] < key) {
                le = mid + 1;
            } else {
                ri = mid; // 注意
            }
        }
        return le;
    }

    // 若找到了key，返回key的下标最大的index
    // 若没找到，返回小于key的最大index
    public static int binarySearchRiBd(int[] arr, int key, int lo, int hi) {
        int le = lo;
        int ri = hi;
        while (le < ri) {
            int mid = (le + ri) >> 1;
            if (arr[mid] == key) {
                le = mid + 1; // 注意
            } else if (arr[mid] < key) {
                le = mid + 1;
            } else if (arr[mid] > key) {
                ri = mid;
            }
        }
        return le - 1; // 注意
    }
}
