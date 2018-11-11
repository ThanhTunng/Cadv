#define initial_size 10
#define incre_size 5

typedef struct entries{
  char name[50];
  int number;
}phoneEntry;

typedef struct phoneBook{
  phoneEntry *entries;
  int total;
  int size;
}phoneBook;

phoneBook *creatPhoneBook(){
  phoneBook *pB = (phoneBook*)malloc(sizeof(phoneBook));
  (*pB).entries =(phoneEntry*)malloc(initial_size*sizeof(phoneEntry));
  (*pB).total = 0;
  (*pB).size = initial_size;
  return pB;
}

void dropPhoneBook(phoneBook *book){
  free((*book).entries);
}

phoneEntry *getPhoneNumber(char *name,phoneBook *book){
  for(int i=0;i<(*book).total;i++){
    if(strcmp(book->entries[i].name,name)==0)
      return (book->entries+i);
  }
  return NULL;
}

void addPhoneNumber(char *n,long num,phoneBook *book){
  phoneEntry *e = getPhoneNumber(n,book);
  phoneEntry *new_entries;
  if(e==NULL){
    if(book->total >= book->size){
      new_entries = (phoneEntry*)malloc(((*book).size+incre_size)*sizeof(phoneEntry));
      memcpy(new_entries,book->entries,(book->total)*sizeof(phoneEntry));
      (*book).entries = new_entries;
      (*book).size += incre_size;
    }else{
      strcpy((*book).entries[book->total].name,n);
      (*book).entries[book->total].number = num;
      (*book).total++;
    }
  }else{
    (*e).number = num;
  }
  return;
}
