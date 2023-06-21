#include<bits/stdc++.h>
using namespace std;

void merge(int arr[], int le, int mid, int ri, int temp[]) {
	int i = le, j = mid + 1;
	int p = 0;
	while (i <= mid && j <= ri) 
    {
		if (arr[i] > arr[j]) 
        {
			temp[p] = arr[j];
			p++;
			j++;
		}
		else 
        {
			temp[p] = arr[i];
			p++;
			i++;
		}
	}
	while (i <= mid)
    {
		temp[p] = arr[i];
		p++;
		i++;
	}
	while (j <= ri)
    {
		temp[p] = arr[j];
		p++;
		j++;
	}
	int n = ri - le + 1;
	for (int i = 0; i < n; i++) arr[le + i] = temp[i];
}
 
void merge_sort(int arr[], int le, int ri,int temp[]) {
	if (le < ri) 
    {
		int mid = le + (ri - le) / 2;
		merge_sort(arr, le, mid, temp);
		merge_sort(arr, mid + 1, ri, temp);
		merge(arr, le, mid, ri, temp);
	}
}
 
int main() {
	int temp[100];
	int a[] = { 2,1,3,5,6,8,7,4,10,5,3,21,1,2,2,2,8 };
	merge_sort(a, 0, 16, temp);
	for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
		cout << a[i] << " ";
	}
	
	return 0;
}