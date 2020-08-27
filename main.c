#include "greedsort.h"

int main()
{
    printf("Opening Files.\n");
    FILE * inputFile, * outputFile;
    inputFile = fopen("./inputs", "r");
    outputFile = fopen("./outputs", "w");

    char filename[10];
    size_t recordSize = 100;

    long N = 1e3;
    long M = 1e9/((long)recordSize);
    size_t B = 3e5/((long)recordSize);

    long outerLoop = (N/M) + 1;
    long innerLoop = (M/B);
    long recordsInBlock = M;

    printf("Loop statistics: %ld outer loops, %ld inner loops, %ld bytes memory\n",
           outerLoop, innerLoop, recordSize*B*innerLoop);
    record * arr = malloc(recordSize*M);

    if (arr == NULL)
    {
        printf("Memory allocation failed. Exiting.");
        return -1;
    }

    for (long i=0; i< outerLoop; i++)
    {

      /*  This is a C-ism, but we can get away with reusing the inputFile
          pointer because it maintains its place in the file after a read. */
      int recordsInBlock = readMemoryLoadByBlocks(inputFile, arr, M, B, recordSize);

        /*  Run the internal sort on the memory load we've just read. */
        printf("Sorting %ld records.\n", recordsInBlock);
        heapSort(arr, recordsInBlock);
        printf("Records sorted, writing output.\n");

        /*  However, here with the output, we have to change the file that we're
            writing to (do we really?) for each run. This may not be totally
            necessary, but this way we're not calculating offsets into one large
            file. I have no idea which approach is more performant (probably the
            offsets, but it probably doesn't matter enough to bother with).  */
        int recordsWritten = writeMemoryLoadByBlocks(outputFile, arr, B, recordSize);
    }

    fclose(inputFile);
    fclose(outputFile);
    free(arr);
}
