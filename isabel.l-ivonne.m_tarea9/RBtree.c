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

nodo* MinAtRight(nodo* root);
nodo* MaxAtLeft(nodo* root);
nodo* RBSucesor(nodo* root);
void delete( nodo** raiz, int key);
void RBDeleteFixup(nodo** raiz, nodo* x);

int get(nodo **raiz, int key); //devuelve el data asociado a la llave
int contains(nodo **raiz, int key);//nos devuelve un 1 si la llave existe dentro del arbol y un 0 si no
int isEmpty(nodo **raiz);// nos devuelve un 1 si el arbol esta vacio y 0 si no
int size(nodo **raiz);//nos regresa 
void imprimirPre(nodo *recorre);//imprime en preorden


void delete( nodo** raiz, int key ){
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
	nodo* y=NULL;
	if(z->izq==NULL||z->der==NULL)
		y = z;
	else
	  y = RBSucesor(z);  //y es el sucesor de z, y es una hoja
	 
	nodo* x=NULL; 
	if(y->izq!=NULL)
		x=y->izq;
	else
	  x = y->der;
	x->padre=y->padre;
	if(y->padre==NULL)
	  *raiz=x;
	else{
		 if(y==y->padre->izq) //y es hijo izquiero
		   y->padre->izq = x;
		 //si no y es hijo derecho
		 else
		  y->padre->der=x;
	   }
		
	if(y!=z)
	 z->key =y->key;
	int color = y->color;
	free(y);
	if(color==0)
	 RBDeleteFixup(raiz, x);
		
    
}
void RBDeleteFixup(nodo** raiz, nodo* x){
	nodo* w=NULL;
	while(x!=*raiz&&x->color==0){
		if(x==x->padre->izq)//x es hijo izquierdo
		 {
			 w=x->padre->der; //w es el hermano de y
			 if(w!=NULL&&w->color==0)
			  {
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
			 if(w!=NULL&&w->color==0)
			  {
				  x->padre->color=1;
				  rightR(raiz,x->padre);
				  w =x->padre->izq;
			  }
			 if(w->der->color==0&&w->izq->color==0)
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
					   
				   }
				   w->color=x->padre->color;
				   x->padre->color=0;
				   w->izq->color=0;
				   rightR(raiz,x->padre);
				   x = *raiz;
			  }
		 }
	 }
	
}

nodo* RBSucesor(nodo* root)
{
	nodo* y = MinAtRight(root);
	if (y==NULL)
	 y = MaxAtLeft(root);
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
               //si z eshijo derecho d
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

int main()
{
    nodo* raiz =NULL;
	 int n=20;
	 int key;
	 for(int i=0; i<n; i++)
	   {
		  key = random()%100+1;
		  printf("key: %d\n",key);
		  put(&raiz,3,key); 
		  //imprimirPre(raiz);
		  
	   }
	  //printf("\n%d",raiz->key);
	  imprimirPre(raiz);
    return 0;
}
