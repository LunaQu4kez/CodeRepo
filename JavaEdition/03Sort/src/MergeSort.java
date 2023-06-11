public class MergeSort {
    public static int[] mergeSort(int[] arr, int l, int h) {
        if (l == h) return new int[]{arr[l]};

        int mid = l + (h - l) / 2;
        int[] leArr = mergeSort(arr, l, mid);
        int[] riArr = mergeSort(arr, mid + 1, h);
        int[] newArr = new int[leArr.length + riArr.length];

        int m = 0, i = 0, j = 0;
        while (i < leArr.length && j < riArr.length) {
            newArr[m++] = leArr[i] <= riArr[j] ? leArr[i++] : riArr[j++];
        }
        while (i < leArr.length) newArr[m++] = leArr[i++];
        while (j < riArr.length) newArr[m++] = riArr[j++];
        return newArr;
    }

    public static void main(String[] args) {
        int[] nums = new int[]{9, 8, 7, 6, 5, 4, 3, 2, 10};
        int[] newNums = mergeSort(nums, 0, nums.length - 1);
        for (int x : newNums) {
            System.out.println(x);
        }
    }
}