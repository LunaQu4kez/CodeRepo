public class ReversePairs {
    public int reversePairs(int[] arr) {
        int n = arr.length;
        if (n < 2) {
            return 0;
        }

        int[] temp = new int[n];
        return reversePairs(arr, 0, n - 1, temp);
    }

    private int reversePairs(int[] arr, int le, int ri, int[] temp) {
        if (le == ri) {
            return 0;
        }

        int mid = le + (ri - le) / 2;
        int leftPairs = reversePairs(arr, le, mid, temp);
        int rightPairs = reversePairs(arr, mid + 1, ri, temp);

        if (arr[mid] <= arr[mid + 1]) {
            return leftPairs + rightPairs;
        }

        int crossPairs = merge(arr, le, mid, ri, temp);
        return leftPairs + rightPairs + crossPairs;
    }

    private int merge(int[] arr, int le, int mid, int ri, int[] temp) {
        for (int i = le; i <= ri; i++) {
            temp[i] = arr[i];
        }

        int i = le;
        int j = mid + 1;

        int count = 0;
        for (int k = le; k <= ri; k++) {
            if (i == mid + 1) {
                arr[k] = temp[j];
                j++;
            } else if (j == ri + 1) {
                arr[k] = temp[i];
                i++;
            } else if (temp[i] <= temp[j]) {
                arr[k] = temp[i];
                i++;
            } else {
                arr[k] = temp[j];
                j++;
                count += (mid - i + 1);
            }
        }
        return count;
    }
}