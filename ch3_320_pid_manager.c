#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MIN_PID 300
#define MAX_PID 5000

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
		pid -= 300;
		pid_map[pid]=false;
		printf("PID %d is released\n",pid+300);
	} else {
		printf("PID %d is out of range\n",pid);
	}
 }
int main(){
	int allocated = allocate_map();
	if (allocated==1){
		for (int i =0 ; i < 4705; i++){
			allocated = allocate_pid();
			printf("allocated pid is %d\n",allocated);
		}
		for (int i=250; i<350; i++){
			release_pid(i);
		}

		for (int i = 0; i < 10; i++){
			allocated = allocate_pid();
			printf("allocated pid is %d\n",allocated);
		}

	} else{
		printf("allocation failed\n");
	}
}
