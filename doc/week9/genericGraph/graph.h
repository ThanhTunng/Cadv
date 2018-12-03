#ifndef GENERIC_GRAPH_
#define GENERIC_GRAPH_

#include <stdio.h>
#include <stdlib.h>
#include "../libfdr/jrb.h"
#include "../libfdr/dllist.h"

typedef struct{
  JRB edges;
  JRB vertices;
  int type;
}Graph;

Graph creat_graph(int i);

void add_vertex(Graph graph,int id,char *name);

char *get_vertex(Graph graph,int id);

void add_edge(Graph graph,int v1,int v2,double w); //from v1 to v2

int has_edge(Graph graph,int v1,int v2); //check if exist the edge from v1 to v2 yes or no

int indegree(Graph graph,int v,int *output);//find the vertices have edges point to v

int outdegree(Graph graph,int v,int *output);//find the vertices that v points to

void get_closet_vertex(Dllist pq, int* closest_vertex, double* min_length);

int pq_search(Dllist pq, int v);

int DAG(Graph graph);// check if graph is DAG(directed graph without directed cycles)

void list_graph(Graph graph, int *output); //list adjacent of all vertices in graph

void drop_graph(Graph graph);

//Traverse graph
void BFS(Graph grap, int start,int stop,void(*func)(int));
void DFS(Graph grap, int start,int stop,void(*func)(int));

double shortest_path(Graph g,int s,int t,int *path,int *length); 
#endif
