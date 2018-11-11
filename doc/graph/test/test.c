#include <stdio.h>
#include <stdlib.h>
//#include "../libfdr/dllist.h"
#include "graph.h"

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

void readData(char* file, Graph g,int n,int *countNode,int *countEdge){
  FILE *fr = fopen(file,"r");
  if(fr==NULL){
    printf("cannot open file %s\n",file);
    return;
  }
  int arr[40];//array stores id keys
  int N = 0;//for count node
  
  for(int i=0;i<n;i++){
    int v[10];
    char c;
    int count = 0;//count number of data per row
    do{
      int temp;
      fscanf(fr,"%d",&temp);
      if(temp==0){
	int p = i*10 + count;
	add_vertex(g, p, 0);
	arr[N] = p ; 
	N++; 
      }
      count++;
    }while((c=fgetc(fr))!='\n');
  }
  printf("%d\t",N);
  for(int i=0;i<N;i++){
    printf("%3d",arr[i]);
  }
  
  int E = 0; //for counting Edges
  
  for(int i=0;i<N;i++){
    for(int j=i+1;j<N;j++){
      int tmp = arr[j]-arr[i];
      if(tmp == 1 || tmp == 10){
	add_edge(g,arr[i],arr[j]);
	E++;
      }
      else continue;
    }
  }

  *countNode = N; *countEdge = E;
  fclose(fr);
  return;
}

int main(){
  Graph g = creat_graph(0);
  int *output = (int*)malloc(40*sizeof(int));

  int count = countLines("matrix.txt");
  int countNode, countEdge;
  readData("matrix.txt",g,count,&countNode,&countEdge);
 
  int choice;
  do{
    printf("\n\n1.Read matrix and store into a graph\n");
    printf("2.Number of nodes and edges\n");
    printf("3.Tim lien thong\n");
    printf("4.In ra cac nut lien thong lon nhat\n");
    printf("5.In ra cac nut dao\n");
    printf("8.Exit");
    printf("\nEnter your choice: ");
    scanf("%d",&choice);

    switch(choice){
    case 1:{
      list_graph(g,output);
      break;
    }
    case 2:{
      printf("Number of nodes: %d\n",countNode);
      printf("Number of Edges: %d\n",countEdge);
      break;
    }
    case 3:{
      printf("Enter the id of node: ");
      int id_node;
      scanf("%d",&id_node);
      int count_indegree = indegree(g,id_node,output);
      printf("Nodes is adjacent to %d: ",id_node);
      for(int i=0;i<count_indegree;i++){
	printf("%5d",output[i]);
      }
      
      break;
    }
    case 4:{
      int max = 0;
      Dllist id_max = new_dllist();
      
      JRB node, tree;
      tree= g.vertices;

      jrb_traverse(node,tree){  //traverse first time to find max
	int v = jval_i(node->key);
	int n = outdegree(g,v,output);
	if(n>max) max = n;
      }
      int countMax = 0;
      jrb_traverse(node,tree){  //traverse again 
	int v = jval_i(node->key);
	int n = outdegree(g,v,output);
	if(n==max){
	  dll_append(id_max,node->key);
	  countMax++;
	}
      }

      Dllist temp;
      printf("Nodes have highest outdgree: ");
      dll_traverse(temp,id_max)
	printf("%5d",jval_i(temp->val));
      printf("\n");
      break;
    }

    case 5:{
      Dllist id_min = new_dllist();
      
      JRB node, tree;
      tree = g.vertices;

      jrb_traverse(node,tree){  //traverse first time to find max
	int v = jval_i(node->key);
	int n = outdegree(g,v,output);
	if(n==0) dll_append(id_min,node->key);
      }

      Dllist temp;
      printf("Cac nut dao cua graph: ");
      dll_traverse(temp,id_min){
	printf("%5d",jval_i(temp->val));
      }
      printf("\n");
    }
    }
  }while(choice!=8);
  return 0;
}
