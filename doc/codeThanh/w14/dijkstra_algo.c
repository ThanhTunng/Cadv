#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/graph/weighted_graph_algo.h"

int main() {

    Graph *g = (Graph *)malloc(sizeof(Graph));
    read_weighted_graph(g, "dijkstra_input_graph.txt", false);

    print_graph_by_vertex_index(g);
    dijkstra(g, 1);
    find_path_dijkstra(g, 1, 6);
    printf("\n");
    return 0;
}