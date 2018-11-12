#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define MAX 25

void print_vertex(Graph g,int i){
  JRB node = jrb_find_int(g.edges,i);
  printf("%5d",jval_i(node->key));
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

void readData(char *file,Graph g,int *countLines,int *countNode,int *countEdge,int *countGate,int gate_array[]){
  FILE *fr = fopen(file,"r");
  if(fr==NULL){
    printf("cannot open file %s\n",file);
    return;
  }
  int n;
  
  fscanf(fr,"%d",&n);
  //printf("%d\n",n);
  *countLines = n;

  int arr[40];//array stores id keys
  int N = 0;//for count node
  int gate = 0;//for count gate
  int max_col = 1;
  for(int i=1;i<=n;i++){
    char c;
    int count = 1; // number of data per row
    do{
      int temp;
      fscanf(fr,"%d",&temp);
      if(temp==0){
	int p = i*10+count;
	add_vertex(g, p, "walkable cell");

	if(p == 10+count || p == i*10 + 1 || p == i*10+max_col || p == n*10+count) gate_array[gate++] = p;

	arr[N] = p;
	N++;
      }
      count++;
    }while((c=fgetc(fr))!='\n');
    //printf("%d\n",count);
    max_col = count-1;
  }
  //  printf("%d\n",max_col);

  /*  printf("%d\t",N);
  for(int i=0;i<N;i++){
    printf("%3d",arr[i]);
    }*/
  
  int E = 0;//for counting Edges

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


  *countNode = N; *countEdge = E; *countGate = gate;
  fclose(fr);
  return;
}



/*void undirect_cell(Graph g,int id,int top,int last,void(*fucn)(Graph,int)){
  

  
  return;
  }*/





int main(){

  Graph g = creat_graph(0);
  //Graph g1 = creat_graph(1);
  
  int *output = (int*)malloc(MAX*sizeof(int));

  int count;
  int countNode, countEdge, countGate;
  int count_isle = 0;

  int gate_array[MAX];
  
  readData("data2.txt",g,&count,&countNode,&countEdge,&countGate,gate_array);
  // readData("matrix.txt",g1,&count,&countNode,&countEdge);
  int choice;
  
  do{
    printf("\n---------------------------------------------------\n");
    printf("\n1.Read maze and print the total number of vertices and edges \n");
    printf("2.Print out total number of gates of the maze \n");
    printf("3.Print out total number of isles of the maze \n");
    printf("4.Input walkable cell and print out total number of directed and undirect connected to cells of input \n");
    printf("5.Input a treasure cell and a gate \n");
    printf("6.Exit\n");
    printf("\n---------------------------------------------------\n");
    printf("\nEnter your choice: ");
    scanf("%d",&choice);

    switch(choice){
    case 1:{
      printf("\nNumber of Vertices: %d\n",countNode);
      printf("Number of Edges: %d\n",countEdge);
      break;
    }
    case 2:{

      printf("The number of gates: %d\n", countGate);
      printf("\nAll Gates: ");
      for(int i=0;i<countGate;i++){
	printf("%5d",gate_array[i]);
      }
      printf("\n");
      break;
    }
    case 3:{
      Dllist id_min = new_dllist();
      
      JRB node, tree;
      tree = g.vertices;

      jrb_traverse(node,tree){  //traverse first time to find max
	int v = jval_i(node->key);
	int n = outdegree(g,v,output);
	if(n==0) dll_append(id_min,node->key);
      }

      Dllist temp;
      int count_Isle = 0;
      printf("\nIsles of Graph: ");
      dll_traverse(temp,id_min){
	printf("%5d",jval_i(temp->val));
	count_Isle++;
      }
      printf("\nTotal number of isles: %d\n",count_Isle);
      printf("\n");
      count_isle = count_Isle;
      break;
    }

    case 4:{
      printf("\nEnter the id of vertex: ");
      int id_node;
      scanf("%d",&id_node);

      //Directed
      int count_indegree = indegree(g,id_node,output);
      int count_dir = 0;
      printf("\nDirect connected to cells of %d: ",id_node);
      for(int i=0;i<count_indegree;i++){
	printf("%5d",output[i]);
	count_dir++;
      }
      /*  printf("\nThe total number of direct connected to cell of id %d: %d \n\n",id_node,count_dir);*/

      //Undirect
     

      /*  //directed
      int *output1 = (int*)malloc(MAX*sizeof(int));
      int count_indegree1 = outdegree(g1,id_node,output1);
      printf("\nDirect connected cells of %d: ",id_node);
      for(int i=0;i<count_indegree1;i++){
	printf("%5d",output1[i]);
	}*/

      //Undirected
      int count_undir = countNode - count_isle -1;
      //   printf("The total number of undirect connected to cell of id %d : %d\n\n",id_node,count_undir);
      if(count_dir==0) printf("0\n");
      else printf("%d\n",count_dir + count_undir);
      printf("\n");
      //free(output1);
      break;
    }
    case 5:{
      int treasure, gate;
      printf("Input the treasure cell: ");
      scanf("%d",&treasure);
      printf("Input the gate: ");
      scanf("%d",&gate);
      /*int check = 0;
      for(int i=0;i<countGate;i++){
	if(gate==gate_array[i]){
	  check = 1;
	  break;
	}
      }
      if(check==0){
	printf("invalid gate\n");
	break;
	}*/

      printf("Path from the Gate to treasure cell: ");
      shortest_path(g,treasure,gate,print_vertex);
      printf("\n");
      break;
    }


    case 6:{

      printf("You've exit application\n");
      free(output);
      jrb_free_tree(g.vertices); jrb_free_tree(g.edges);
      //   jrb_free_tree(g1.vertices); jrb_free_tree(g1.edges);
      break;
    }
    default:{
      printf("Try again!!\n");
      getchar();
      break;
    }
    }
  }while(choice!=6);

  return 0;
}
