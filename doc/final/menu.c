#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./"

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

void readData(char* file  ){
  FILE *fr = fopen(file,"r");
  if(fr==NULL){
    printf("Cannot open file %s\n",file);
    return;
  }


  return;
}

int main(){

  int choice;
  do{
    printf("\n1.\n");
    printf("2.\n");
    printf("3.\n");
    printf("4.\n");
    printf("5.\n");
    printf("6.\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice){
    case 1:{

      break;
    }
    case 2:{

      break;
    }
    case 3:{

      break;
    }
    case 4:{

      break;
    }
    case 5:{

      break;
    }
    default:{
      printf("Try again!!\n");
      getchar();
      break;
    }
      
    }
  }while(choice!=);

  return 0;
}
