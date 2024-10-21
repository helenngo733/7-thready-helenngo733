#include "thready.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void random_sleep() {
    int sleep_time = rand() % 8 + 1;
    sleep(sleep_time);
}

void* thread_func1(void* arg) {
    int* ix = (int*)arg;
    fprintf(stderr, "Thread %d (%ld) beginning\n", *ix, pthread_self());
    random_sleep();
    fprintf(stderr, "Thread %d (%ld) exiting\n", *ix, pthread_self());
    return NULL;
}

void pattern_1(int num_of_things) {
    pthread_t threads[num_of_things]; //array
    int thread_args[num_of_things]; //static array

    for (int ix = 0; ix < num_of_things; ix++) {
        thread_args[ix] = ix + 1; //filling the array
        pthread_create(&threads[ix], NULL, thread_func1, &thread_args[ix]);
    }

    for (int ix = 0; ix < num_of_things; ix++) {
        pthread_join(threads[ix], NULL);
    }
    fprintf(stderr, "\n");
}

void* thread_func2(void* arg) {
    int* args = (int*)arg;
    int ix = args[0];
    int total_things = args[1];

    fprintf(stderr, "Thread %d (%ld) beginning\n", ix, pthread_self());
    random_sleep();

    if (ix < total_things) {
        pthread_t child_thread;
        int next_args[2]; //static array
        next_args[0] = ix + 1; //filling the array
        next_args[1] = total_things;

        fprintf(stderr, "Thread %d (%ld) creating thread %d\n", ix, pthread_self(), ix + 1);
        pthread_create(&child_thread, NULL, thread_func2, next_args);
        pthread_join(child_thread, NULL);
    }

    fprintf(stderr, "Thread %d (%ld) exiting\n", ix, pthread_self());
    return NULL;
}

void pattern_2(int num_of_things) {
    int args[2]; //static array
    args[0] = 1; //filling the array
    args[1] = num_of_things;
    thread_func2(args);
    fprintf(stderr, "\n");
}
