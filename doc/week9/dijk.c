#include <stdio.h>
#include "graph.h"

int length_path = 0;

void path_store(Graph g,int i,int path[]){
  JRB node = jrb_find_int(g.edges,i);
  path[length_path++] = jval_i(node->key);
}

int main(){
  Grapg g = creat_graph(1);
  int path[100];
  
  
}
