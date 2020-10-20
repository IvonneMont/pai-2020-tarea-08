#ifndef RBTREE_T09
#define RBTREE_T09

typedef struct nodo{
     int data;
     int key;
     //0 negro y 1 rojo
     int color;
     struct nodo *izq, *der, *padre;

}nodo;
//Prototipos
void leftR(nodo **raiz, nodo *x);
void rightR(nodo **raiz, nodo *x);
void put(nodo **raiz, int data, int key);
void RBInsertFix(nodo **raiz, nodo *z);

nodo* MinAtRight(nodo* root);
nodo* MaxAtLeft(nodo* root);
nodo* RBSucesor(nodo* root);
void deleteRB( nodo** raiz, int key);
void RBDeleteFixup(nodo** raiz, nodo* x);

int get(nodo **raiz, int key); //devuelve el data asociado a la llave
int contains(nodo **raiz, int key);//nos devuelve un 1 si la llave existe dentro del arbol y un 0 si no
int isEmpty(nodo **raiz);// nos devuelve un 1 si el arbol esta vacio y 0 si no
int size(nodo **raiz);//nos regresa 
void imprimirPre(nodo *recorre);//imprime en preorden
#endif
