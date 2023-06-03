import java.util.Arrays;

public class Prefix {
    public static void main(String[] args) {
        int[] arr = new int[]{1, 0, 2, 3, 1, 2, 0, 1, 4, 2, 3};
        System.out.println("arr: " + Arrays.toString(arr));
        int[] preSum = prefixSum(arr);
        System.out.println("prefixSum: " + Arrays.toString(preSum));

        int l = 2, r = 6;
        int sum = preSum[r + 1] - preSum[l]; // 查询[l,r]区间（端点都含）的和：preSum[r + 1] - preSum[l]
        System.out.println("arr [l,r]=[2,6] sum: " + sum);
    }

    public static int[] prefixSum(int[] arr) {
        int n = arr.length;
        int[] preSum = new int[n + 1];
        for (int i = 0; i < n; i++) {
            preSum[i + 1] = preSum[i] + arr[i];
        }
        return preSum;
    }
}
