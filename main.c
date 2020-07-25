#include "heapsort.h"

int main()
{
    FILE * inputFile, * outputFile;
    inputFile = fopen("./inputs", "r");
    outputFile = fopen("./outputs", "w");
    
    char buf[105];
    char key[10];
    int64_t n = 2e8; // number of records to be sorted.
    int rSize = 104; // number of bytes per record.

    int64_t result = n*rSize;
    printf("Memory needed: %ld\n", result);
    result = result/1e9;
    printf("Memory in GB: %ld\n", result);

    record * arr = calloc(1, n*rSize);
    if (arr) 
    {       
        for (int64_t k=0; k < n; k++) 
        {
            fgets(buf, 105, inputFile);
            memcpy(key, buf, 10);
            memcpy(arr[k].key, buf, 10);
            memcpy(arr[k].body, (buf + 10), 90);
        }

        heapSort(arr, n);

        printf("Sorted array is: \n");
        printArray(arr, n);

        for (int64_t k=0; k < n; k++)
        {
            fputs(arr[k].key, outputFile);
        }
        
    }
    
    fclose(inputFile);
    fclose(outputFile);
}