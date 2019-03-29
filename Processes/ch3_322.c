#include <stdio.h>
#include <stdlib.h> /*strtol*/
#include <unistd.h> /*fork*/
#include <sys/wait.h> /*wait*/
#include <sys/mman.h> /*shm_open, shm_unlink*/
#include <fcntl.h> /*O_RDWR, O_RDONLY, O_CREAT*/
#include <string.h>

#define SIZE 4096

char* stringify(unsigned long long int number){
  char char_array[SIZE];
  sprintf(char_array, "%llu ", number);
  char *char_ptr;
  char_ptr = &char_array[0];
  return char_ptr;
}
void execute_algo(char* arg, void *write_ptr){

  char *buffer;
  unsigned long long int converted_int = strtol(arg, &buffer, 10);

  sprintf(write_ptr, "%s", arg);
  write_ptr += strlen(arg);

  if (converted_int == 0){
    printf("input not pos int\n");
    return;
  }

  while (converted_int > 1){

    if (converted_int % 2 == 0){
      converted_int /= 2;
    } else {
      converted_int = 3 * converted_int +1;
    }
    char* stringified_int = stringify(converted_int);
    sprintf(write_ptr, " %s", stringified_int);
    /*sizeof a char* is 8 bytes, strlen iterates thru the array until reach \0*/
    write_ptr += strlen(stringified_int);
  }

}

void* create_readonly_shared_memory(const char* name){
  void *ptr;
  int shm_fd;
	shm_fd = shm_open(name, O_CREAT | O_RDONLY, 0666);

	ftruncate(shm_fd, SIZE);
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

  return ptr;
}

void* access_write_shared_memory(const char* name){
  void *write_ptr;
  int shm_fd;
  shm_fd = shm_open(name , O_RDWR, 0666);
  write_ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd,0);
  return write_ptr;
}
int main(int argc, char* argv[]){
  const char* shm_name = "OS";
  void *ptr;
  ptr = create_readonly_shared_memory(shm_name);
  pid_t pid = fork();
  if (pid == 0){
    if (argc == 2){
      void* write_ptr;
      write_ptr = access_write_shared_memory(shm_name);
      execute_algo(argv[1], write_ptr);
    } else {
      printf("Error:incorrect argc\n");
    }

    return 0;

  } else if (pid<0){
    printf("Error: fork failed\n");
  } else {
    pid_t finished_child;
    finished_child = wait(NULL);
    printf("Child pid = %d is done.\n", finished_child);
    printf("Message received is...\n");
    printf("%s\n", (char *)ptr);
    shm_unlink(shm_name);

  }


}
