#ifndef graph_h
#define graph_h
#include <stdio.h>
#include <stdlib.h>
int max;
typedef struct{
  int *matrix;
  int sizemax;
}Graph;

Graph creatGraph(){
  Graph g = *(Graph*)malloc(sizeof(Graph));
  g.matrix = (int*)malloc(max*max*sizeof(int));
  g.sizemax = max;
  return g;
}

void addEdge(Graph g,int v1,int v2){
  if(v1>max || v2>max || v1<0 || v2<0){
    printf("Invalid edge\n");
    return;
  }
  g.matrix[v1*g.sizemax+v2] = 1;
  g.matrix[v2*g.sizemax+v1] = 1;
  return;
}

int adjacent(Graph g,int v1,int v2){
  return matrix[v1*g.sizemax+v2];
}

int getAdjacentVertices(Graph g,int vertex,int *output){
  int total = 0;
  for(int i=0;i<g.sizemax;i++){
    if(adjacent(g,vertex,i)==1){
      output[total++] = i;
    }
  }
  return total;
}

void dropGraph(Graph g){
  free(g.matrix);
  g.matrix = NULL;
  g.sizemax = 0;
  free(g);
  return;
}
#endif

