#include "graphLib.h"
#define MAX 10
int main(){
  Graph g = creatGraph(MAX);
  addEdge(g,0,1);
  addEdge(g,0,2);
  addEdge(g,0,6);
  addEdge(g,0,5);
  addEdge(g,5,3);
  addEdge(g,5,4);
  addEdge(g,3,4);
  addEdge(g,4,6);
  int *output = (int*)malloc(MAX*sizeof(int));
  int total = getAdjacentVertices(g,6,output);
  for(int i=0;i<total;i++){
    printf("(%s,%d)\n","6",output[i]);
  }
  return 0;
}
