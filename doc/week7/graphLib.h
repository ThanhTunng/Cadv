#ifndef graph_lib
#define graph_lib

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int *matrix;
  int sizemax;
  int *visited;
}Graph;

Graph creatGraph(int max){
  Graph g;
  g.matrix = (int*)malloc(max*max*sizeof(int));
  g.sizemax = max;
  g.visited = (int*)malloc(max*sizeof(int));
  for(int i=0;i<g.sizemax;i++){
    g.visited[i]=0;
  }
  return g;
}
void addEdge(Graph g,int v1,int v2){
  g.matrix[v1*g.sizemax+v2] = 1;
  g.matrix[v2*g.sizemax+v1] = 1;
  return;
}

int adjacent(Graph g,int v1,int v2){
  int i = (g.matrix)[v1*g.sizemax+v2];
  return i;
}

int getAdjacentVertices(Graph g,int v,int *output){
  int total=0;
  for(int i=0;i<g.sizemax;i++){
    if(adjacent(g,v,i))
      output[total++] = i;
  }
  return total;
}

void dropGraph(Graph g){
  free(g.matrix);
  g.matrix = NULL;
  g.sizemax = 0;
  return;
}

#endif
