#include "jrb.h"
#include "jrb.c"

typedef struct dirGraph{
  JRB edges;
  JRB vertices;
}dirGraph;

dirGraph *make_dirGraph(){
  dirGraph *g = (dirGraph*)malloc(sizeof(dirGraph));
  g->edges = make_jrb();
  g->vertices = make_jrb();
  return g;
}

int main(){
  
}
