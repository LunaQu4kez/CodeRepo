#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;


// 若找到了key，返回key的下标最小的index
// 若没找到，返回大于key的最小index
int binarySearchLeBd(vector<int>& arr, int key) {
    return lower_bound(arr.begin(), arr.end(), key) - arr.begin();
}


// 若找到了key，返回key的下标最大的index
// 若没找到，返回小于key的最大index
int binarySearchRiBd(vector<int>& arr, int key) {
    return upper_bound(arr.begin(), arr.end(), key) - arr.begin() - 1;
}


int main(){
    vector<int> arr{1, 3, 9, 15, 15, 15, 19, 19, 26, 31, 33, 36, 40};
    int n = arr.size();
    int keys[] = {0, 15, 19, 32, 41};
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "length of arr: " << n << endl;
    cout << "binary search left bound" << endl;
    for (size_t i = 0; i < sizeof(keys)/sizeof(keys[0]); i++)
    {
        int key = keys[i];
        cout << "key: " << key << "  index: " << binarySearchLeBd(arr, key) << endl;
    }
    cout << "binary search right bound" << endl;
    for (size_t i = 0; i < sizeof(keys)/sizeof(keys[0]); i++)
    {
        int key = keys[i];
        cout << "key: " << key << "  index: " << binarySearchRiBd(arr, key) << endl;
    }

    return 0;
}