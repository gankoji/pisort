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
include a reference for that, but I can't remember where it is, so you'll have to
take my word for it for now.

# Why so much code?

If you take a look at the src/ folder, you'll see that there's quite a lot of
code going on here. The original intent of this project was to implement from
scratch the GreedSort algorithm published by Nodine and Vitter in the late 90s.
While we did get most of the way there, time and resource constraints kept that
from ever getting off the ground completely. In the end, I ended up
incorporating a library with 90% of the external merge sort functionality I was
looking for already built (alveko/external_sort here on github, an excellent
piece of code and highly recommended for perusal). After that choice, it was a
simple matter of getting the right datatype defined for our specific purpose,
and tuning the runtime parameters for best performance. 

# What are the dependencies?
This project was built with GCC on MSys2/MinGW. I have tested it on a Raspberry
Pi 4 as well, running 64-bit Manjaro. Any environment where you have GCC and
its standard libraries will likely work. 

# How do I use it?
Take a look at newmain.cc. At the top of that file, the input and output files
are defined as strings. You can either modify those strings and recompile using
the makefile, or adjust the main function to take your files as arguments. 

Also consider adjusting the memory parameters to fit your particular machine.
The current parameters expect a machine with at least 10 GB free memory, so
beware if your machine doesn't have that! After getting the parameters to your
liking, simply open a terminal and run pisort.exe. 

There is a possible bug remaining, in that trying to sort files that are very
large, the program may give up part of the way through and fail silently. I have
yet to determine whether this is due to some strange limit I'm running into with
my filesystem, or there is something slightly more subtle going on in the code
itself. I have only seen this when sorting a 1 TB file, sizes smaller than that
complete just fine. 

