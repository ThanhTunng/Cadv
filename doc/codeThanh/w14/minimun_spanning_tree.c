#include <stdio.h>
#include <string.h>
#include "../lib/graph/weighted_graph_algo.h"

int main() {
  
  Graph *g = (Graph *)malloc(sizeof(Graph));
  read_weighted_graph(g, "spanning_tree_graph_input.txt", true);
  sort_vertex_graph(g);

  // print_graph_by_vertex_index(g);
  print_graph(g);
  kruskal(g);
  return 0;
}