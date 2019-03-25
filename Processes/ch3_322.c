#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>

#define SIZE 4096
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

void create_read_shared_memory(const char* name, void *ptr){
	int shm_fd;
	shm_fd = shm_open(name, O_CREAT | O_RDRW, 0666);
	ftruncate(shm_fd, SIZE);
	ptr = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
}

void access_write_shared_memory(const char* name, void *ptr){
	int shm_fd;
	shm_fd = shm_open(name , O_RDRW, 0666);
	ptr =mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED, shm_fd,0);
}
int main(int argc, char* argv[]){
  const char* shm_name = "OS";
  pid_t pid = fork();
  void *ptr;
  int shm_fd_parent = create_shared_memory(shm_name, ptr);
  if (pid == 0){
    void *write_ptr;
    access_write_shared_memory(name, write_ptr);

  } else {
    int *status;
    pid_t finished_child;
    finished_child = wait(status);
    printf("%s", (char *)ptr);

  }


}
