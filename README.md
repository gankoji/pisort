Hello! Welcome to the very unoriginally named PiSort project!

# What this is

PiSort is an attempt at a performant, cross-platform external sorting solution,
with the express intent to be used as part of a submission to the
[sortbenchmark.org](http://sortbenchmark.org) annual sorting competition.

The purpose of the sortbenchmark competition is to encourage developers to push
the boundaries of what is possible with modern hardware, in terms of raw speed
in sorting extremely large datasets (i.e. 100 TB, the current GraySort size)
which cannot fit in main memory of a single system, and in terms of efficiency,
as with the JouleSort category. As an interesting aside, it has been estimated
that sorting data, as a primary operation in many other aspects of computing,
actually account for approximately 20% (1/5th) of *all computer usage*. I should
include a reference for that, but I can't remember where it is, so take my word
for it. 

# Sorting Algorithms
## External Sorting

As mentioned above, the intent of this software is to be efficient at handling
*external sorting*, where the dataset to be sorted is too large to fit inside a
machine's main memory. There are a wide range of techniques to handle this type
of problem, but most of them fall under the umbrella of either *merge sorts* or
*distribution sorts*. The approach here will be of the merge sort variety, and
is based directly on the Greed Sort algorithm published by James Vitter and Mark
Nodine [1]. 

## Internal Sorting

To achieve external sorting, a routine for sorting subsequences of the main
dataset in memory is also required. The literature on this subject is extensive,
but two of the most well known, and most performant in terms of best, average,
worst-case runtime and space complexity, are Heapsort and Timsort. Having a
robust implementation of one of these algorithms is a prerequisite to tackling
the external sort problem.

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

## Disk manager, single threaded

## Sort program manager

There are tunable parameters to the GreedSort algorithm, such as block size for
disk reads and writes, as well as input/output files and disk to be used. We'll
need a comprehensive wrapper to manage all of these dials. 

## GreedSort, first cut

This is the first major milestone. In a single threaded environment, with
tunable parameters, can we get valid sort results in a time that's in line with
expectations?

## Multi-threaded disk manager

## Multi-threaded GreedSort

[1] - Nodine, Mark and Vitter, Jeffrey Scott, "Greed Sort: Optimal Deterministic
Sorting on Parallel Disks", Journal of the Association for Computing Machinery,
Vol 42, No 4, July 1995, pp. 919-933. 
