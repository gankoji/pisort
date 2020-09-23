# Roadmap (Approximate)

## Infrastructure Setup (Done)

This project will be written in C, based on the gcc compiler (due to its
excellent optimization capacity and capability to target ARM processors). The
sortbenchmark.org contest provides utilities for generating random data to be
sorted (which is required to be used for submissions), called gensort, as well
as a utility to validate the checksum of both input and output datafiles, called
valsort. These will be linked here for testing the project as development
progresses.

## Internal Sort Implementation (Done)

We've gone with Heapsort as the default internal sort algorithm for now. There's
always a possibility of coming back to this decision in the future, and moving
to something that has a little better performance, but I just don't see the need
for it right now since our primary bottleneck is *not* going to be the CPU or
the RAM here.

## Disk manager, single threaded (Done)

This is the fun part. We're going to be dealing with massive files, much too big
to fit into main system memory, so we'll need a coherent strategy to deal with
files starting on disk, temp files written back out to clear up memory, and the
final sorted file being written to disk. While the first cut can be simple and
sequential, the need for parellelism for speed necessitates a good
architecture/clean design here.

## Sort program manager (Done)

There are tunable parameters to the GreedSort algorithm, such as block size for
disk reads and writes, as well as input/output files and disk to be used. We'll
need a comprehensive wrapper to manage all of these dials.

## GreedSort, first cut (Done, ish)

This is the first major milestone. In a single threaded environment, with
tunable parameters, can we get valid sort results in a time that's in line with
expectations?

(20200819 Update) We've progressed to the point where the next item on the
agenda is to implement the entirety of the greedsort algorithm. We have
capabilities in place to create initial runs of a specified memory load size and
write them back to disk. The key remaining piece of the algorithm is now to
merge those initial runs until only one remains, and handling the disks to make
that a possibility. One thing needed to accomplish this, according to Nodine and
Vitter's original specification, is an implementation of Leighton's columnsort
algorithm, which will be included here in the next commit. This is used after
the initial greedsort merge is run, to 'clean up' the approximately sorted list
that this phase produces.

## ColumnSort (Done)
(20200826 Update) After today's commits, we've managed to implement a working
version of the columnsort algorithm, which reuses some of our previous work (the
heapsort implementation) as the subordinate sorting algorithm. Funny, how all of
these different sorting techniques require an 'actual sorting implementation'
under the hood...

## Unit Tests! Sort of ... (Done)
Also of note, unit testing functionality has been added to cover the columnsort
implementation, and can be called directly from make! Simply run 'make test' to
compile the unit test bench and see the results. At the moment, the tests are
pretty trivial, but I thought it was a good time to get the basics setup for
future use.

## Refactoring Time! (Already?) (Also, Done)
Next up will be a slight refactor of main, mostly to break out the initial loop
of greedsort to its own function. I think the final intent is to have greedSort
be a fuction, who's body simply calls out to a handful of helpers, like
columnSort. Additionally, we'll refactor the makefile to place build artifacts
into their own folder, and the final binary outputs to yet another one. This
should help keep the development space clear. 

## GreedSort, cut 2 (In Progress)

Now that we've spent some serious time and effort understanding the inner
workings of this algorithm, including implementing the minor pieces needed to
build it up (like heapsort, columnsort, and the initial run creation), as well
as refactored the code to make it much easier to understand the pieces and how
they fit together, it's time to take another crack at getting the merge phase
down in code. That's the goal for this week/weekend (28-30 Aug). 

## Profiling

I thoroughly expect that this project will need to be adjusted, tweaked, and
tuned over the course of development to take advantage of the specific hardware
we have on hand. We'll need to be able to accurately measure performance of the
overall system, as well as key subsytems, to search for bottlenecks and optimize
them accordingly.

Also, a convenient build system is probably necessary. Makefiles should suffice
for a program this small, but ideally the system could invoke
profiling/measurement as well for convenience.

## Multi-threaded disk manager

The most important aspect of this part of the project is making sure we saturate
the IO bus as thoroughly as possible. Any time spent idle is wasted, when IO is
the bottleneck.

## Multi-threaded GreedSort

[1] - Nodine, Mark and Vitter, Jeffrey Scott, "Greed Sort: Optimal Deterministic
Sorting on Parallel Disks", Journal of the Association for Computing Machinery,
Vol 42, No 4, July 1995, pp. 919-933.
