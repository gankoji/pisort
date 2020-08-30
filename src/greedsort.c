#include "heapsort.h"

int readMemoryLoadByBlocks(FILE * inputFile, record * arr, const long M, const int B, const char recordSize)
{
	record * temp = arr;
	long innerLoop = (M/B);
	int recordsInBlock = M;

	for (long j=0; j < innerLoop; j++)
	{
		size_t recordsRead = fread((void *)temp, recordSize, B, inputFile);

		if (recordsRead != B)
		{
			printf("reading data error.\n");
			printf("expected %d records, got %lld records.\n On loop iteration %ld\n", B, recordsRead, j);
			recordsInBlock = (j*(long)B) + (long)recordsRead;
			innerLoop = j + 1;
			break;
		}
		else
		{
			// We've read the whole block, move the pointer.
			temp += recordsRead;
		}
	}

	return recordsInBlock;
}

int writeMemoryLoadByBlocks(FILE * outputFile, record * arr, const int M, const int B, const char recordSize)
{
	record * temp = arr;
	long innerLoop = (M/B);
	int recordsInBlock = M;

	for (long j=0; j < innerLoop; j++)
	{
		/*  This code is wrong. It does not create many small temp files
		    that are sorted, i.e. it doesn't create the initial runs
		    anymore. */
		size_t recordsWritten = fwrite((void *)temp, recordSize, B, outputFile);

		if (recordsWritten != B)
		{
			recordsInBlock = (j*(long)B) + (long)recordsWritten;
			break;
		}
		else
		{
			// We've written the whole block, move the pointer.
			temp += recordsWritten*recordSize;
		}
	}

	return recordsInBlock;
}

