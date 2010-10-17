# multithreaded ncurses
#### An exercise in resource allocation, thread synchronization, semaphores and mutexes -- with animation!

Compile with
    make clean && make
Run as
    ./nc

This project was done as an assignment for [CSC4320 Operating Systems](http://www.cs.gsu.edu/~skarmakar/csc4320_teaching.html) at [Georgia State University](http://www.cs.gsu.edu/). I used the [GNU ncurses](http://www.gnu.org/software/ncurses/) for animation.

Here we spawn 20 threads and let them pick random columns. Then we have little squares marching down the screen. There is, however, a mutual exclusion zone! Only one thread at a time is allowed in here.