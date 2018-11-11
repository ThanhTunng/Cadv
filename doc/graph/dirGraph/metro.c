#include <stdio.h>
#include <stdlib.h>
#include "metroLib.h"

void printVertex(Graph g, int i){
  JRB node = jrb_find_int(g.vertices,i);
  printf("%20s",jval_s(node->val));
}

void clear_buffer(){
  char ch;
  while((ch=getchar())!= '\n' && ch!=EOF);
}

int countLines(char* file){
  FILE *fr = fopen(file,"r");
  if(fr==NULL){
    printf("cannot open file %s\n",file);
    return 0;
  }
  int count =0;
  char c;
  while((c=fgetc(fr))!=EOF){
    if(c=='\n') count++;
  }
  fclose(fr);
  return count;
}

void readData(char *file,Graph g,int n){
  FILE *fr =fopen(file,"r");
  if(fr==NULL){
    printf("cannot open %s\n",file);
    return;
  }

  char c;
  int count=0;
  while(!feof(fr)){
    char *station = (char*)malloc(20*sizeof(char));
    //clear_buffer();
    fgets(station,20,fr);
    station[strlen(station)-1] = ' ';
    printf("%s\n",station);
    add_vertex(g,++count,station);
  }
  
  fclose(fr);
  return;
}

#define MAX 100

int main(){
  Graph lines = creat_graph(0);
  int *output = (int*)malloc(MAX*sizeof(int));

  //Input data
  int n = countLines("metro.txt");
  readData("metro.txt",lines,n);

  add_edge(lines, 1, 2);
  add_edge(lines, 2, 4);
  add_edge(lines, 4, 3);
  add_edge(lines, 3, 7);
  add_edge(lines, 3, 5);
  add_edge(lines, 6, 8);
  add_edge(lines, 8, 9);

  //Application
  int choice;
  do{
    //printf("1.Input the start \n");
    printf("1.Print out all stations linked with\n");
    printf("2.Find the adjacent stations\n");
    printf("3.Fint the shortes way to stations");
    printf("4.Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d",&choice);

    switch(choice){
      /*case 1:{
      
      break;
    }*/
    case 1:{
      list_graph(lines,output); 
      break;
    }
    case 2:{
      /*int str;
      printf("Enter your current station: ");
      scanf("%d",&str);
      JRB temp = make_jrb();
      jrb_traverse(temp,lines.vertices){
	if(jval_i(temp->key) == str) break;
	else continue;
      }
      printf("%d\n",jval_i(temp->key));
      int c = outdegree(lines,jval_i(temp->key),output);
      printf("%d\n",c);
      for(int i=0;i<c;i++){
	printf("Adjacent stations: %d\n",output[i]);
      }
      free(str);*/
      break;
    }
    case 3:{
      char str1[20],str2[20];
      printf("Enter the start station: ");
      clear_buffer();
      fgets(str1,20,stdin);
      str1[strlen(str1)-1] =
      printf("Enter the end station: ");
      clear_buffer();
      fgets(str2,20,stdin);

      JRB node1,node2;
      jrb_traverse(node1,lines.vertices){
	if(strcmp(str1 , jval_s(node1->val)) == 0) break;
	else continue;
      }
      jrb_traverse(node2,lines.vertices){
	if(strcmp(str2 , jval_s(node2->val)) == 0) break;
	else continue;
      }

      if(node1 == NULL){
	printf("No info about the starting station\n");
	break;
      }
      else if(node2 == NULL){
	printf("No info about the ending station\n");
	break;
      }
      else{
	printf("%d\n",jval_i(node1->key));
	printf("%d\n",jval_i(node2->key));
      }
      break;
    }
    case 4:{
      printf("You've exit application!!  Good bye!\n");
      break;
    }
    default:{
      printf("Try again!!\n");
      getchar();
      break;
    }

    }

  }while(choice!=4);

  return 0;  
}
