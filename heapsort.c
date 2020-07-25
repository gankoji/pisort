#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], int a, int b)
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(arr, i, largest);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr, 0, i);
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n)
{
    if (n > 10) n = 10;
    for (int i = 0; i < n; ++i)
        printf("\t%d", arr[i]);
}

int main()
{
    /*int arr[] = { 5,18,4,13,10,7};
    int n = sizeof(arr) / sizeof(arr[0]);*/

    int n = 1e6;
    int * arr = malloc(n*sizeof(int));

    if (arr) 
    {
        for (int i=0; i<n; i++) {
            arr[i] = rand();
        }
        heapSort(arr, n);

        printf("Sorted array is: \n");
        printArray(arr, n);
    }
}