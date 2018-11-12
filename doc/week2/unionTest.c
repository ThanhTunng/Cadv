#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int int_cmp(void const *x, void const *y){
  int a = *((int*)x);
  int b = *((int*)y);
  return (a==b?0:(a>b?1:-1));
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
  
  
  return 0;
}
