#include <stdlib.h>
#include <stdio.h>
#include "RBtree.h"

int main(){
	
	nodo *raiz=NULL;
	printf("\nAgrega llave 84\n");
	put(&raiz,rand()%20,84);
	imprimirPre(raiz);
	printf("\nAgrega llave 87\n");
	put(&raiz,rand()%20,87);
	imprimirPre(raiz);
	printf("\nAgrega llave 78\n");
	put(&raiz,rand()%20,78);
	imprimirPre(raiz);
	printf("\nAgrega llave 16\n");
	put(&raiz,rand()%20,16);
	imprimirPre(raiz);
	printf("\nAgrega llave 94\n");
	put(&raiz,rand()%20,94);
	imprimirPre(raiz);
	printf("\nAgrega llave 36\n");
	put(&raiz,rand()%20,36);
	imprimirPre(raiz);
	printf("\nAgrega llave 93\n");
	put(&raiz,rand()%20,93);
	imprimirPre(raiz);
	printf("\nAgrega llave 50\n");
	put(&raiz,rand()%20,50);
	imprimirPre(raiz);
	printf("\nAgrega llave 22\n");
	put(&raiz,rand()%20,22);
	imprimirPre(raiz);
	
	//Borrado
	printf("\nBorrado 93\n");
	deleteRB(&raiz,93);
	imprimirPre(raiz);
	printf("\nBorrado 94\n");
	deleteRB(&raiz,94);
	imprimirPre(raiz);
	printf("\nBorrado 36\n");
	deleteRB(&raiz,36);
	imprimirPre(raiz);
	printf("\nBorrado 87\n");
	deleteRB(&raiz,87);
	imprimirPre(raiz);
	printf("\nBorrado 16\n");
	deleteRB(&raiz,16);
	imprimirPre(raiz);
	printf("\nBorrado 50\n");
	deleteRB(&raiz,50);
	imprimirPre(raiz);
	printf("\nBorrado 22\n");
	deleteRB(&raiz,22);
	imprimirPre(raiz);
	printf("\nBorrado 84\n");
	deleteRB(&raiz,84);
	imprimirPre(raiz);
	printf("\nBorrado 78\n");
	deleteRB(&raiz,78);
	imprimirPre(raiz);
	return 0;
}
