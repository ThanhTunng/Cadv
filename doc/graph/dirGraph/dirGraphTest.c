#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libfdr/dllist.h"
#include "./dirGraph.h"

void printVertex(Graph graph,int u){
  JRB node = jrb_find_int(graph.vertices,u);
  printf("%10s",jval_s(node->val));
}

int main()
{
  Graph g = creat_graph();
  int* output = (int*)malloc(100*sizeof(int));

  add_vertex(g, 1, "V1");
  add_vertex(g, 2, "V2");
  add_vertex(g, 3, "V3");
  add_vertex(g, 4, "V4");
  add_vertex(g, 5, "V5");
  
  add_edge(g, 1, 3);
  add_edge(g, 1, 2);
  add_edge(g, 2, 4);
  add_edge(g, 3, 4);
  add_edge(g, 4, 5);
  
  printf("%s\n",get_vertex(g,1));
  printf("%d\n",outdegree(g,1,output));

  for(int i=0;i<outdegree(g,1,output);i++){
    printf("%d\t",output[i]);
  }
  printf("\n");
  //print out the whole graph
  list_graph(g,output);

  printf("BFS from 1 to all:");
  BFS(g,1,-1,printVertex);
  printf("\n");
  
  printf("DFS from 1 to all:");
  DFS(g,1,-1,printVertex);
  printf("\n");

  drop_graph(g);
  free(output);
  return 0;
}
