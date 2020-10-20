#include <stdlib.h>
#include <stdio.h>
#include "RBtree.h"

void deleteRB( nodo** raiz, int key ){
	nodo* z= *raiz;
	//Busca el nodo con la llave
	while(z!=NULL&&z->key!=key)
	 {
		 if(key>z->key)
			z = z->der;
		 else
		  z = z->izq;
	 }
	//Si no encontró ningún nodo se sale de la función
	if(z==NULL)
		return;
	//z es el nodo a borrar
	if(z==*raiz&&z->der==NULL&&z->izq==NULL)
	 {
		 free(z);
		 *raiz=NULL;
		 return;
	 }
	nodo* y=NULL;
	if(z->izq==NULL||z->der==NULL)
		y = z;
	else
	  { 
		  y = RBSucesor(z);  //y es el sucesor de z, y es una hoja
		  //printf("\nsucesor: %i\n",y->key);
		}
	nodo* x=NULL; 
	if(y->izq!=NULL)
		x=y->izq;
	else
	  x = y->der;
	if(x!=NULL)
		x->padre=y->padre;
	if(y->padre==NULL)
	  *raiz=x;
	else{
		 if(y==y->padre->izq) //y es hijo izquiero
		   y->padre->izq = x;
		 //si no y es hijo derecho
		 else
		  (y->padre)->der=x;
	   }
		
	if(y!=z)
	 z->key =y->key;
	int color = y->color;
	if(color==0)
	 {
		 //printf("\nfix\n");
		 if(x==NULL)//se crea NIL
		  {
			  //printf("\nx NULL\n");
			  nodo *w=NULL;
			  x= y->padre;
			  //printf("\nx igual al padre de y\n");
			 
			  if(x->der==NULL&&x->izq==NULL)//x es el único nodo
			   {
				   x->color=0;
				   free(y);
				   return;
			   }
			   if(x==*raiz)
			   {
				   if(x->der==NULL)
				    {
						if(x->izq->der==NULL&&x->izq->izq==NULL)
						 {
							 x->color=0;
							 x->izq->color=1;
							 free(y);
							 return;
					     }
					}
					if(x->izq==NULL)
				    {
						if(x->der->der==NULL&&x->der->izq==NULL)
						 {
							 x->color=0;
							 x->der->color=1;
							 free(y);
							 return;
					     }
					}
			   }
			  //si no, tiene un hijo no nulo
			  if(x->der==NULL) //tiene hijo izquierdo
				{
					//printf("\nx tiene hijo izquierdo\n");
					w=x->izq;
					//printf("\nw: %i\n",w->key);
					if(w->color==1)
					 {
					   //printf("\nw es rojo\n");
					   w->color=0;
					   if(x->padre!=NULL)
							x->padre->color=1;
				       rightR(raiz,x);
				       if(x->padre==NULL)
						{
							 *raiz = w;
							  //printf("\nw es la raiz\n");
						 }
				       w=w->der;
				       //printf("\nw %i\n",w->key);
				       //printf("\nx %i\n",x->key);
				     }
				   
					 if(w->izq->color==0)
				     {
					   if(w->der!=NULL)
						w->der->color=0;
					   w->color=1;
					   
					   //printf("\nx %i\n",x->key);
					   rightR(raiz, x);
					   x=x->padre;
					   x->color=1;
					   x->der->color=0;
					   x->izq->color=0;
					   
					   
				    }
				}
			  else{
				  //tiene hijo derecho
				  w=x->der;
				  w->color=0;
				  //printf("\nw %i\n",w->key);
				  leftR(raiz,x);
				  if(x->padre==NULL)
					{
						*raiz=w;
					}
				  if(x->der!=NULL)
					x->der->color=1;
				  if(x->izq!=NULL)
					x->izq->color=1;
				  
				  //printf("\nw %i\n",w->key);
			    }
			free(y);
			return;  
		  }
		 RBDeleteFixup(raiz, x);
	 }
	 free(y);	
    
}
void RBDeleteFixup(nodo** raiz, nodo* x){
	nodo* w=NULL;
	while(x!=*raiz&&x->color==0){
		if(x==x->padre->izq)//x es hijo izquierdo
		 {
			 w=x->padre->der; //w es el hermano de y
			 if(w!=NULL&&w->color==1)
			  {
				  w->color=0;
				  x->padre->color=1;
				  leftR(raiz,x->padre);
				  w =x->padre->der;
			  }
			 if(w->izq->color==0&&w->der->color==0)
			  {
				  w->color=1;
				  x=x->padre;
			  }
			 else
			  {
				  if(w->der->color==0)
				   {
					   w->izq->color=0;
					   w->color=1;
					   rightR(raiz, w);
					   w=x->padre->der;
					   
				   }
				   w->color=x->padre->color;
				   x->padre->color=0;
				   w->der->color=0;
				   leftR(raiz,x->padre);
				   x = *raiz;
			  }
		 }
		else
		 {
             w=x->padre->izq; //w es el hermano de y
			 if(w!=NULL&&w->color==1)
			  {
				  w->color=0;
				  x->padre->color=1;
				  rightR(raiz,w);
				  w =x->padre->der;
			  }
			 if(w!=NULL&&w->der->color==0&&w->izq->color==0)
			  {
				  w->color=1;
				  x=x->padre;
			  }
			 else
			  {
				  if(w->izq->color==0)
				   {
					   w->der->color=0;
					   w->color=1;
					   leftR(raiz, w);
					   w=x->padre->der;
					   
				   }
				   w->color=x->padre->color;
				   x->padre->color=0;
				   w->izq->color=0;
				   rightR(raiz,x->padre);
				   x = *raiz;
			  }
		 }
	 }
  x->color=0;
	
}

