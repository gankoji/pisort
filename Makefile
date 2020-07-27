all: main.o heapsort.o
		gcc main.o heapsort.o -o heapsort -m64

main.o: main.c
		gcc -c main.c -m64

heapsort.o: heapsort.c 
		gcc -c heapsort.c -m64

clean:
		rm -f *.o *.exe