#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
void execute_algo(char* arg){
  char *ptr;
  unsigned long long int converted_int = strtol(arg, &ptr, 10);
  if (converted_int == 0){printf("input not pos int\n");return;}
  printf("%llu\t", converted_int);
  while (converted_int > 1){

    if (converted_int%2==0){

      converted_int /= 2;

    } else {
      converted_int = 3*converted_int +1;
    }
    printf("%llu\t", converted_int);
  }
  printf("\n");

}

int main(int argc, char* argv[]){
  pid_t pid = fork();
  if (pid == 0){
    if (argc == 2){
      execute_algo(argv[1]);
    } else {
      printf("Error:incorrect argc\n");
    }
  } else {
    int *status;
    pid_t finished_child;
    finished_child = wait(status);
    printf("%d child finished, parent exiting...\n", finished_child);

  }


}
