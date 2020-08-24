//#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "heapsort.h"

typedef struct {
    size_t start;
    size_t size;
} column_t;

typedef void column_sorter(record *, column_t *, int);

/*
 * Verify the dimensions of the passed array.
 */

int check_dimensions(size_t r, size_t s) {
    if (r % 2) {
        fprintf(stderr, "r must be even\n");
        return 0;
    }

    if (r % s) {
        fprintf(stderr, "s must divide r\n");
        return 0;
    }

    if (r < 2 * s * s) {
        fprintf(stderr, "r must be grater than 2s²\n");
        return 0;
    }

    return 1;
}

/**
 * The basic column sort implementation. It does a copy of the array for steps
 * 3 and 5. It also does not sort the half-columns in the beginning and the
 * end, since that is not necessary for the correctness of the algorithm.
 */

void columnsort(record *A, size_t r, size_t s, column_sorter sort_columns) {
    size_t size = r * s;
    record *copy;
    column_t *columns;

    if (!check_dimensions(r, s))
    {
        printf("Error! ColumnSort called with improper dimensions!\n");
        return;
    }

    copy = calloc(size, sizeof(record));
    columns = calloc(s, sizeof(column_t));

    for (size_t i = 0; i < s; i++) {
        columns[i] = (column_t) {i * r, r};
    }

    sort_columns(A, columns, s);

    for (size_t i = 0; i < size; i++) {
        copy[(i % s) * r + i / s] = A[i];
    }

    sort_columns(copy, columns, s);

    for (size_t i = 0; i < size; i++) {
        A[i] = copy[(i % s) * r + i / s];
    }

    sort_columns(A, columns, s);

    for (size_t i = 0; i < s - 1; i++) {
        columns[i] = (column_t) {i * r + r / 2, r};
    }

    sort_columns(A, columns, s - 1);

    free(copy);
}