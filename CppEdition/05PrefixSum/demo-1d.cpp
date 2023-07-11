#include<bits/stdc++.h>
using namespace std;

int* prefixSum1d(int* arr, int n)
{
    int* preSum = new int[n + 1];
    preSum[0] = 0;
    for (int i = 1; i <= n; i++) {
        preSum[i] = preSum[i - 1] + arr[i];
    }
    return preSum;
}

int main()
{
    int arr[] = {-10000, 1, 0, 2, 3, 1, 2, 0, 1, 4, 2, 3}; // 下标 1 到 n 为有效下标
    int l = 2, r = 9;
    int* preSum = prefixSum1d(arr, 11);
    int sum = preSum[r] - preSum[l - 1]; // 查询[l,r]区间（端点都含）的和 （1 ≤ l ≤ r ≤ n）
    cout << "arr [l,r]=[2,9] sum: " << sum;

    return 0;
}