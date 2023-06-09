import java.util.Arrays;

/*
Leetcode2719
给你两个数字字符串 num1 和 num2 ，以及两个整数 max_sum 和 min_sum 。如果一个整数 x 满足以下条件，我们称它是一个好整数：
num1 <= x <= num2
min_sum <= digit_sum(x) <= max_sum
请你返回好整数的数目。答案可能很大，请返回答案对 1e9 + 7 取余后的结果。
注意，digit_sum(x) 表示 x 各位数字之和。
 */

class Example2 {
    private static final int MOD = (int) 1e9 + 7;
    private int minSum, maxSum;
    char[] s;
    int[][] memo;

    public int count(String num1, String num2, int minSum, int maxSum) {
        this.minSum = minSum;
        this.maxSum = maxSum;
        int ans = count(num2) - count(num1) + MOD; // 避免负数
        int sum = 0;
        for (char c : num1.toCharArray()) sum += c - '0';
        if (minSum <= sum && sum <= maxSum) ans++; // x=num1 是合法的，补回来
        return ans % MOD;
    }

    private int count(String S) {
        s = S.toCharArray();
        int n = s.length;
        memo = new int[n][Math.min(9 * n, maxSum) + 1];
        for (int i = 0; i < n; i++)
            Arrays.fill(memo[i], -1); // -1 表示没有计算过
        return f(0, 0, true);
    }

    private int f(int i, int sum, boolean isLimit) { // 这里没有用到isNum，因为前导0不影响求和
        if (sum > maxSum) // 非法数字
            return 0;
        if (i == s.length)
            return sum >= minSum ? 1 : 0;
        if (!isLimit && memo[i][sum] != -1)
            return memo[i][sum];
        int res = 0;
        int up = isLimit ? s[i] - '0' : 9;
        for (int d = 0; d <= up; ++d) // 枚举要填入的数字 d
            res = (res + f(i + 1, sum + d, isLimit && d == up)) % MOD;
        if (!isLimit)
            memo[i][sum] = res;
        return res;
    }
}
