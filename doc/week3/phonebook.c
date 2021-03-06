#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phoneBook.h"

int countLines(char *file){
  FILE *fo = fopen(file,"r");
  if(fo==NULL){
    printf("cannot open file\n");
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

void readDataFromFile(char *file,phoneBook *book,int n){
  FILE *fo = fopen(file,"r");
  if(fo==NULL){
    printf("cannot open file\n");
    return;
  }
  
  char *str = (char*)malloc(50*sizeof(char));
  int num;
  for(int i=0;i<n;i++){
    fscanf(fo,"%s%d",str,&num);
    addPhoneNumber(str,num,book);    
  }
  fclose(fo);
  return;
}

int main(){
  phoneBook * pB = creatPhoneBook();
  int n = countLines("phoneBook");
  readDataFromFile("phoneBook",pB,n);

  for(int i=0;i<n;i++){
    printf("%-20s%-10d\n",pB->entries[i].name,pB->entries[i].number);
  }
  dropPhoneBook(pB);
  return 0;
}
