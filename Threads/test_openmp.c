#include <omp.h>
#include <stdio.h>

int main(){

  #pragma omp parallel
  {
    printf("holaa\n")
  }
  return 0; 

}
