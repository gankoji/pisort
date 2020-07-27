#include "heapsort.h"

// My python analysis of the time bounds, disk speed and energy usage for this
// particular scenario shows that a block size of 3e5 bytes is optimal. That
// analysis, however, is ignoring creation of temporary files, so it might be
// optimistic and misleading. Let's work on chunking anyway. 

int main()
{
    FILE * inputFile, * outputFile;
    inputFile = fopen("./inputs", "r");
    outputFile = fopen("./outputs", "w");
    
    int b = 1e5; // number of records per block to read/sort
    int rSize = 104; // number of bytes per record.
    int k = 0, i = 0; // block counters
    
    char filename[10];
    char buf[105];
    char key[10];

    int64_t result = b*rSize;
    printf("Memory needed: %ld\n", result);
   
    record * arr = calloc(1, result);
    if (arr) 
    {       
        while( fgets(buf, rSize, inputFile) )
        {
            // Copy the record
            memcpy(arr[k].key, buf, 10);
            memcpy(arr[k].body, (buf + 10), 90);

            k += 1;
            if (k >= b)
            {
                // We've read a full block, process it
                heapSort(arr, b);
                sprintf(filename, "output%d", i);
                FILE * tempFile = fopen(filename, "w");

                for (int j=0; j < b; j++)
                {
                    fputs(arr[j].key, tempFile);
                }

                fclose(tempFile);
                printf("Wrote output file %s\n", filename);
                k = 0;
                i += 1;
            }
        }
    }
    
    if (k != 0)
    {
        // We have one final block that wasn't written
        heapSort(arr, b);
        sprintf(filename, "output%d", i);
        FILE * tempFile = fopen(filename, "w");
               
        for (int j=0; j < k; j++)
        {
            fputs(arr[j].key, tempFile);
        }

        printf("Wrote output file %s\n", filename);
    }

    fclose(inputFile);
    fclose(outputFile);
}