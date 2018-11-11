#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define rand_max 100

int *creatArray(int size){
  int *arr = (int*)malloc(size*sizeof(int));
  return arr;
}


int *dupArray(int p[],int size){
  int *arr = (int *)malloc(size*sizeof(int));
  for(int i=0;i<size;i++){
    *(arr+i) = p[i];
  }
  return arr;
}

/*void memcpy(void *dest, void *src, size_t size){
  
  }*/

int int_compare(void const* x, void const* y){
  int m, n;
  m = *((int*)x);
  n = *((int*)y);
  if(m==n) return 0;
  return m>n? 1:-1;
}


int main(){
  int arr[30];
  int *a = creatArray(30);
  time_t t;
  srand((unsigned)time(&t));
  for(int i=0;i<30;i++){
    arr[i] = rand() %rand_max;
  }
  qsort(arr,30,sizeof(int),int_compare);
  for(int i=0;i<30;i++){
    printf("%d\n",arr[i]);
  }
  
  
  return 0;
}
