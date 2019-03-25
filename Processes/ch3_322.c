#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 4096
char* stringify(unsigned long long int number){
  printf("instringigy %llu\n",number);
  char char_array[1024];
  sprintf(char_array, "%llu", number);
  char *char_ptr;
  char_ptr = &char_array[0];
  return char_ptr;
}
void execute_algo(char* arg, void *write_ptr){
  printf("executing algo....%s\n",arg);
  char *buffer;
  unsigned long long int converted_int = strtol(arg, &buffer, 10);
  printf("start here 123....%llu\n", converted_int);
  if (converted_int == 0){
    printf("input not pos int\n");
    return;
  }
  printf("start here....345%llu\n", converted_int);
  while (converted_int > 1){

    if (converted_int % 2 == 0){
      converted_int /= 2;
    } else {
      converted_int = 3 * converted_int +1;
    }
    char* stringified_int = stringify(converted_int);
    sprintf(write_ptr, "%s\t", stringified_int);
    write_ptr += sizeof(stringified_int);
  }
  printf("holalalalal\n");
}

void create_read_shared_memory(const char* name, void **ptr){
	int shm_fd;
	shm_fd = shm_open(name, O_CREAT | O_RDONLY, 0666);
  printf("read_shared memory fd = %d\n",shm_fd);
	ftruncate(shm_fd, SIZE);
	*ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
  printf("read shared mem created\n");
}

void access_write_shared_memory(const char* name, void **ptr){
	int shm_fd;
	shm_fd = shm_open(name , O_RDWR, 0666);
  printf("write_shared memory fd = %d\n",shm_fd);
	*ptr =mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd,0);

  printf("write shared mem created\n");
}
int main(int argc, char* argv[]){
  const char* shm_name = "OS";

  void *ptr;
  int shm_fd;
	shm_fd = shm_open(shm_name, O_CREAT | O_RDONLY, 0666);
  printf("read_shared memory fd = %d\n",shm_fd);
	ftruncate(shm_fd, SIZE);
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
  printf("read shared mem created\n");
  pid_t pid = fork();
  printf("child process created %d\n",pid);

  if (pid == 0){

    if (argc == 2){
      void *write_ptr;
      int shm_fd_w;
    	shm_fd_w = shm_open(shm_name , O_RDWR, 0666);
      printf("write_shared memory fd = %d\n",shm_fd_w);
    	write_ptr =mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd_w,0);
      printf("write shared mem created\n");
      char *message = "fuck";
      sprintf(write_ptr,"%s",message);
      // execute_algo(argv[1], write_ptr);
    } else {
      printf("Error:incorrect argc\n");
    }
    printf("last lne of child\n");
    return 0;

  }else if (pid<0){
    printf("fork failed\n");
  } else {
    int *status;
    pid_t finished_child;
    finished_child = wait(status);
    printf("child %d is done..with status code %d\n", finished_child, *status);
    printf("message received %s", (char *)ptr);
    shm_unlink(shm_name);

  }


}
