#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS     5

void *PrintHello(void *threadid)
{
	long tid;
	tid = (long)threadid;
	sleep(2);
	printf("Hello World! It's me, thread #%ld!\n", tid);
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc;
	long t = 0;
	long ts[NUM_THREADS];
	for(t=0; t<NUM_THREADS; t++) {
		printf("In main: creating thread %ld\n", t);
		ts[t] = t*10;
		rc = pthread_create(&threads[t], NULL, PrintHello, (void*)ts[t]);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
  
	for(t=0; t<NUM_THREADS; t++) {
		pthread_join(threads[t], NULL);
	}
	/* Last thing that main() should do */
	// pthread_exit(NULL);
}
