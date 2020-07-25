#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct records
{
   char key[10];
   char body[94]; 
} record;

void swap(record arr[], int a, int b)
{
    record temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

int myCompare(char * a, char * b)
{
    if (strncmp(a, b, 100) >= 0)
    {
        return 1;
    } else
    {
        return 0;
    }
    
}
void heapify(record arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && myCompare(arr[l].key, arr[largest].key))
        largest = l;
    if (r < n && myCompare(arr[r].key, arr[largest].key))
        largest = r;
    if (largest != i) {
        swap(arr, i, largest);
        heapify(arr, n, largest);
    }
}

void heapSort(record arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr, 0, i);
        heapify(arr, i, 0);
    }
}

void printArray(record arr[], int n)
{
    if (n > 10) n = 10;
    char printableKey[11];
    for (int i = 0; i < n; ++i)
    {
        // The keys are stored directly in line with the record, with no null
        // terminator. This confuses poor C. Buffer it and add one for printing. 
        memcpy(printableKey, arr[i].key, 10);
        printableKey[10] = '\0';

        printf("Key: %s\n", printableKey);
        printf("Body: %s\n", arr[i].body);
    }
}

int main()
{
    FILE * inputFile, * outputFile;
    inputFile = fopen("../inputs", "r");
    outputFile = fopen("../outputs", "w");

    char buf[105];
    char key[10];
    int n = 2e7; // number of records to be sorted.
    int rSize = 104; // number of bytes per record.

    record * arr = malloc(n*rSize);
    if (arr) 
    {       
        for (int k=0; k < n; k++) 
        {
            fgets(buf, 105, inputFile);
            memcpy(key, buf, 10);
            memcpy(arr[k].key, buf, 10);
            memcpy(arr[k].body, (buf + 10), 90);
        }

        fclose(inputFile);
        heapSort(arr, n);

        printf("Sorted array is: \n");
        printArray(arr, n);

        for (int k=0; k < n; k++)
        {
            // for (int j=0; j<10; j++)
            // {
            //     fputc(arr[k].key[j], outputFile);
            // }
            fputs(arr[k].key, outputFile);
        }
        fclose(outputFile);
    }
    
}