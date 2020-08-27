#ifndef COLUMNSORT
#define COLUMNSORT

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "heapsort.h"

typedef struct {
  size_t start;
  size_t size;
} column_t;

typedef void column_sorter(record *, column_t *, int);

/* int check_dimensions(size_t r, size_t s); */
void columnHeapSort(record * arr, column_t * colpairs, int numcols);
void columnsort(record *A, size_t r, size_t s, column_sorter sort_columns);

#endif
