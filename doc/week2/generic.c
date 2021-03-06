#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int int_compare(void const *x,void const *y){
  int a = *((int *)x);
  int b = *((int *)y);
  return (a==b ? 0 : ( a>b ? 1:-1));
}

int search(void *buf,int size,int l,int r,void *item,int (*compare)(const void *,const void* )){
  if(r<l) return -1;
  int i = (l+r)/2;
  int res = compare(item, (char *)buf + size*i);
  if(res==0) return i;
  else if(res<0) return search(buf,size,l,i-1,item,compare);
  else return search(buf,size,i+1,r,item,compare);
}

typedef struct array{
  int n;
}arr;

int main(int argc,char *argv[]){
  arr *a = (arr*)malloc(sizeof(arr)*100);
  srand(time(0));
  for(int i=0;i<100;i++){
    a[i].n = rand()%100;
  }
  
  
  qsort(a,100,sizeof(arr),int_compare);
  for(int i=0;i<100;i++){
    printf("%d\n",a[i].n);
  }
  arr *temp = (arr*)malloc(sizeof(arr));
  (*temp).n = atoi(argv[2]);
  printf("%d\n",atoi(argv[2]));
  int res = search(a,sizeof(arr),0,99,temp,int_compare);
  if(res==-1) printf("No element in array\n");
  else printf("The index of the element: %d\n",res);
  free(a);
  return 0;
}
