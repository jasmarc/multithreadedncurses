#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX 20
#define BARRIER_SIZE 6

void *functionC();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
int row,col,barrier_start,barrier_end;

int main()
{
    initscr();
    getmaxyx(stdscr,row,col);
    barrier_start = ((row/2) - BARRIER_SIZE/2);
    barrier_end = ((row/2) + BARRIER_SIZE/2);
    int rc[MAX];
    int i;
    pthread_t threads[MAX];
    // draw the lines for the "critical region"
    for(i = 0; i < col; ++i) {
        mvaddch(barrier_start, i, '-');
        mvaddch(barrier_end, i, '-');
    }
    for(i = 0; i < MAX; ++i) // spawn threads
        rc[i]=pthread_create( &threads[i], NULL, &functionC, NULL);
    for(i = 0; i < MAX; ++i) // join them all
        pthread_join( threads[i], NULL);
    
    getch();
    endwin();
    return 0;
}

void *functionC()
{
    srand(time(NULL));
    sleep(1);
    int i;
    int j = rand() % col;                                       // pick a random column
    for(i = 0; i < row; ++i) {                                  // advance the square to the bottom of the screen
        if(i == barrier_start) pthread_mutex_lock( &mutex1 );   // grab mutex for critical region
        if(i == barrier_end) pthread_mutex_unlock( &mutex1 );   // release for critical region
        pthread_mutex_lock( &mutex2 );                          // grab mutex for drawing
        if(i > 0) {                                             // erase previous spot
            if(i == barrier_end + 1 || i == barrier_start + 1)
                mvprintw(i - 1, j, "-");
            else
                mvprintw(i - 1, j, " ");
        }
        mvprintw(i, j, "#");                                    // draw square
        refresh();
        pthread_mutex_unlock( &mutex2 );                        // release mutex for drawing
        sleep(rand() % 5);                                      // sleep a random amount of time to spread the threads out a little
    }
}
