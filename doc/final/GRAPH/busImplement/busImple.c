#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./wGraph.h"

void print_vertex(Graph g,int i){
  JRB node = jrb_find_int(g.vertices,i);
  printf("%-s",jval_s(node->val));
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

int getData(char* file,Graph map){
  FILE *fr = fopen(file,"r");
  if(fr==NULL){
    printf("cannot open file %s\n",file);
    return 0;
  }

  char line[500];
  int mode = 0;
  int stat = 1;
  char *bus;

  while(fgets(line,500,fr)!= NULL){
    if(strcmp(line,"<BUS>\n") == 0){
      mode = 1;
      continue;
    }else if(strcmp(line,"<ARRIVE>\n") == 0){
      mode = 2;
      continue;
    }else if(strcmp(line,"<GOBACK>\n")==0){
      mode = 2;
      continue;
    }

    switch(mode){
    case 1:{
      bus = strdup(line);
      bus[strlen(bus)-1] = '\0';
      break;
    }
    case 2:{
      char *prev = NULL;
      char *cur = NULL;
      cur = strtok(line,"-");
      while(cur!=NULL){
	printf("%s\n",cur);
	if(get_vertex_id(map,cur) == -1){
	  add_vertex(map,stat++,cur);
	}
	printf("%d\n",get_vertex_id(map,cur));
	if(prev!=NULL){
	 if(has_edge(map,get_vertex_id(map,prev),get_vertex_id(map,cur))==0)
	   add_edge(map,get_vertex_id(map,prev),get_vertex_id(map,cur),bus);
	}
	prev =  strdup(cur);
	cur = strtok(NULL,"-\n");
      }
      free(prev); free(cur);
      break;
    }
    }
    
  }
  fclose(fr);
  return stat;
}

int main(){
  Graph map = creat_graph(1);
  int *output = (int*)malloc(100*sizeof(int));
  int choice;
  int n=0;
  do{
    printf("1.Read data from file\n");
    printf("2.Look for the shortest path\n");
    printf("3.Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice){
    case 1:{
      printf("Enter the file name: ");
      char name[50];
      scanf("%s",name);
      
      n = getData(name,map);
      printf("%d\n",n);
      break;
    }
    case 2:{
      printf("Enter the starting point: \n");
      char start[20];
      scanf("%s",start);
      
      printf("Enter the ending point: \n");
      char end[20];
      scanf("%s",end);
      
      printf("%d\n",get_vertex_id(map,start));
      printf("%d\n",get_vertex_id(map,end));
      Dllist path = shortest_path(map,get_vertex_id(map,start),get_vertex_id(map,end));
      if(path==NULL) printf("No path between %s and %s\n",start,end);
      else{
	Dllist node;
	char *busName;
	dll_traverse(node,path){
	  print_vertex(map,jval_i(node->val));
	  printf("%-s","-->");
	}
	printf("\n");
      }
      break;
    }
    }
    
  }while(choice!=3);
  drop_graph(map);
  return 0;
}
