#ifdef union_ADT
#define union_ADT


typedef union Jval{
  int x;
  float y;
  double z;
  char c;
  char *str;
  void *v;
}Jval;

/*
Jval new_jval_void(void *a){
  Jval j;
  j.v = *((char*)a);
  return j;
  }*/

Jval new_jval_int(int a){
  Jval j;
  j.x = a;
  return j; 
}

Jval new_jval_float(float a){
  Jval j;
  j.y = a;
  return j;
}

Jval new_jval_double(double a){
  Jval j;
  j.z = a;
  return j;
}

Jval new_jval_char(char a){
  Jval j;
  j.c = a;
  return j;
}

Jval new_jval_str(char *a){
  Jval j;
  strcpy(j.str,a);
  return j;
}

int search(void *buf,int size,int l,int r,void *item,int (*compare)(const void *,const void* )){
  if(r<l) return -1;
  int i = (l+r)/2;
  int res = compare(item, (char *)buf + size*i);
  if(res==0) return i;
  else if(res<0) return search(buf,size,l,i-1,item,compare);
  else return search(buf,size,i+1,r,item,compare);
}



#endif
