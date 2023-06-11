import java.util.Arrays;

class Demo {
    char s[];
    int memo[][];

    public int method(int n) { // 到n为止的所有种类数
        s = Integer.toString(n).toCharArray();
        int m = s.length;
        memo = new int[m][1 << 10];
        for (int i = 0; i < m; i++)
            Arrays.fill(memo[i], -1); // -1 表示没有计算过

        return f(0, 0, true, false); // toDo:返回结果，根据需要决定返回什么
        // return n - f(0, 0, true, false); 也可能返回这个
    }

    /**
     * @param i 从左往右数第 i 个数位
     * @param mark 记录需要的数值（比如当前数字是几，和是多少等）
     * @param isLimit 该位是否被限制了（比如最大值为 234 ，而首位为 2 ，则这一位只能为 0-3 ，被限制了
     *                若首位为 1 ，这一位可以为 0-9 ，没有被限制）
     * @param isNum 是不是这一位之前全是前导 0
     * @return 递归过后的答案（枚举出来的种类数）
     * toDo: isNum可以根据需求
     */
    private int f(int i, int mark, boolean isLimit, boolean isNum) {
        if (i == s.length)
            return isNum ? 1 : 0; // isNum 为 true 表示得到了一个合法数字
        if (!isLimit && isNum && memo[i][mark] != -1)
            return memo[i][mark];
        int res = 0;
        if (!isNum) // 可以跳过当前数位
            res = f(i + 1, mark, false, false);
        int up = isLimit ? s[i] - '0' : 9; // 如果前面填的数字都和 n 的一样，那么这一位至多填数字 s[i]（否则就超过 n 了）
        for (int d = isNum ? 0 : 1; d <= up; ++d) // 枚举要填入的数字 d
            // toDo: 可以加有需要的判断条件
            res += f(i + 1, mark | (1 << d), // toDo: 递归传入mark的值要根据题目的不同改变
                    isLimit && d == up, true);
        if (!isLimit && isNum)
            memo[i][mark] = res;
        return res;
    }
}