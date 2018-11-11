#define initial_size 20
#define incre_size 10

typedef struct{
  void *key;
  void *Entry;
}value;

typedef struct{
  Entry *entries;
  size_t size;
  int total;
}symbolTable;

Entry *makeNode(void *name,void *phone){
  Entry *temp = (Entry*)malloc(sizeof(Entry));
  (*temp).key = strdup((char*)name);
  (*temp).value = malloc(sizeof(int));
  memcpy((*temp).value,phone,sizeof(int));
  return temp;
}
  
int compare(void const *x,void const *y){
  /*  char *a = (char*)x;
  char *b = (char*)y;
  int n = strcmp(a,b);
  return (n==0?0:(n>0)?1:-1);*/
  return (strcmp((char*)x,(char*)y));
}

void dropSymbolTable(symbolTable *st){
  for(int i=0;i<st->total;i++){
    free((*st).entries[i].key);
    free((*st).entries[i].value);
  }
  free((*st).entries);
}

symbolTable *creatSymbolTable(){
  symbolTable *sT = (symbolTable*)malloc(sizeof(symbolTable));
  (*sT).entries = (Entry*)malloc(initial_size*sizeof(Entry));
  (*sT).size = initial_size;
  (*sT).total = 0;
  return sT;
}

Entry *getEntry(void *name,symbolTable *ST){
  for(int i=0;i<ST->total;i++){
    if(compare((*ST).entries[i].key, name)==0){
      printf("true\n");
      return ((*ST).entries + i);
    }
  }
  return NULL;
}

void addEntry(void *name,void *val,symbolTable *ST){
  Entry *e = getEntry(name,ST);
  Entry *new_entries;
  if(e==NULL){
    if(ST->total>=ST->size){
      new_entries = (Entry*)malloc(((*ST).size+incre_size)*sizeof(symbolTable));
      memcpy(new_entries,ST->entries,(ST->total)*sizeof(Entry));
      (*ST).entries = new_entries;
      (*ST).size += incre_size;
    }
    else{
      (*ST).entries[(*ST).total] = *makeNode(name,val);
      //  strcpy((*ST).entries[ST->total].key,name);
      //(*ST).entries[ST->total].value = val;
      (*ST).total++;
    }
  }else{
    (*e).value = val;
  }
  return;
}
