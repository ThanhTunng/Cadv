#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libfdr/dllist.h"
#include "graph.h"


Graph creat_graph(int i){
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  g.type = i;
  return g;
}

void add_vertex(Graph graph,int id,char* name){
  JRB node = jrb_find_int(graph.vertices,id);
  if(node == NULL){
    jrb_insert_int(graph.vertices,id,new_jval_s(name));
  }
}

char* get_vertex(Graph graph,int id){
  JRB node = jrb_find_int(graph.vertices,id);
  if(node == NULL){
    printf("No vertex with id %d\n",id);
    return NULL;
  }else{
    char* name = strdup(jval_s(node->val));
    return name;
  }
}

void add_edge(Graph graph,int v1,int v2,double weight){
  JRB node1 = jrb_find_int(graph.vertices,v1);
  JRB node2 = jrb_find_int(graph.vertices,v2);
  if(node1 == NULL && node2 == NULL){
    printf("Vertex %d and %d does not exist!\n",v1,v2);
    return;
  }
  if(node1 == NULL){
    printf("Vertex %d does not exist!\n",v1);
    return;
  }
  if(node2 == NULL){
    printf("Vertex %d does not exist!\n",v2);
    return; 
  }else{
    node1 = jrb_find_int(graph.edges,v1);
    JRB tree;
    if(node1 == NULL){
      tree = make_jrb();
      jrb_insert_int(graph.edges,v1,new_jval_v(tree));
    }
    else      tree = jval_v(node1->val);

    node2 = jrb_find_int(tree,v2);
    if(node2 == NULL){
      jrb_insert_int(tree,v2,new_jval_s("walkable cell"));
    }

    //if type = 0 for undirected graph
    if(graph.type == 0){
      node2 = jrb_find_int(graph.edges,v2);
      JRB tree;
      if(node2 == NULL){
	tree = make_jrb();
	jrb_insert_int(graph.edges,v2,new_jval_v(tree));
      }
      else      tree = jval_v(node2->val);

      node1 = jrb_find_int(tree,v1);
      if(node1 == NULL){
	jrb_insert_int(tree,v1,new_jval_s("walkable cell"));
    }

    }
  }
}

int has_edge(Graph graph,int v1,int v2){
  JRB node1 = jrb_find_int(graph.edges,v1);
  if(node1 == NULL)
    return 0;
  else{
    JRB node2 = jrb_find_int((JRB)jval_v(node1->val),v2);
    if(node2 == NULL) return 0;
    else return 1;
  }
}

int indegree(Graph graph,int v,int* output){
  JRB node = jrb_find_int(graph.vertices,v);
  if(node == NULL){
    printf("Vertex %d doesn't exist!\n",v);
    return -1;
  }else{
    int count = 0;
    jrb_traverse(node,graph.edges){
      JRB tmp = jval_v(node->val);
      if(jrb_find_int(tmp,v) != NULL)
	output[count++] = jval_i(node->key);
    }
    return count;
  }
}

int outdegree(Graph graph,int v,int* output){
  JRB node = jrb_find_int(graph.vertices,v);
  if(node == NULL){
    printf("Vertex %d doesn't exist!\n",v);
    return -1;
  }else{
    node = jrb_find_int(graph.edges,v);
    if(node == NULL) return 0;
    else{
      int count = 0;
      JRB tree = jval_v(node->val);
      jrb_traverse(node,tree)
	output[count++] = jval_i(node->key);
      return count;
    }
  }
}

JRB sp_distance, sp_parent, sp_visited;

void get_closet_vertex(Dllist pq, int* closest_vertex, double* min_length){
  double tmp;
  Dllist ptr, node = NULL;
  int u;
  *min_length = INFINITE_VALUE;
  dll_traverse(ptr,pq){
    u = jval_i(ptr->val);

    tmp = jval_d(jrb_find_int(sp_distance, u)->val);
    if(*min_length > tmp){
      *min_length = tmp;
      node = ptr;
    }
  }
  *closet_vertex = jval_i(node->val);
}

int pq_search(Dllist pq, int v){
  Dllist ptr;
  dll_traverse(ptr,pq){
    if(jval_i(ptr->val)==v)
      return 1;
  }
  return 0;
}

void drop_graph(Graph graph){
  JRB node;
  jrb_traverse(node,graph.edges)
    jrb_free_tree((JRB)jval_v(node->val));
  
  jrb_free_tree(graph.edges);
  jrb_free_tree(graph.vertices);
}

