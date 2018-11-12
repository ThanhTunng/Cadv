#include <stdio.h>
#include <stdlib.h>
#include "undirGraph.h"
#include "../libfdr/dllist.h"
void printVertex(int v){
  printf("%3d",v);
}

#define MAXSIZE 100
int main() {

  int count;
  int *output = (int*)malloc(MAXSIZE*sizeof(int));
  Graph g = creatGraph();

  addEdge(g,1,2);
  addEdge(g,1,3);
  addEdge(g,1,4);
  addEdge(g,2,5);
  addEdge(g,2,6);
  addEdge(g,3,7);
  addEdge(g,4,8);
  addEdge(g,4,9);

  /*  addEdge(g, 1, 2);
  addEdge(g, 2, 3);
  addEdge(g, 2, 4);
  addEdge(g, 3, 4);
  addEdge(g, 3, 5);
  addEdge(g, 5, 6);*/
  
  printf("The Graph: ");
  listGraph(g,output);
  printf("\n");
  printf("\nFinish testing traverse Graph\n\nTesting BFS...\n");
  
  printf("BFS: start from 1 to all: \n");
  BFS(g,1,-1,printVertex);
  printf("\nFinish testing BFS\n\nTesting DFS....\n");
  
  printf("DFS: start from 1 to all following the depth of tree:\n");
  DFS(g,1,-1,printVertex);  
  printf("\nFinish testing DFS\n\n");

  free(output);
  dropGraph(g);
  return 0;
}
