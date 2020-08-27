all: main.o heapsort.o columnsort.o greedsort.o
		gcc main.o heapsort.o columnsort.o greedsort.o -o pisort -m64

test: testMain.o heapsort.o columnsort.o columnsorttest.o
		gcc testMain.o heapsort.o columnsort.o columnsorttest.o -o piSortTest -m64
		./piSortTest.exe

testMain.o: testMain.c
		gcc -c testMain.c -m64

columnSortTest.o: columnsorttest.c
		gcc -c columnsorttest.c -m64

main.o: main.c
		gcc -c main.c -m64

heapsort.o: heapsort.c
		gcc -c heapsort.c -m64

columnsort.o: columnsort.c
		gcc -c columnsort.c -m64

greedsort.o: greedsort.c
		gcc -c greedsort.c -m64

clean:
		rm -f *.o *.exe
