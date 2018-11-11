#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a,int *b){
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
  return;
}

void exch(void *x, void *y,size_t size){
  char *first = (char*)x;
  char *last = (char*)x + size;
  char *res = (char*)y;
  char temp;
  for(;first!=last;first++){
    temp = *first; *first = *res; *res = temp;
    res++;
  }
  return;
}

void sort2w(int arr[],int l,int r){
  int pivot,i,j;
  if(l>=r) return;
  i=l;j=r+1;
  pivot = arr[l];

  do{
    do i++; while(arr[i]>pivot);
    do j--; while(arr[j]<pivot);
    if(i<j) swap(&arr[i],&arr[j]);
  }while(i<j);
  swap(&arr[l],&arr[j]);
  sort2w(arr,l,j-1);
  sort2w(arr,j+1,r);
}

int int_compare(const void *a,const void *b){
  int x = *((int*)a);
  int y = *((int*)b);
  return (x==y? 0 : (x>y?1:-1));
}

void sort3w(void *a,int size,int l,int r,int (*compare)(const void*,const void*)){
  if(r<=l) return;
  int i=l-1, j=r;
  int p=l-1, q=r;

  while(1){
    while(compare((char*)a+ (++i)*size,(char*)a + r*size)<0);
    while(compare((char*)a+ r*size,(char*)a + (--j)*size)<0){
      if(j==l) break;
    }

    if(i>=j) break;
    exch((char*)a + i*size,(char*)a + j*size,size);
    if(compare((char*)a + i*size,(char*)a + r*size)==0) exch((char*)a + (++p)*size,(char*)a + i*size,size);
    if(compare((char*)a + j*size,(char*)a +r*size)==0) exch((char*)a + (--q)*size,(char*)a+ j*size,size);
  }

  exch((char*)a + i*size,(char *)a +size*r,size);
  j=i-1;
  i=i+1;
  for(int k=l;k<=p;k++) exch((char*)a + k*size,(char*)a + (j--)*size,size);
  for(int k=r-1;k>=q;k--) exch((char*)a + size*k,(char*)a + (i++)*size,size);
  sort3w(a,size,l,j,compare);
  sort3w(a,size,i,r,compare);
}

int main(){
  time_t t;
  int choice;
  do{
    printf("1.QuickSort 2-way\n");
    printf("2.QuickSort 3-way\n");
    printf("3.Exit\n");
    printf("Option: ");
    scanf("%d",&choice);
    switch(choice){
    case 1:{
      int *a = (int*)malloc(1000000*sizeof(int));
      srand((unsigned)time(&t));
      for(int i=0;i<1000000;i++){
	a[i] = rand() %10000000;
      }
  
      clock_t start,end;
      start = clock();
      sort2w(a,0,999999);
      end = clock();
      /*for(int i=0;i<100;i++){
	printf("%d\n",a[i]);
	}*/
      printf("Total time: %lf sec\n",(double)(end-start)/CLOCKS_PER_SEC);
      free(a);
      break;
    }
    case 2:{
      int *a = (int*)malloc(1000000*sizeof(int));
      srand((unsigned)time(&t));
      for(int i=0;i<1000000;i++){
	a[i] = rand() %10000000;
      }
  
      clock_t start,end;
      start = clock();
      sort3w(a,sizeof(int),0,999999,int_compare);
      end = clock();
      /*  for(int i=0;i<100;i++){
	printf("%d\n",a[i]);
	}*/
      printf("Total time: %lf sec\n",(double)(end-start)/CLOCKS_PER_SEC);
      free(a);
      break;
    }
    case 3:{
      printf("Good bye!!!\n");
      break;
    }
    default:{
      printf("Try again!");
      getchar();
      break;
    }
    }
  }while(choice!=3);
  return 0;
}
