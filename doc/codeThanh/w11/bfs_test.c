#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/graph/dfs.h"
#include "../lib/graph/bfs.h"

int main() {
  Graph *g = (Graph *)malloc(sizeof(Graph));

  read_graph_from_file(g, "graph_input.txt", false);
  sort_vertex_graph(g);

  print_graph(g);
  
  initialize_dfs(g);
  bfs(g, 1);

  find_shortes_path(1, 4, parent);
  return 0;
}
