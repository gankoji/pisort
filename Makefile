# This makefile is borderline spaghetti code/unmaintainable. It works for now,
# with the mere 6 or 7 source files we have at the moment. If we were to
# significantly expand that number, loops would need to be integrated, or even a
# move to automake would be justified. However, at the moment, this is passable,
# and has the desired effect of keeping the code organized and the working
# directory clear of build artifacts.

CC = gcc
LD = gcc
CFLAGS = -Wall -Wpedantic -m64

TARGET = pisort.exe

SOURCEDIR = ./src
BUILDDIR = ./build
SOURCES = $(wildcard $(SOURCEDIR)/*.c)
OBJS = $(notdir $(SOURCES:.c=.o))
OBJECTS = $(addprefix $(BUILDDIR)/, $(OBJS))

TESTTGT = pisorttest.exe
TESTDIR = ./test
TESTSRC = $(wildcard $(TESTDIR)/*.c)
TESTO = $(notdir $(TESTSRC:.c=.o))
TESTOBJS = $(addprefix $(BUILDDIR)/, $(TESTO))

.PHONY: all

all: format $(OBJECTS)
		$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS)

$(BUILDDIR)/main.o: $(SOURCEDIR)/main.c
		$(CC) -c $(SOURCEDIR)/main.c -o $(BUILDDIR)/main.o $(CFLAGS)

$(BUILDDIR)/heapsort.o: $(SOURCEDIR)/heapsort.c
		$(CC) -c $(SOURCEDIR)/heapsort.c -o $(BUILDDIR)/heapsort.o $(CFLAGS)

$(BUILDDIR)/columnsort.o: $(SOURCEDIR)/columnsort.c
		$(CC) -c $(SOURCEDIR)/columnsort.c -o $(BUILDDIR)/columnsort.o $(CFLAGS)

$(BUILDDIR)/greedsort.o: $(SOURCEDIR)/greedsort.c
		$(CC) -c $(SOURCEDIR)/greedsort.c -o $(BUILDDIR)/greedsort.o $(CFLAGS)

test: $(TESTOBJS) $(OBJECTS)
		$(CC) $(TESTOBJS) $(BUILDDIR)/heapsort.o $(BUILDDIR)/columnsort.o -o $(TESTTGT) $(CFLAGS)
		./piSortTest.exe

$(BUILDDIR)/testMain.o: $(TESTDIR)/testMain.c
		$(CC) -c $(TESTDIR)/testMain.c -o $(BUILDDIR)/testMain.o $(CFLAGS)

$(BUILDDIR)/columnsorttest.o: $(TESTDIR)/columnSortTest.c
		$(CC) -c $(TESTDIR)/columnSortTest.c -o $(BUILDDIR)/columnsorttest.o $(CFLAGS)

format:
		astyle --indent=tab --style=allman $(SOURCEDIR)/*.c $(TESTDIR)/*.c $(SOURCEDIR)/*.h $(TESTDIR)/*.h
clean:
		rm -f $(TARGET) $(BUILDDIR)/*.o