nodo* RBSucesor(nodo* root)
{
	nodo* y =MaxAtLeft(root); 
	if (y==NULL)
	 y = MinAtRight(root);
	return y;
}
nodo* MinAtRight(nodo* root){
	if(root->der==NULL) return NULL;
	if(root->der->izq==NULL) {// Minimum is at root − >right
        return root->der;
      }
	nodo* x= root->der;
	// Min node is attained by going left
	while (x->izq->izq != NULL) {
      x = x->izq;
    }
	return x->izq;
}

nodo* MaxAtLeft(nodo* root){
	if(root->izq==NULL) return NULL;
	if(root->izq->der==NULL) {// Max is at root − >izq
		return root->izq;
      }
	nodo* x= root->izq;
	// Max node is attained by going right
	while (x->der->der != NULL) {
      x = x->der;
    }
	return x->der;
}


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
    while (z!=*raiz&&z->padre->color==1)
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
               //si z es hijo derecho d
            else 
            {
				if(z==z->padre->der)
				{
					//se aplica el caso 2
					z=z->padre;
					leftR(raiz, z);
				}
                
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
            
            y=((z->padre)->padre)->izq;
            if(y!=NULL && y->color==1)
               {
                //caso 1 papa y tio son rojos
                z->padre->color=0;
                y->color=0;
                z->padre->padre->color=1;
                z=z->padre->padre;
               } 
            else 
            {
                if(z==z->padre->izq)
                {
                 //caso 2
                 z=z->padre;
                 rightR(raiz, z);
			    }
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
    (*raiz)->color=0;
}
int get(nodo **raiz, int key)
{
    nodo *x;
    x = *raiz;

    while(x!=NULL)
    {
        if(key<x->key)
        {
        //si la llave a buscar es menor que la del nodo actual 
        //baja por la izquierda
            x=x->izq;
        }
        //si la llave a buscar es mayor que la del nodo actual 
        //baja por la derecha
        else if(key>x->key)
        {
            x=x->der;
        }    
        else
        {    
            //si no se cumplio ninguna de las anterioes encontro la llave
            return x->data;
            printf("el dato asociado a la llave: %i, es: %i.\n",key,x->data);
        }
    }
    printf("la llave: %i, no existe en el arbol.\n",key);
    return 0;
}

int contains(nodo **raiz, int key)
{
    nodo *x;
    x = *raiz;

    while(x!=NULL)
    {
        if(key<x->key)
        {
        //si la llave a buscar es menor que la del nodo actual 
        //baja por la izquierda
            x=x->izq;
        }
        //si la llave a buscar es mayor que la del nodo actual 
        //baja por la derecha
        else if(key>x->key)
        {
            x=x->der;
        }    
        else
        {    
            //si no se cumplio ninguna de las anterioes encontro la llave
            return 1;
            printf("la llave: %i, si se encuentra dentro del arbol.\n",key);
        }
    }
    printf("la llave: %i, no existe en el arbol.\n",key);
    return 0;
}

int isEmpty(nodo **raiz)
{
    if(*raiz==NULL)
      {
        return 1;
      }  
    else
     {
        return 0;
     }
}
/*void cuenta(nodo **raíz, int *num)
{
    nodo *x;
    x=*raiz;
    if ( x != NULL)
    {
        (*num)++;
        cuenta(x->izq, num);
        cuenta(x->der, num);
    }
}
int size(nodo **raiz)
{

    int *num;
    cuenta(raiz,num); 

}*/

void imprimirPre(nodo *recorre)
{
    if (recorre != NULL)
    {
        printf("key = %i, color %i ->",recorre->key, recorre->color);
        imprimirPre(recorre->izq);
        imprimirPre(recorre->der);
    }
}

