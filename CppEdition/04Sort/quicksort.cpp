#include<bits/stdc++.h>
using namespace std;

void quick_sort(int a[], int l, int r)
{
    if (l < r)
    {     
        int i = l, j = r, x = a[l];
        while (i < j)
        {
            while(i < j && a[j] >= x)
                j--; 
            if(i < j)
                a[i++] = a[j];
            while(i < j && a[i] < x)
                i++; 
            if(i < j)
                a[j--] = a[i];
        }
        a[i] = x;
        quick_sort(a, l, i - 1);
        quick_sort(a, i + 1, r);
    }
}

int main()
{
    int a[6] = {2, 16, 8, 10, 9, 5};
    quick_sort(a, 0, 6-1);
    for (int i = 0; i < 6; i++)
    {
        cout << a[i] << " ";
    }
    
    return 0;
}