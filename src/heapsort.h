#ifndef HEAPSORT
#define HEAPSORT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Each record is 100 bytes, with the first 10 bytes being the key. We make the
// struct 104 bytes to align each record with the word boundary on a 64-bit
// machine, for better access times and cache utilization.
typedef struct records
{
   char key[10];
   char body[90];
} record;

int myCompare(char * a, char * b);
void swap(record arr[], int a, int b);
void heapify(record arr[], int n, int i);
void heapSort(record arr[], int n);
void printArray(record arr[], int n);

#endif // HEAPSORT
