#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./weightedGraph.h"

//void print_vertex(Graph g,int i){
//  JRB node = jrb_find_int(g.edges,i);
//  printf("%5d",jval_i(node->key));
//}

int countLines(char* file){
  FILE *fr = fopen(file,"r");
  if(fr==NULL){
    printf("cannot open file %s\n",file);
    return 0;
  }
  int count =0;
  char c;
  while((c=fgetc(fr))!=EOF){
    if(c=='\n') count++;
  }
  fclose(fr);
  return count;
}

int mode(int argc){
  if(argc == 2) return 1;
  else if(argc == 3) return 2;
  else if(argc == 5) return 3;
  else if(argc == 4) return 4;
  else if(argc == 6) return 5;
  else if(argc == 8) return 6;
}

void mode1(){
  printf("C-advanced\nHK20182\n");
}

int mode2(char const *argv){
  FILE *fr = fopen(argv,"r");
  if(fr==NULL){
    printf("Cannot open file %s\n",argv);
    return 0;
  }

  Graph item = creat_graph(0);
  
  int m;
  fscanf(fr,"%d",&m);
  for(int i=1;i<=m;i++){
    char *str = (char*)malloc(100*sizeof(char));
    int id;
    fscanf(fr,"%s %d",str,&id);
    add_vertex(item,id,str);
  }
  
  int *output = (int*)malloc(100*sizeof(int));
  list_graph(item,output);
  drop_graph(item);
  fclose(fr);
  return m;
}


int mode3(char const *argv,int m,int argc1,int argc2){
  FILE *fr = fopen(argv,"r");
  if(fr==NULL){
    printf("Cannot open file %s\n",argv);
    return 0;
  }
  
  int n;
  fscanf(fr,"%d",&n); //scan number of deposi

  Graph depo = creat_graph(0);
  
  for(int i=1;i<=n;i++){ //scanf depo
    char *name = (char*)malloc(100*sizeof(char));
    int id;
    fscanf(fr,"%s %d",name,&id);

    JRB detail = make_jrb();
    for(int j=1;j<=m;j++){
      int type; int num;
      fscanf(fr,"%d %d",&type,&num);
      jrb_insert_int(detail,type,new_jval_i(num));
    }

    add_vertex(depo,id,strdup(name));
    jrb_insert_int(depo.vertices,id,new_jval_v(detail));
  }

  //scan link depos
  int link;
  fscanf(fr,"%d",&link);
  int id1; int id2; int w;
  for(int i=1;i<=link;i++){
    fscanf(fr,"%d %d %d",&id1,&id2,&w);
    add_edge(depo,id1,id2,(double)w);
  }

  double distance = get_edge_weight(depo,argc1,argc2);
  if(distance == INFINITE_VALUE) printf("No path between %d and %d\n",argc1,argc2);
  else printf("Distance between %d and %d: %g km\n",argc1,argc2,distance);
  
  return n;
}


void mode4(char const *argv1, char const *argv2,Graph depo,Graph item){
  //read argv1
  FILE *fr1 = fopen(argv1,"r");
  if(fr1==NULL){
    printf("Cannot open file %s\n",argv1);
    return ;
  }
  
  int m;
  fscanf(fr1,"%d",&m);
  for(int i=1;i<=m;i++){
    char *str = (char*)malloc(100*sizeof(char));
    int id;
    fscanf(fr1,"%s %d",str,&id);
    add_vertex(item,id,str);
  }
  //finish read argv1

  //read argv2
  FILE *fr2 = fopen(argv2,"r");
  if(fr2==NULL){
    printf("Cannot open file %s\n",argv2);
    return ;
  }
  
  int n;
  fscanf(fr2,"%d",&n); //scan number of deposi
  
  for(int i=1;i<=n;i++){ //scanf depo
    char *name = (char*)malloc(100*sizeof(char));
    int id;
    fscanf(fr2,"%s %d",name,&id);

    JRB detail = make_jrb();
    for(int j=1;j<=m;j++){
      int type; int num;
      fscanf(fr2,"%d %d",&type,&num);
      jrb_insert_int(detail,type,new_jval_i(num));
    }

    add_vertex(depo,id,strdup(name));
    jrb_insert_int(depo.vertices,id,new_jval_v(detail));
  }

  //scan link depos
  int link;
  fscanf(fr2,"%d",&link);
  int id1; int id2; int w;
  for(int i=1;i<=link;i++){
    fscanf(fr2,"%d %d %d",&id1,&id2,&w);
    add_edge(depo,id1,id2,(double)w);
  }
  //finish read argv2
  fclose(fr1); fclose(fr2);

  //check for depository
  int *output = (int*)malloc(100*sizeof(int));

  JRB temp,nameDepo;
  jrb_traverse(temp,depo.vertices){
    int v = jval_i(temp->key);
    nameDepo = jrb_find_int(depo.vertices,v);
    printf(" %s : ",jval_s(nameDepo->val));

    JRB tmp,num,Name;
    jrb_traverse(tmp,(JRB)jval_v(nameDepo->val)){
      int u = jval_i(tmp->key);
      Name = jrb_find_int(item.vertices,u);
      printf("%s : %d\n",jval_s(Name->val),jval_i(tmp->val));
    }
  }

  return;
}

int main(int argc,char const* argv[]){

  Graph item = creat_graph(0);
  Graph depo = creat_graph(0);
  switch(mode(argc)){
    case 1:{
      mode1();
      break;
    }
    case 2:{
     int  m = mode2(argv[2]);
     //list_graph(item,output);
      break;
    }
    case 3:{
      int m = mode2("sanpham.txt");
      int n = mode3(argv[2],m,atoi(argv[3]),atoi(argv[4]));
      break;
    }
    case 4:{
      //int m = mode2(argv[3]);
      //int n = mode3(argv[2],m,atoi(argv[3]),atoi(argv[4]));
      mode4(argv[3],argv[2],depo,item);
      break;
    }
    case 5:{

      break;
    }
      
  }

  return 0;
}
