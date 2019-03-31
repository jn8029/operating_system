#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


#define MIN_PID 300
#define MAX_PID 5000
#define THREAD_NUM 1000
bool* pid_map;


int allocate_map(void){
	pid_map =  (bool*) malloc(sizeof(bool)*(MAX_PID-MIN_PID+1));
	if (pid_map==NULL){return -1;}
	return 1;
}

int allocate_pid(void){
	for (size_t i =0 ;i<MAX_PID-MIN_PID+1; i++){
		if (!pid_map[i]){
			pid_map[i]=true;
			return i+MIN_PID;
		}
	}
	return 1;
}

void release_pid(int pid){
	if (pid>=MIN_PID && pid<=MAX_PID){
		pid -= MIN_PID;
		pid_map[pid]=false;
		printf("PID %d is released\n",pid+MIN_PID);
	} else {
		printf("PID %d is out of range\n",pid);
	}
 }

void *runner(void *max_seconds){
  int tid = allocate_pid();
  int randomnumber;
  randomnumber = rand() % 10;
  if(*(int*)max_seconds < randomnumber){
    *(int*)max_seconds = randomnumber;
  }
  printf("TID %d, sleeping for %d seconds...\n", tid, randomnumber);
  sleep(randomnumber);
  release_pid(tid);
  pthread_exit(0);
}

int main(){
  srand(time(NULL));
	int allocated = allocate_map();
  pthread_t threads[THREAD_NUM];
  int max_seconds;

	if (allocated==1){
    // clock_t begin = clock();



    for (int i = 0 ; i<THREAD_NUM; i++){
      pthread_t tid; /* the thread identifier */
      threads[i] = tid;
      pthread_attr_t attr;
      pthread_attr_init(&attr);
      void *args;
      pthread_create(&tid,&attr,runner,&max_seconds); /* wait for the thread to exit */
    }

    for (int j = 0; j<THREAD_NUM;j++){
      pthread_join(threads[j], NULL);
    }
    clock_t end = clock();
    // double time_spent = (double)(end - begin);
    printf("max_thread_wait = %d\n",max_seconds);
    // printf("total program time %f\n", time_spent);
    /* here, do your time-consuming job */




	} else{
		printf("allocation failed\n");
	}
}
