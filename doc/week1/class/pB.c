#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countLine(char *file){
  FILE *fo = fopen(file,"r");
  if(fo==NULL){
    return 0;
  }
  int count=0;
  char c;
  while((c=fgetc(fo))!=EOF){
    if(c=='\n') count++;
  }
  fclose(fo);
  return count;
}

typedef struct phone{
  char name[15];
  char num[15];
}phone;

void readFile(char *file,phone pb[],int n){
  FILE *fr = fopen(file,"r");
  if(fr==NULL){
    printf("cannot open file\n");
    return;
  }

  for(int i=0;i<n;i++){
    fscanf(fr,"%s\t%s",pb[i].name,pb[i].num);
  }
  fclose(fr);
  return;
}

int nameCmp(void const *x,void const *y){
  char *a, *b;
  a = (char*)x;
  b = (char*)y;
  if(strcmp(a,b)==0) return 0;
  return strcmp(a,b)>0? 1:-1;
}

int main(){
  int n = countLine("phoneBook");
  phone *pb = (phone*)malloc(100*sizeof(phone));
  readFile("phoneBook",pb,n);

  qsort(pb,n,sizeof(phone),nameCmp);

  printf("%-15s%-15s\n","Name","Phone");
  for(int i=0;i<n;i++){
    printf("%-15s%-15s\n",pb[i].name,pb[i].num);
  }
  free()
  return 0;
}
