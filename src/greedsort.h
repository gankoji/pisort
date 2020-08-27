#ifndef GREEDSORT
#define GREEDSORT

#include "heapsort.h"
#include "columnsort.h"

int readMemoryLoadByBlocks(FILE * file, record * arr, const long M, const int B, const char recordSize);
int writeMemoryLoadByBlocks(FILE * file, record * arr, const int B, const char recordSize);


#endif //GREEDSORT
