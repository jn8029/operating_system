#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_ARGS 80
#define MAX_HISTORY 5
#define MAX_COMMAND_LENGTH 80

struct CommandNode {
  char *command;
  int index;
  struct CommandNode *next;
};
typedef struct CommandNode CommandNode;

typedef struct {
  CommandNode *head;
  CommandNode *tail;
} CommandList;

int main(void){
  char *args[MAX_ARGS];
  int should_run = 1;
  int history_counter= 1;
  char *history = "history\n";
  char *quit = "quit\n";
  char *double_exclamation = "!!\n";

  CommandList command_list;
  CommandNode head;
  head.next = &head;
  command_list.head = &head;
  command_list.tail = &head;

  while (should_run){
    printf("osh>");
    fflush(stdout);
    char *command;
    command = (char*)malloc(sizeof(char)*MAX_COMMAND_LENGTH);
    fgets(command, MAX_COMMAND_LENGTH, stdin);


    if (strcmp(command,history)==0){
      CommandNode *temp;
      temp = command_list.head;
      while (1){
        if(temp->command!=NULL)printf("%d %s", temp->index, temp->command);
        if (temp->next == temp){
          break;
        }
        temp = temp->next;
      }
      continue;
    } else if (strcmp(command, quit)==0){
      break;
    } else if (strcmp(command,double_exclamation)==0){
      command = command_list.tail->command;
    }

    CommandNode *comm;
    /*sizeof: need to dereference comm otherwise it'll be the size of a pointer (8 bytes)*/
    comm = (CommandNode*)malloc(sizeof(*comm));
    comm->index = history_counter;
    comm->command = command;
    comm->next = comm;
    command_list.tail->next = comm;
    command_list.tail = comm;
    history_counter++;


    char arg[MAX_COMMAND_LENGTH];
    size_t command_char_counter = 0;
    for(size_t j = 0; j < MAX_ARGS; j++){
      char* comm_arg;
      comm_arg = (char*)malloc(sizeof(char)*MAX_COMMAND_LENGTH);
      size_t i = 0;
      for(; (int)command[command_char_counter] <=126 && (int)command[command_char_counter] >=33 ; command_char_counter++,i++){
        comm_arg[i] = command[command_char_counter];
      }
      comm_arg[i] = '\0';
      args[j] = comm_arg;
      if (command[command_char_counter] == '\0' | command[command_char_counter] == '\n'){

        break;
      }
      command_char_counter ++;
    }
    pid_t child = fork();
    if (child<0){
      printf("Error: fork failed\n");
    }else if (child==0){
      execvp(args[0],args);
    } else{
      pid_t finished;
      finished = wait(NULL);
      printf("Info: finished child process pid=%d\n",finished);
    }

  }
}
