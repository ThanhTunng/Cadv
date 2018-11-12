void exch(void *x,void *y,size_t size){
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


void insertionSort(void *list,size_t size,size_t n,(int*)compare(const void*,const void*)){
  char *next;
  for(int i=1;i<n;i++){
    next = (char*)list + i*size;
    for(j=i-1;j>=0 && (compare(next,(char*)list+j*size)<0);j--)
      exch((char*)list+(j+1)*size , (char*)list+j*size);
    exch((char*)list+(j+1)*size,next);   
  }
  return;
}
