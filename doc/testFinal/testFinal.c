#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./weightedGraph.h"

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

int readGood(char* file,Graph good){
  FILE *fr = fopen(file,"r");
  if(fr==NULL){
    printf("cannot open file %s!!\n",file);
    return 0;
  }
  int m;
  fscanf(fr,"%d ",&m);
  //printf("%d\n",m);
  char *str = (int*)malloc(100*sizeof(int));
  int id=0;
  for(int i=1;i<=3;i++){
    fscanf(fr,"%s %d",str,&id);
    //  printf("%d - %s\n",id,str);
    add_vertex(good,id,str);
  }
  fclose(fr);
  return m;
}

int readStorage(char *file,Graph storage,int m){
  FILE *fr = fopen(file,"r");
  if(fr==NULL){
    printf("cannot open file %s!!\n",file);
    return 0;
  }

  int n;
  fscanf(fr,"%d",&n);

  //read (m+1)*n
  for(int i=1;i<=n;i++){
    char *str = (int*)malloc(100*sizeof(int));
    int idS=0;

    fscanf(fr,"%s %d",str,&idS); //scan storage
    if(get_vertex(storage,idS)==NULL)
      add_vertex(storage,idS,str); //add new storage
    
    JRB tree =make_jrb();
    int idG=0; int num=0; 

    for(int k=1;k<=m;k++){
      fscanf(fr,"%d %d",&idG,&num); //scan id and its num
      jrb_insert_int(tree,idG,new_jval_i(num)); //add id of goods and its number
    }
    jrb_insert_int(storage.edges,idS,new_jval_v(tree)); //add list of good into each storage
    
  }
  //finish read (m+1)*n
  int * output = (int*)malloc(100*sizeof(int));
  
  //read edges
  int link;
  fscanf(fr,"%d ",&link);

  for(int i=1;i<=link;i++){
    char *buff = (int*)malloc(100*sizeof(int));
    fgets(buff,50,fr);
    int id1,id2, w;
    sscanf(buff,"%d %d %d",&id1,&id2,&w);
    printf("%d %d %d\n",id1,id2,w);
    add_edge(storage,id1,id2,(double)w);
  }
  fclose(fr);
  return n;
}

int main(int argc,char* argv[]){
  Graph storage = creat_graph(0);
  Graph good = creat_graph(0);
  int *output = (int*)malloc(100*sizeof(int));
  int m,n;
  if(argc == 2){
    printf("C-advaned\nHK20182\n");
  }
  
  if(argc == 3){
    m = readGood("sanpham.txt",good);
    list_graph(good,output);
   
  }

  if(argc == 5){
    m = readGood("sanpham.txt",good);
    n = readStorage("khohang.txt",storage,m);
    int id1 = atoi(argv[3]);
    int id2 = atoi(argv[4]);
    // printf("%d %d\n",id1,id2);
    char *check1 = get_vertex(storage,id1);
    char *check2 = get_vertex(storage,id2);
    //printf("%d %d\n",id1,id2);
    if(check1 == NULL || check2 == NULL){
      printf("-1\n");
      return 0;
    }else{
      double distance = get_edge_weight(storage,id1,id2);
      printf("Edge exists?: %d\n",has_edge(storage,id1,id2));
      if(distance == INFINITE_VALUE){
	printf("-1");
	return 0;
      }else{
	printf("Distance between %d and %d: %g km\n",id1,id2,distance);
      }
      
    }
      
  }

  if(argc == 4){
    m = readGood("sanpham.txt",good);
    n = readStorage("khohang.txt",storage,m);
    JRB node,name;
    jrb_traverse(node,storage.vertices){
      int v = jval_i(node->key);
      name = jrb_find_int(storage.vertices,v);
      printf("%s :\n ",jval_s(name->val));
      JRB tree = jval_v(name->val);
      JRB tmp;
      jrb_traverse(tmp,tree){
	JRB Name = jrb_find_int(good.vertices,jval_i(tmp->key));
	printf("%s : %d\n",jval_s(Name->val),jval_i(tmp->val));
      }
     
    }
  }
  
  return 0;
}
