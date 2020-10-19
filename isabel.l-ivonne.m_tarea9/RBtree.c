#include <stdlib.h>
#include <stdio.h>

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

void leftR(nodo **raiz, nodo *x)
{
    nodo *y;
   y = x->der;
   //Cambio de hijos
   x->der=y->izq;
    //termina de trasplantar el subarbol izquierdo de y a x asignando el padre       
   if (y->izq!=NULL)
    {
        y->izq->padre=x;
    }
    //se le asigna el padre de x a y
    y->padre=x->padre;
    //Checa que x sea la raiz
    if(x->padre==NULL)
        *raiz=y;
    //si no es la raíz checa si es hijo izquierdo
    else if(x== x->padre->izq)
        x->padre->izq=y;
    //o si es hijo derecho
    else 
        x->padre->der=y;
    //Como es rotacion a la izquierda x pasa a ser hijo izquierdo de y
    y->izq=x;
    //el papa de x ahora es y
    x->padre=y;
}

void rightR(nodo **raiz, nodo *x)
{
    nodo *y;
   //se identifico y como el hijo izquierdo de x
   y = x->izq;
   //Los hijos izquierdos de x pasan a ser los hijos derechos que tenia y 
   x->izq=y->der;
   //hacemos x el padre de hijo derecho de y
   if (y->der!=NULL)
    {
        y->der->padre=x;
    }
    //le asignamos a y el que era el padre de x
    y->padre=x->padre;
    //se checa que x no sea la raiz
    if(x->padre==NULL)
        *raiz=y;
    //Si no es la raiz checamos si es hijo derecho
    else if(x== x->padre->der)
        //si es hijo derecho su nuevo hijo derecho sera y
        x->padre->der=y;
    //si no fue hijo derecho, ni raiz es hijo izquierdo
    else 
        //asignamos y como el nuevo hijo izquierdo
        x->padre->izq=y;
    //asignamos x como el hijo derecho de y
    y->der=x;
    //el papa de x ahora es y
    x->padre=y;
}

void put(nodo **raiz, int data, int key)
{   
    

    nodo *y = NULL;
    nodo *x = *raiz;

    while(x!=NULL)
    {
        //se respeta las propiedades de la insercion binaria
        y=x;
        if(key<x->key)
        {
            x=x->izq;
        }
        else if(key>x->key)
        {
            x=x->der;
        }    
        else
        {    //si no se cumplio ninguna de las anteriores es por que 
            //la llave ya existia y se actualiza el dato
            x->data=data;
            return;
        }
    }
    //se crea el nodo a insertar 
    nodo *z = (nodo*)malloc(sizeof(nodo));
    //se verifica que conseda la memoria
    if(z==NULL)
        return;
    //se inicializa
    z->data = data;
    z->key=key;
    z->izq = NULL;
    z->der = NULL;
    z->padre=y;
    z->color=1;
    // checamos que y no sea null por que si eso pasa el arbol esta vacio
    if(y==NULL)
    {  
        *raiz=z;
        z->color=0;
        return;
    }
    //si la llave de z es mas chica que la de y, z tiene que ser hijo izq 
    else if(key<y->key)
        y->izq=z;
    //si no se cumplio las anteriores es por que la llave de z es mayor a la de y, por lo que 
    //z es hijo derecho de y
    else
        y->der=z;
    RBInsertFix(raiz,z);
}

void RBInsertFix(nodo **raiz, nodo *z)
{
    nodo *y;
    while (z->padre->color==1)
    {
        //si el papa de z es hijo izquierdo
        if(z->padre==z->padre->padre->izq)
        {
            y=z->padre->padre->der;
            if(y!=NULL && y->color==1)
               {
                //caso 1 papa y tio son rojos
                z->padre->color=0;
                y->color=0;
                z->padre->padre->color=1;
                z=z->padre->padre;
               } 
               //si z eshijo derecho d
            else if(z==z->padre->der)
            {
                //se aplica el caso 2
                z=z->padre;
                leftR(raiz, z);
                //si se convierte en caso 3
                if(z->padre!=NULL)
                    z->padre->color=0;
                if (z->padre->padre!=NULL)
                {
                    z->padre->padre->color=1;
                    rightR(raiz,z->padre->padre);
                }
            }
        }
        //si el papa de z es hijo derecho
        else
        {
            
             y=z->padre->padre->izq;
            if(y!=NULL && y->color==1)
               {
                //caso 1 papa y tio son rojos
                z->padre->color=0;
                y->color=0;
                z->padre->padre->color=1;
                z=z->padre->padre;
               } 
            else if(z==z->padre->izq)
            {
                //caso 2
                z=z->padre;
                rightR(raiz, z);
                if(z->padre!=NULL)
                    z->padre->color=0;
                if (z->padre->padre!=NULL)
                {
                    z->padre->padre->color=1;
                    leftR(raiz,z->padre->padre);
                }
            }
        }
    }
}
