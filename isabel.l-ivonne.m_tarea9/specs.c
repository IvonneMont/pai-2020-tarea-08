#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "RBtree.h"

int test_insert_element(void){ 
  printf("Al probar un elemento se debe mantener la propiedad del heap: "); 
  // Create heap 
  
  nodo *raiz=NULL;
  // add 0
  put(&raiz,0,0);
  if(get(&raiz,0) != 0 && contains(&raiz, 0)!=1){puts("ERROR"); return 0;}

  // add 1
  put(&raiz,1,1);
  if(get(&raiz,1) != 1 && contains(&raiz, 1)!=1){puts("ERROR"); return 0;}

  // add 5
 put(&raiz,2,2);
  if(get(&raiz,2) != 2 && contains(&raiz, 2)!=1){puts("ERROR"); return 0;}

  // add 3
  put(&raiz,3,3);
  if(get(&raiz,3) != 3 && contains(&raiz, 3)!=1){puts("ERROR"); return 0;}

  puts("OK"); 
  //free_THeap(&th);
  return 1;
} 



void test_insert()
{
  
}

void test_remove()
{
}

int main(int num_args, char ** args)
{
 
  	int all_tests_ok = 1;
  	all_tests_ok &= test_insert_element();
  	assert(all_tests_ok); 
  

 

  return 0;
} 
