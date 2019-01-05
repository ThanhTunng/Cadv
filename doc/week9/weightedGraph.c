#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libfdr/dllist.h"
#include "./weightedGraph.h"

Graph creat_graph(int kind){
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  if(g.kind != 0) g.kind = 1;
  else g.kind = 0;
  return g;
}

void add_vertex(Graph g, int id, char* name){
  JRB node = jrb_find_int(g.vertices,id);
  if(node == NULL){
    jrb_insert_int(g.vertices,id,new_jval_s(strdup(name)));
  }else{
    printf("The vertex with id: %d existed already!!\n",id);
  }
}

char *get_vertex(Graph g,int id){
  JRB node = jrb_find_int(g.vertices,id);
  if(node == NULL){
    return NULL;
  }else{
    char *name = strdup(jval_s(node->val));
    return name;
  }
}

void add_edge(Graph g,int v1,int v2,double weight){
  JRB node1 = jrb_find_int(g.vertices,v1);
  JRB node2 = jrb_find_int(g.vertices,v2);
  //check existence of node with id v1 v2
  if(node1 == NULL){
    printf("Vertex %d doesn't exist!!\n",v1);
    return;
  }
  else if(node2 == NULL){
    printf("Vertex %d doesn't exist!!\n",v2);
    return;
  }
  else{
    //v1 v2 already exist
    node1 = jrb_find_int(g.edges,v1);//find node v1 in edges tree
    JRB tree;// tree of outdegree of node v1
    if(node1 == NULL){
      tree = make_jrb();//v1 does not exist in edge tree -> creat new tree for outdegree
      jrb_insert_int(g.edges,v1,new_jval_v(tree));//insert node v1 to edges tree
    }else
      tree = (JRB)jval_v(node1->val);//if v1 existed already

    JRB check;
    check = jrb_find_int(tree,v2);//check the existence of the edge between v1 and v2
    if(check==NULL)
      jrb_insert_int(tree,v2,new_jval_d(weight));//insert the edge with weight


    //for undirected weighted graph
    if(g.kind == 0){
      node2 = jrb_find_int(g.edges,v2); // find edge-tree of vertex v2 
      if(node2 == NULL){ // edge-tree of vertex v2 doesn't exist(degree = 0)
	tree = make_jrb();
	jrb_insert_int(g.edges,v2,new_jval_v(tree));
      }else tree = (JRB)jval_v(node2->val);
      // add adge v2 --> v1
      jrb_insert_int(tree,v1,new_jval_d(weight));
      }
  }
}

double get_edge_weight(Graph g,int v1,int v2){
  JRB node = jrb_find_int(g.vertices,v1);
  if(node == NULL) return INFINITE_VALUE;//if v1 doesnt exist
  else{
    if(v1==v2) return 0;
  }

  JRB node1 = jrb_find_int(g.edges,v1);
  if(node1 == NULL)
    return INFINITE_VALUE; // if v1 has no outdegree
  else{
    JRB node2 = jrb_find_int((JRB)jval_v(node1->val),v2);
    if(node2 == NULL) return INFINITE_VALUE; // if no edges between v1 & v2
    else return jval_d(node2->val);
  }
}

void drop_graph(Graph g){
  JRB node;
  jrb_traverse(node,g.edges)
    jrb_free_tree((JRB)jval_v(node->val));

  jrb_free_tree(g.edges);
  jrb_free_tree(g.vertices);
}

int indegree(Graph g,int v,int *output){
  JRB node = jrb_find_int(g.vertices,v);
  if(node == NULL){
    printf("Vertex %d doesn't exist!\n",v);
    return -1;
  }else{
    int count = 0;
    jrb_traverse(node,g.edges){
      JRB tmp = jval_v(node->val);
      if(jrb_find_int(tmp,v)!=NULL)
	output[count++] = jval_i(node->key);
    }
    return count;
  }
}

