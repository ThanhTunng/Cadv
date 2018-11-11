#include <stdio.h>
#include <stdlib.h>
#include "../libfdr/jrb.h"
#include "./undirGraph.h"

JRB creatGraph(){
  JRB g = make_jrb();
  return g;
}

void addEdge(Graph graph,int v1,int v2){
  JRB node = jrb_find_int(graph,v1);
  JRB tree;

  if(node == NULL){
    tree = make_jrb();
    jrb_insert_int(graph,v1,new_jval_v(tree));
  }else{
    tree = (JRB)jval_v(node->val);
  }
  jrb_insert_int(tree,v2,new_jval_i(1));

  node = jrb_find_int(graph,v2);
  if(node == NULL){
    tree = make_jrb();
    jrb_insert_int(graph,v2,new_jval_v(tree));
  }else{
    tree = (JRB)jval_v(node->val);
  }
  jrb_insert_int(tree,v1,new_jval_i(1));
}

int adjacent(Graph g,int v1, int v2){
  //If the tree does not have vertex v1 or v2 is not in the tree, return 0
  //If true, return 1;
  JRB node = jrb_find_int(g,v1);
  if (node==NULL) return 0;

  JRB tree = (JRB) jval_v(node->val);

  if(jrb_find_int(tree, v2) == NULL) return 0;

  return 1;
}

int getAdjacentVertices(Graph g,int vertex, int* output){
  JRB node = jrb_find_int(g, vertex);

  if(node == NULL) //vertex does not exist
    return 0;

  JRB tree = (JRB) jval_v(node->val);

  int count = 0;
  jrb_traverse(node, tree)
    output[count++] = jval_i(node->key);

  return count;
}

void listGraph(Graph graph,int* output){
  JRB node;
  for(node = jrb_first(graph);node != jrb_nil(graph);node = jrb_next(node)){
    int n = getAdjacentVertices(graph,jval_i(node->key),output);
    printf("\nVertex %d ",jval_i(node->key));
    if(n != 0)
      for(int i = 0;i<n;i++)
	printf("--> %d ",output[i]);
  }
}

void dropGraph(Graph g){
  //delete all adjacent list tree then delete vertices tree
  JRB node;
  jrb_traverse(node, g)
    jrb_free_tree(jval_v(node->val));

  jrb_free_tree(g);
}

void BFS(Graph g,int start,int stop,void(*func)(int)){
  JRB visited;
  Dllist queue,node;
  int n,i,u,v;
  int* output = (int*)malloc(100*sizeof(int));

  queue = new_dllist();
  dll_append(queue,new_jval_i(start));
  visited = make_jrb();

  while(!dll_empty(queue)){
    node = dll_first(queue);
    u = jval_i(node->val);
    dll_delete_node(node);

    if(jrb_find_int(visited,u)==NULL){ //not visited yet
      //visit u
      func(u);
      jrb_insert_int(visited,u,new_jval_i(1));

      if(u==stop) break;

      //add adjacent of u to queue
      n = getAdjacentVertices(g,u,output);
      for(i=0;i<n;i++){
	v = output[i];
	if(jrb_find_int(visited,v)==NULL)
	  dll_append(queue,new_jval_i(v));
      }
    }
  }
  jrb_free_tree(visited);
  free(output);
}

void DFS(Graph g,int start,int stop,void(*func)(int)){
  JRB visited;
  Dllist stack,node;
  int n,i,u,v;

  int* output = (int*)malloc(100*sizeof(int));

  stack = new_dllist();
  dll_prepend(stack,new_jval_i(start));
  visited = make_jrb();

  while(!dll_empty(stack)){
    node = dll_first(stack);
    u = jval_i(node->val);
    dll_delete_node(node);

    if(jrb_find_int(visited,u)==NULL){//u not visited yet
      //visit u now
      func(u);//print u out
      jrb_insert_int(visited,u,new_jval_i(1));
      if(u==stop) break;

      //add adjacent of u to queue
      n = getAdjacentVertices(g,u,output);
      for(i=0;i<n;i++){
	v = output[i];
	if(jrb_find_int(visited,v)==NULL)
	  dll_prepend(stack,new_jval_i(v));
      }
    }
  }
  jrb_free_tree(visited);
  free(output);
}
