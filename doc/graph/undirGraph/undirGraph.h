#ifndef GRAPH_JRB
#define GRAPH_JRB

#include "../libfdr/jrb.h"
#include "../libfdr/dllist.h"
typedef JRB Graph;

JRB creatGraph();

void addEdge(Graph graph,int v1,int v2);

int adjacent(Graph graph,int v1,int v2);

int getAdjacentVertices(Graph graph,int v,int *output);

void dropGraph(Graph g);

void BFS(Graph graph,int start,int stop,void(*func)(int));

void DFS(Graph graph,int start,int stop,void(*func)(int));
#endif
