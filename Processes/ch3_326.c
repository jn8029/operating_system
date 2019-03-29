#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024

int main(){
  int fd[2];
  int fd_2[2];
  if (pipe(fd)==-1){
    printf("Pipe failed\n");
    return 1;
  }
  if (pipe(fd_2)==-1){
    printf("Pipe failed\n");
    return 1;
  }

  pid_t pid = fork();
  if (pid<0){
    printf("Error: Fork failed");
    return 1;
  } else if (pid == 0){
  /*child process*/
    char *read_message;
    read_message = (char*)malloc(BUFFER_SIZE);
    close(fd[1]); /*close write end*/
    close(fd_2[0]);
    read(fd[0], read_message, BUFFER_SIZE);
    int changed;
    char changed_char;
    char *new_message;
    new_message = (char*)malloc(BUFFER_SIZE);
    printf("received message in child process is %s\n",read_message);
    for (size_t i =0 ; i < strlen(read_message); i++){
      if ((int)read_message[i]<=90 && (int)read_message[i]>=65){
        changed = (int)read_message[i] + 32;
        changed_char = (char)changed;
      } else if ((int)read_message[i]<=122 && (int)read_message[i]>=97){
        changed = (int)read_message[i] -32;
        changed_char = (char)changed;
      } else {
        changed_char = read_message[i];
      }
      new_message[i] = changed_char;
    }
    printf("sent message from child process is %s\n",new_message);
    write(fd_2[1],new_message,BUFFER_SIZE);
    close(fd_2[1]);
    return 0;


  } else {
    char *message = "HELLO WORLD";
    printf("sent message from parent process is %s\n",message);
    close(fd[0]);/*close read end*/
    close(fd_2[1]);
    write(fd[1], message, strlen(message)+1);
    close(fd[1]);
    pid_t finished = wait(NULL);
    char *returned_message;
    returned_message = (char*)malloc(BUFFER_SIZE);
    read(fd_2[0], returned_message, BUFFER_SIZE);
    printf("retuned message in parent process is %s\n",returned_message);

  }



}