void list_graph(Graph graph,int* output){
  JRB node,tree,name;
  tree = graph.vertices;
  // for(node = jrb_first(tree);node != jrb_nil(tree);node = jrb_next(node))
  jrb_traverse(node,tree){
    int v = jval_i(node->key);
    name = jrb_find_int(graph.vertices,v);
    
    printf("Vertex %d: ",jval_i(name->key));
    int n = outdegree(graph,v,output);
    if(n > 0){
      for(int i = 0;i<n;i++){
	name = jrb_find_int(graph.vertices,output[i]);
	if(name!=NULL)
	  printf("--> %d ",jval_i(name->key));
      }
    }
    printf("\n");
  }
}

void BFS(Graph graph,int start,int stop,void(*func)(int)){
  JRB visited;
  Dllist queue,node;
  int u,v,i,n;
  int* output = (int*)malloc(100*sizeof(int));

  queue = new_dllist();
  dll_append(queue,new_jval_i(start));
  visited = make_jrb();

  while(!dll_empty(queue)){
    node = dll_first(queue);
    u = jval_i(node->val);
    dll_delete_node(node);

    if(jrb_find_int(visited,u) == NULL){
      func(graph,u);
      jrb_insert_int(visited,u,new_jval_i(1));
      if(u == stop)
	break;

      n = outdegree(graph,u,output);
      for(i = 0;i < n;i++){
	v = output[i];
	if(jrb_find_int(visited,v) == NULL)
	  dll_append(queue,new_jval_i(v));
      }
    }
  }
  jrb_free_tree(visited);
  free(output);
}

void DFS(Graph graph,int start,int stop,void(*func)(int)){
  JRB visited;
  Dllist stack,node;
  int u,n,i,v;
  int* output = (int*)malloc(100*sizeof(int));

  visited = make_jrb();
  stack = new_dllist();
  dll_prepend(stack,new_jval_i(start));

  while(!dll_empty(stack)){
    node = dll_first(stack);
    u = jval_i(node->val);
    dll_delete_node(node);

    if(jrb_find_int(visited,u) == NULL){
      func(graph,u);
      jrb_insert_int(visited,u,new_jval_i(1));
      if(u == stop)
	break;

      n = outdegree(graph,u,output);
      if(n != 0){
	for(i = n-1;i >= 0;i--){
	  v = output[i];
	  if(jrb_find_int(visited,v) == NULL)
	    dll_prepend(stack,new_jval_i(v));
	}
      }
    }
  }
  jrb_free_tree(visited);
  free(output);
}




// For Directed Graph
int dag_Check,dag_Start;

void dag_visit(Graph graph,int v){
  if(has_edge(graph,v,dag_Start))
    dag_Check = 1;
}

int DAG(Graph graph){
  JRB node;
  jrb_traverse(node,graph.vertices){
    dag_Start = jval_i(node->key);
    dag_Check = 0;
    DFS(graph,dag_Start,-1,dag_visit);
    if(dag_Check == 1) return 0;
  }
  return 1;
}
/*
// Find Shortest Path
void shortest_path(Graph graph,int start,int stop,void(*func)(Graph,int,int)){
  JRB visited,pred,tNode;
  Dllist queue,qNode;
  int* output = (int*)malloc(100*sizeof(int));
  int u,v,n,k;
  
  visited = make_jrb();
  pred = make_jrb();
  queue = new_dllist();
  dll_append(queue,new_jval_i(start));
  jrb_insert_int(pred,start,new_jval_i(-1));

  // Start BFS from start to stop
  while(!dll_empty(queue)){
    qNode = dll_first(queue);
    u = jval_i(qNode->val);
    dll_delete_node(qNode);

    if(jrb_find_int(visited,u) == NULL){
      jrb_insert_int(visited,u,new_jval_i(1));
    }
    
    if(u == stop) break;
    
    n = outdegree(graph,u,output);
    if(n != 0){
      for(int i = 0;i < n;i++){
	v = output[i];
	if(jrb_find_int(visited,v) == NULL)
	  if(jrb_find_int(pred,v) == NULL){
	    jrb_insert_int(pred,v,new_jval_i(u));
	    dll_append(queue,new_jval_i(v));
	  }
      }
    }
  }
  
  // Finish BFS
  Dllist path = new_dllist();
  tNode = jrb_find_int(pred,stop);
  if(tNode == NULL){
    printf("No Path!\n");
    return;
  }else{
    dll_prepend(path,new_jval_i(stop));
    k = jval_i(tNode->val);
    while(k != start){
      dll_prepend(path,new_jval_i(k));
      tNode = jrb_find_int(pred,k);
      k = jval_i(tNode->val);
    }
    dll_prepend(path,new_jval_i(k));
  }
  dll_traverse(qNode,path){
    func(graph,jval_i(qNode->val),path);
  }
  printf("\n");
  
  jrb_free_tree(pred);
  jrb_free_tree(visited);
  free(output);
}
*/
double shortest_path(Graph g,int s,int t,int *path,int *length){
  int i, n, output[100];
  int closet_vertex;
  double min_length, w;

  JRB node;

  sp_dis
  
}
