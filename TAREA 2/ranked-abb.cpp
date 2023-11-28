// T A R E A  2
// Problema 2: ABB con Operacion Rank


// L I B R E R I A S

#include <iostream>
#include <stdlib.h>

using namespace std; 
typedef int tElem;
typedef int i;


// S T R U C T

struct tNodo {
    int info;
    tNodo *izq;
    tNodo *der;
};


// C L A S S

class RankedABB {

private:
    tNodo *raiz;
    int cantE;

public:
    RankedABB();
    void insert(tElem x);
    bool find(tElem x);
    int rank(tElem x);
    void verArbol(tElem x);
};


// F U N C I O N E S - C L A S S  RankedABB

RankedABB::RankedABB() {
    raiz = new tNodo;
    raiz->der=NULL;
    raiz->izq=NULL;
    cantE = 0;
};  
/*****
*   RankedABB
******
*   Resumen Función: inicializa la class RankedABB creando el primer nodo
******
*   Input:
*       Sin inputs 
* .......
******
*   Returns:
*       Sin retorno
*****/
    

tNodo *createNode(int x) {
    tNodo *newNode = new tNodo();
    newNode->info = x;
    newNode->der = NULL;
    newNode->izq = NULL;
    return newNode;
};
/*****
*   tNodo createNode
******
*   Resumen Función: crea un nodo y le asocia un valor
******
*   Input:
*       int x: valor a ingresar en  el nodo 
* .......
******
*   Returns:
*       tNodo newNode: el nodo creado con su valor asociado a la info
*****/

void insertHelp(tNodo *&arbol, tElem x) {
    if (arbol == NULL) {
        tNodo *newNode = createNode(x);
        arbol = newNode;
    } 
    else {
        int auxVRaiz;
        auxVRaiz = arbol->info;

        if (x < auxVRaiz) {
            insertHelp(arbol->izq, x);
        }   
        else {
            insertHelp(arbol->der, x);
        }
    }
};

/*****
*   void insertHelp(tNodo *&arbol, tElem x)
******
*   Es una función recursiva que recorre el arbol binario y compara los valores para saber si tiene que 
*   insertar a la derecha o izquierda, comparando si el nodo es NULL o no.
******
*   Input:
*       tNodo *&arbol : Arbol Binario
*       tElem x: Valor a añadir, el cual será iterado de manera recursiva por el arbol siguiendo las sentencias de if.
******
*   Returns:
*       Sin retorno
*****/
    

void RankedABB::insert(tElem x) {
    if (cantE == 0) {
        raiz->info = x;
        cantE++;
        return;
    } 
    else {
        cantE++;
        return insertHelp(raiz, x);
    }
};

/***** 
*   RankedABB::insert(tElem x): Es el tipo de elemento que se desea insertar dentro del arbol binario.
****** 
*   Retorna a otra función auxiliar para buscar de manera recursiva.
******
*   Input: 
*       tElem x: Es el elemento que se desea insertar * 
******
*   Returns:
*       Sin retorno
*****/

bool findHelp(tNodo *nodo, tElem x) {
    if (nodo == NULL)
        return false;
    if (nodo->info == x)
        return true;
    if (nodo->info > x)
        return findHelp(nodo->izq, x);
    else
        return findHelp(nodo->der, x); 
};

/***** 
*   bool findHelp(tNodo *nodo, tElem x): Es el tipo de elemento que se desea buscar dentro del arbol binario.
****** 
*   Retorna a otra función auxiliar para buscar de manera recursiva.
******
*   Input: 
*       tElem x: Es el elemento que se desea buscar * 
******
*   Returns:
*       findHelp, recibe como parametro el arbol binario y el valor que se desea buscar y retonar un valor booleano en caso de encontrar o no el valor x.
*****/

bool RankedABB::find(tElem x) { 
    return findHelp(raiz, x); 
};

/***** 
*   RankedABB::find(tElem x): Es el tipo de elemento que se desea buscar dentro del arbol binario.
****** 
*   Retorna a otra función auxiliar para buscar de manera recursiva.
******
*   Input: 
*       tElem x: Es el elemento que se desea buscar * 
******
*   Returns:
*       findHelp Retorna un valor booleano.
*****/

int cont = 0;

int rankHelp(tNodo *nodo, tElem x) {
    if(nodo!=NULL){
        if (x<=nodo->info) cont++;
        rankHelp(nodo->izq,x);
        rankHelp(nodo->der,x);
    }
    
    return cont;
};

/*****
*   int rankHelp
******
*   la funcion rankHelp dado un elemento x, busca retornar la cantidad de elementos que son menores o iguales a x respecto al arbol
******
*   Input:
*       tNodo *nodo: Arbol Binario
*       tElem x: valor a analizar
* .......
******
*   Returns:
*       cont, cont es un contador el cual va aumentado su valor cuando un nodo es menor o igual a x
*****/


int RankedABB::rank(tElem x) { 
    return rankHelp(raiz, x); 
};

/*****
*   int RankedABB::rank
******
*   llama a la funcion rankHelp la cual recibe el valor de x y la raiz del arbol, para analizarlo
******
*   Input:
*       tElem x : valor a analizar
* 
******
*    Returns:
*       rankHelp, la cual es una funcion que analiza el valor de x en el arbol.
*****/