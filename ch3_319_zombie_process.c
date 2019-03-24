#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(){

	pid_t pid;
	pid = fork();

	if (pid<0){
		printf("%s","for failed");
	} else if (pid==0){
		printf("pid=%d %s\n",pid,"do nothing");
		return 0;
	} else{
		printf("in parent process, child process pid=%d, goign to sleep\n",pid);
		while(1){}
	}
	return 0;

}
