#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80

int main(void){
  char *args[MAX_LINE];
  char *history_commands[MAX_LINE];
  int should_run = 1;
  int history_counter= 0;
  while (should_run){

    printf("osh>");
    fflush(stdout);
    char *command;
    command = (char*)malloc(sizeof(char)*MAX_LINE);
    fgets(command,MAX_LINE, stdin);
    printf("received command %s\n",command);
    history_commands[history_counter%MAX_LINE] = command;
    history_counter++;
    char *history = "history\n";
    char *quit = "quit\n";
    if (strcmp(command,history)==0){
      for (size_t i =0; i<history_counter; i++){
        printf("%zu %s",i, history_commands[i]);
      }
      continue;
    } else if (strcmp(command,quit)==0){
      break;
    }


    char arg[MAX_LINE];
    size_t command_char_counter = 0;
    for(size_t j = 0; j < MAX_LINE; j++){
      char* comm_arg;
      comm_arg = (char*)malloc(sizeof(char)*MAX_LINE);
      size_t i = 0;
      for(; command[command_char_counter] != ' ' && command[command_char_counter]!='\0' && command[command_char_counter]!='\n'; command_char_counter++,i++){
        comm_arg[i] = command[command_char_counter];
      }
      comm_arg[i] = '\0';
      args[j] = comm_arg;
      if (command[command_char_counter] == '\0' | command[command_char_counter] == '\n'){
        printf("meeting ender\n");
        break;
      }
      command_char_counter ++;



    }
    pid_t child = fork();
    if (child<0){
      printf("fork failed\n");
    }else if (child==0){
      execvp(args[0],args);
    } else{
      pid_t finished;
      finished = wait(NULL);
      printf("finished child %d\n",finished);
    }

  }
}
