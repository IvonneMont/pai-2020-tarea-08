#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "RBtree.h"

int test_insert_element(void){ 
  printf("Al probar la funcion put, la funcion get y la funcion contains"); 
  // Create raiz
  
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
  //falta free;
  return 1;
} 


int test_Remove_element(void){ 
  printf("Al Probar la funcion delete: "); 
  // Create raiz 
  nodo *raiz=NULL;
  put(&raiz,0,0);
  put(&raiz,1,1);
  put(&raiz,2,2);
  put(&raiz,3,3);
  deleteRB(&raiz,3);
  if(contains(&raiz, 3)!=0){puts("ERROR"); return 0;}
  deleteRB(&raiz,2);
  if(contains(&raiz, 2)!=0){puts("ERROR"); return 0;}
  deleteRB(&raiz,1);
  if(contains(&raiz, 1)!=0){puts("ERROR"); return 0;}
  deleteRB(&raiz,0);
  if(contains(&raiz, 0)!=0){puts("ERROR"); return 0;}

  puts("OK"); 
  //falta free
  return 1;
}

int main(int num_args, char ** args)
{
 
  	int all_tests_ok = 1;
  	//test de la funcion insertar, get y conteins
  	all_tests_ok &= test_insert_element();
  	//test de la funcion de borrar
  	all_tests_ok &= test_Remove_element();
  	assert(all_tests_ok); 
  

 

  return 0;
} 
