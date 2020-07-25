all: main

main: 
		gcc main.c heapsort.c -o heapsort -m64

heapsort: heapsort.c
		gcc heapsort.c -o heapsort.o -m64