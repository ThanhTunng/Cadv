
#include <stdio.h>
#include <stdlib.h>
#include "rbtree/jrb.h"

int main(){
  JRB t = make_jrb();
  Jval a = new_jval_i(10);
  Jval b = new_jval_i(20);

  jrb_insert_int(t,1,a);
  jrb_insert_int(t,2,b);

  JRB node = jrb_find_int(t,2);
  printf("value: %d\n",jval_i(node->val));
  return 0;
}