int outdegree(Graph g,int v,int *output){
  JRB node = jrb_find_int(g.vertices,v);
  if(node==NULL){
    printf("Vertex %d doesn't exist!!\n",v);
    return -1;
  }else{
    node = jrb_find_int(g.edges,v);
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

void list_graph(Graph graph,int* output){
  JRB node,name;
  jrb_traverse(node,graph.vertices){
    int v = jval_i(node->key);
    name = jrb_find_int(graph.vertices,v);
    printf("Vertex %s : ",jval_s(name->val));
    int n = outdegree(graph,v,output);
    if(n != 0){
      for(int i = 0;i<n;i++){
        name = jrb_find_int(graph.vertices,output[i]);
        printf("--> %s ",jval_s(name->val));
      }
    }
    printf("\n");
  }
}

//Shortest path (Dijkstra algorithm)

//Find the element with min distance to starting point in priority queue

Dllist find_min(Dllist pQueue){
  Dllist min = dll_first(pQueue);
  Dllist ptr;
  dll_traverse(ptr,pQueue){
    double *u = jval_v(ptr->val);
    double *v = jval_v(min->val);
    if(u[2] < v[2])
      min = ptr;
  }
  return min;
}


//Find the node u in priority queue

Dllist find_node(Dllist dllist,int u){
  Dllist find;
  dll_traverse(find,dllist){
    double* ptr = jval_v(find->val);
    if(ptr[0]==u)
      break;
  }
  return find;
}

//update new min distance to the starting point of the node v when go through node u (if not shorter --> not change)
void relax(Dllist pQueue,int u,int v, Graph g){
  double weight = get_edge_weight(g,u,v);//get weight of edge between u and v
  Dllist U = find_node(pQueue,u);
  Dllist V = find_node(pQueue,v);
  double *val_u = jval_v(U->val);
  double *val_v = jval_v(V->val);
  if(val_v[2] > (val_u[2] + weight)){//if exist new min distance
    val_v[2] = val_u[2] + weight;
    val_v[1] = u;//assign new parent of v is u
  }
}

double shortest_path(Graph g,int s,int t,int *path,int *length){
  int n;
  JRB visited, tNode;
  Dllist pQueue, qNode;
  int *output = (int*)malloc(100*sizeof(int));

  //initialization
  pQueue = new_dllist();
  visited = make_jrb();

  //add vertices to priority queue
  jrb_traverse(tNode,g.vertices){
    if(jval_i(tNode->key) == s){
      double *table = (double*)malloc(3*sizeof(double));
      table[0] = jval_i(tNode->key);
      table[1] = -1;
      table[2] = 0;
      dll_append(pQueue,new_jval_v(table));
    }else{
      double *table = (double*)malloc(3*sizeof(double));
      table[0] = jval_i(tNode->key);
      table[1] = -1;
      table[2] = INFINITE_VALUE;
      dll_append(pQueue,new_jval_v(table));
    }
  }

  while(!dll_empty(pQueue)){
    qNode = find_min(pQueue);
    double *doub = jval_v(qNode->val);

    //relax
    n = outdegree(g,doub[0],output);
    for(int i=0;i<n;++i){
      if(jrb_find_int(visited,output[i]) == NULL)
	relax(pQueue,doub[0],output[i],g);
    }

    //add to visited tree
    double *table = (double*)malloc(2*sizeof(double));
    table[0] = doub[1];
    table[1] = doub[2];
    jrb_insert_int(visited,(int)doub[0],new_jval_v(table));

    dll_delete_node(qNode);
  }

  double distance = 0;
  tNode = jrb_find_int(visited,t);
  if(tNode != NULL){
    double *list = jval_v(tNode->val);
    distance = list[1];
    int cnt = 0;
    int parent = 0;
    int add = t;

    while(parent!=-1){
      path[cnt++] = add;
      tNode = jrb_find_int(visited,add);
      double *fi = jval_v(tNode->val);
      parent = (int)fi[0];
      add = parent;
    }
    *length = cnt;
  }

  free(output);
  jrb_free_tree(visited);
  return distance;
}

//BFS & DFS
void BFS(Graph graph,int start,int stop,void(*func)(Graph,int)){
  JRB visited; //save the visited vertices
  Dllist queue, node;
  int u,v,i,n;
  int *output = (int*)malloc(100*sizeof(int));

  //Initialization
  queue = new_dllist();
  dll_append(queue,new_jval_i(start)); //add vertex into queue to visit first
  visited = make_jrb();

  while(!dll_empty(queue)){
    node = dll_first(queue); // dequeue
    u = jval_i(node->val); // get value - key of vertex
    dll_delete_node(node);

    if(jrb_find_int(visited,u)==NULL){ //didnt visit
      func(graph,u);
      jrb_insert_int(visited,u,new_jval_i(1)); // add to visited tree

      if(u==stop) break;

      n = outdegree(graph,u,output); //get list of adjacent
      if(n!=0){
	for(i=0;i<n;i++){
	  v = output[i];
	  if(jrb_find_int(visited,v)==NULL)
	    dll_append(queue,new_jval_i(v)); // enqueue if not visited
	}
      }

    }
    
  }

  //free memo

  jrb_free_tree(visited);
  free_dllist(queue);
  free(output);
}

void DFS(Graph graph,int start,int stop,void(*func)(Graph,int)){
  JRB visited; //save the visited vertices
  Dllist stack,node;
  int u,n,i,v;
  int *output = (int*)malloc(100*sizeof(int));

  //Initialization
  visited = make_jrb();
  stack = new_dllist();
  dll_prepend(stack,new_jval_i(start)); // add start vertex into stack to visted first

  while(!dll_empty(stack)){
    node = dll_first(stack); //pop
    u = jval_i(node->val); // get value - key of vertex
    dll_delete_node(node);

    if(jrb_find_int(visited,u) == NULL){ //if not visited yet
      func(graph,u);
      jrb_insert_int(visited,u,new_jval_i(1)); //add into visited tree
      if(u == stop) break;

      n = outdegree(graph,u,output); //get list of adjacent
      if(n!=0){
	for(i = n-1;i>=0;i--){
	  v = output[i];
	  if(jrb_find_int(visited,v)==NULL)
	    dll_prepend(stack,new_jval_i(v));//put into visited list if not visited
	}
      }
    }
  }

  //free memory
  jrb_free_tree(visited);
  free_dllist(stack);
  free(output);
}
