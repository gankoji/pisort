// My python analysis of the time bounds, disk speed and energy usage for this
// particular scenario shows that a block size of 3e5 bytes is optimal. That
// analysis, however, is ignoring creation of temporary files, so it might be
// optimistic and misleading. Let's work on chunking anyway.


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

