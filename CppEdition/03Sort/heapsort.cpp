#include<bits/stdc++.h>
using namespace std;

void swap(int &a, int &b) 
{
	int temp = a;
	a = b;
	b = temp;
}

void heapify(int arr[], int n, int i) {
	if (i >= n) return;
	int largest = i;
	int lson = i * 2 + 1;
	int rson = i * 2 + 2;
	if (lson < n && arr[largest] < arr[lson]) largest = lson;
	if (rson < n && arr[largest] < arr[rson]) largest = rson;
	if (largest != i) 
    {
		swap(arr[largest], arr[i]);
		heapify(arr, n, largest);
	}
 
}
void heap_sort(int arr[], int n) {
	int lastNode = n - 1;
	int parent = (lastNode - 1) / 2;
	for (int i = parent; i >= 0; i--)
    {
		heapify(arr, n, i);
	}
	for (int i = n - 1; i >= 0; i--)
    {
		swap(arr[i], arr[0]);
		heapify(arr, i, 0);
	}
}
int main() {
	int arr[] = {6, 5, 8, 4, 5, 6, 2, 7, 8, 3, 1, 2, 5};
	heap_sort(arr, sizeof(arr) / sizeof(arr[0]));
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) 
    {
		cout << arr[i] << " ";
	}
 
	return 0;
}
