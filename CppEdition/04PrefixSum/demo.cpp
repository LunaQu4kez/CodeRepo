#include<bits/stdc++.h>
using namespace std;

int* prefixSum(int arr[], int n)
{
    int* preSum = new int[n + 1];
    preSum[0] = 0;
    for (int i = 0; i < n; i++) {
        preSum[i + 1] = preSum[i] + arr[i];
    }
    return preSum;
}

int main()
{
    int arr[] = {1, 0, 2, 3, 1, 2, 0, 1, 4, 2, 3};
    int l = 2, r = 6;
    int* preSum = prefixSum(arr, 11);
    int sum = preSum[r + 1] - preSum[l]; // 查询[l,r]区间（端点都含）的和：preSum[r + 1] - preSum[l]
    cout << "arr [l,r]=[2,6] sum: " << sum;

    return 0;
}