#include <stdio.h>
#include <pthread.h>
#include <assert.h>

static volatile int counter = 0;
pthread_mutex_t     lock;

 void *
 mythread(void *arg)
 {
     int i;

     printf("%s: begin\n", (char *) arg);
     for (i = 0; i < 1e7; i++) {
	 pthread_mutex_lock(&lock);
	 counter = counter + 1;
	 pthread_mutex_unlock(&lock);
     }

     printf("%s: done\n", (char *) arg);
     return NULL;
 }

 int
 main(int argc, char *argv[])
 {
     pthread_t p1, p2;
     int       rc;

     rc = pthread_mutex_init(&lock, NULL);
     assert(rc == 0);

     printf("main: begin (counter = %d)\n", counter);
     pthread_create(&p1, NULL, mythread, "A");
     pthread_create(&p2, NULL, mythread, "B");

     // join waits for the threads to finish
     pthread_join(p1, NULL);
     pthread_join(p2, NULL);
     printf("main: done with both (counter = %d)\n", counter);
     pthread_mutex_destroy(&lock);

     return 0;
 }
