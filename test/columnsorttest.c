#include "columnsorttest.h"
#include <stdio.h>

#define ARRAYSIZE 20
#define COLS 2
#define ROWS 10

char failed = 0;

void testColumnSort()
{
    /*  Create an array of records to be sorted. */
    record testArray[ARRAYSIZE];

    for (int i=0; i<ARRAYSIZE; i++)
    {
        /*  Create a reverse sorted array */
        testArray[i].key[0] = ARRAYSIZE - i;
    }

    /*  Call columnsort on that array */
    columnsort(testArray, ROWS, COLS, columnHeapSort);

    /*  Check that it is actually sorted! */
    for (int i=0; i<(ARRAYSIZE - 1); i++)
    {
        if (strcmp(testArray[i].key, testArray[i+1].key) > 0)
        {
            printf("ColumnSort Failure, array is not sorted.\n");
            failed = 1;
            break;
        }
    }

    if (failed == 0)
    {
        printf("ColumnSort Testing Successful.\n");
    }
}
