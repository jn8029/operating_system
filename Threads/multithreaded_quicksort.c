#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

typedef struct {
  int *to_be_sorted;
  int front;
  int back;
} params;

int partition(int *to_be_sorted, int front, int back){
  printf("partitioning index from %d to %d\n",front,back);

  int pivot =to_be_sorted[back];
  int break_point = front-1;
  int temp;
  int slider;
  for (slider = front; slider < back; slider++ ){
    if (to_be_sorted[slider] < pivot){

      break_point ++;
      printf("replacing %d and %d\n",to_be_sorted[slider], to_be_sorted[break_point]);
      temp = to_be_sorted[slider];
      to_be_sorted[slider] = to_be_sorted[break_point];
      to_be_sorted[break_point] = temp;
    }
  }
  break_point++;
  printf("replacing %d and %d\n",to_be_sorted[slider], to_be_sorted[break_point]);
  temp = to_be_sorted[break_point];
  to_be_sorted[break_point] = pivot;
  to_be_sorted[back] = temp;
  return break_point;

}

void *quicksort(int *to_be_sorted, int front , int back){
  if (back<=front){return NULL;}
  int pivot_point = partition(to_be_sorted, front, back);
  printf("pivot point at index %d\n",pivot_point);
  quicksort(to_be_sorted, front, pivot_point-1);
  quicksort(to_be_sorted, pivot_point+1, back);
  return NULL;

}

void *runner(void *pa){
  params* p = (params*)pa;
  int front = p->front;
  int back = p->back;
  printf("executing thread sort form %d to %d\n", front, back);
  quicksort(p->to_be_sorted, front, back);


  pthread_exit(0);
}


int main(){
  int *to_be_sorted;
  to_be_sorted = malloc(sizeof(int)*ARRAY_SIZE);
  for (int i = ARRAY_SIZE, j = 0; i>0; i--,j++){

    if (i%2==0){
      to_be_sorted[j] = -2;
    } else {
      to_be_sorted[j] = i;

    }
    printf("%d\t",to_be_sorted[j]);

  }
  printf("\n");
  void *param_one = malloc(sizeof(params));
  ((params*)param_one)->to_be_sorted = to_be_sorted;
  ((params*)param_one)->front = 0;
  ((params*)param_one)->back = ARRAY_SIZE/2;
  void *param_two = malloc(sizeof(params));
  ((params*)param_two)->to_be_sorted = to_be_sorted;
  ((params*)param_two)->front = ARRAY_SIZE/2+1;
  ((params*)param_two)->back = ARRAY_SIZE-1;

  pthread_t tid_first; /* the thread identifier */
  pthread_t tid_second;

  pthread_attr_t attr_first;
  pthread_attr_t attr_second;
  pthread_attr_init(&attr_first);
  pthread_attr_init(&attr_second);
  pthread_create(&tid_first,&attr_first,runner,param_one); /* wait for the thread to exit */
  pthread_create(&tid_second,&attr_second,runner,param_two);
  pthread_join(tid_first, NULL);
  pthread_join(tid_second,NULL);
  printf("SORTED:\n");
  for (int i = 0; i<ARRAY_SIZE; i++){
    printf("%d\t",to_be_sorted[i]);
  }
  printf("\n");




}
