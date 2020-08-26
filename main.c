#include "heapsort.h"

// My python analysis of the time bounds, disk speed and energy usage for this
// particular scenario shows that a block size of 3e5 bytes is optimal. That
// analysis, however, is ignoring creation of temporary files, so it might be
// optimistic and misleading. Let's work on chunking anyway. 

int main()
{
    printf("Opening Files.\n");
    FILE * inputFile, * outputFile;
    inputFile = fopen("./inputs", "r");
    outputFile = fopen("./outputs", "w");

    int b = 1e3; // number of records per block to read/sort
    int rSize = 100; // number of bytes per record.
    int k = 0, i = 0; // block counters

    char filename[10];
    char buf[105];
    char key[10];
    size_t recordSize = 104;
    size_t count = 5e7;

    long N = count;
    long M = 1e9/((long)recordSize);
    size_t B = 3e5/((long)recordSize);

    long loop1Times = (N/M) + 1;
    long innerLoop = (M/B);
    long recordsInBlock = M;

    printf("Loop statistics: %ld outer loops, %ld inner loops, %ld bytes memory\n", 
            loop1Times, innerLoop, recordSize*B*innerLoop);
    record * arr = malloc(recordSize*M);
    
    if (arr != NULL) 
    {
        //printf("Inside processing.\n");
        for (long i=0; i< loop1Times; i++)
        {
            record * temp = arr;
            long j=0;
            for ( j=0; j < innerLoop; j++)
            {
                //printf("%dth memory load, %dth block.\n", i, j);
                size_t recordsRead = fread((void *)temp, recordSize, B, inputFile);
                //printf("%ld records read.\n", recordsRead);
                if (recordsRead != B)
                {
                    printf("reading data error.\n");
                    printf("expected %d records, got %d records.\n On loop iteration %d\n", B, recordsRead, j);
                    recordsInBlock = (j*(long)B) + (long)recordsRead;
                    innerLoop = j + 1;
                    break;
                } else {
                    // We've read the whole block, move the pointer.
                    temp += recordsRead;
                }
            }

            printf("Sorting %ld records.\n", recordsInBlock);
            heapSort(arr, recordsInBlock);

            temp = arr;
            j=0;
            printf("Records sorted, writing output.\n");
            for ( j=0; j < innerLoop; j++)
            {
                
                size_t recordsWritten = fwrite((void *)arr, recordSize, B, outputFile);
                if (recordsWritten != B)
                {
                    printf("writing data error.\n");
                    printf("expected %d records, got %d records.\n", recordSize*count, recordsWritten);
                    break;
                } else {
                    // We've read the whole block, move the pointer.
                    temp += recordsWritten*recordSize;
                }
            }

        }
    } else {
        printf("Memory allocation failed.\n");
    }
    // if (arr) 
    // {       
    //     while( fgets(buf, rSize, inputFile) )
    //     {
    //         // Copy the record
    //         memcpy(arr[k].key, buf, 10);
    //         memcpy(arr[k].body, (buf + 10), 90);

    //         k += 1;
    //         if (k >= b)
    //         {
    //             // We've read a full block, process it
    //             heapSort(arr, b);
    //             sprintf(filename, "output%d", i);
    //             FILE * tempFile = fopen(filename, "w");

    //             for (int j=0; j < b; j++)
    //             {
    //                 fputs(arr[j].key, tempFile);
    //             }

    //             fclose(tempFile);
    //             printf("Wrote output file %s\n", filename);
    //             k = 0;
    //             i += 1;
    //         }
    //     }
    // }
    
    // if (k != 0)
    // {
    //     // We have one final block that wasn't written
    //     heapSort(arr, k);
    //     sprintf(filename, "output%d", i);
    //     FILE * tempFile = fopen(filename, "w");
        
    //     //printArray(arr, 10);
    //     for (int j=0; j < k; j++)
    //     {
    //         fputs(arr[j].key, tempFile);
    //     }

    //     fclose(tempFile);
    //     printf("Wrote output file %s\n", filename);
    // }

    fclose(inputFile);
    fclose(outputFile);
    free(arr);
}
