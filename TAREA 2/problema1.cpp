// T A R E A  2
// Problema 1: El Teclado Descompuesto


// L I B R E R I A S

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef string Element;


// S T R U C T

struct nodo{
  Element info;
  nodo* sig;

};


// C L A S S

class Lista {

  private:

    nodo* head;
    nodo* tail;
    nodo* curr;
    int size;
    int pos;


  public:

    Lista();
    int insert(Element info);
    void moveToStart();
    void moveToEnd();
    void prev();
    void next();
    Element retorno();
    int lengh();

};


// F U N C I O N E S - C L A S S  L I S T A

int Lista::lengh(){
  return size;
  
}

/*****
* int lengh
******
* Resumen Función: da el tamano de la lista
******
* Input:
*   Sin input
* .......
******
*   Returns:
*     int size: tamaño de la lista
*****/

Element Lista::retorno(){
  return curr->info;
  
}

/*****
* Element retorno 
******
* Resumen Función retorna el elemento actual de la posicion en la lista 
******
* Input:
*   Sin input
* .......
******
* Returns:
*   Element curr->info: informacion de la posicion actual de la lista
*****/

void Lista::next(){
  if (curr != tail){
    curr = curr->sig;
    pos++;
    
  }
}

/*****
* void  next
******
* Resumen Función: mueve el parametro pos a la siguiente posicion
******
* Input:
*   La funcion no recibe ningun parametro
* .......
******
* Returns:
*   Al ser una funcion void no retorna nada
*****/

void Lista::moveToStart(){
  curr = head;
  pos = 0;
  
}

/*****
* void moveToStart
******
* Mueve el parametro pos al inicio de la lista
******
* Input:
*   La funcion no recibe ningun parametro
* .......
******
* Returns:
*   Al ser una funcion void no retorna nada
*****/


void Lista::moveToEnd(){
  curr = tail;
  pos = size;
  
}

/*****
* void  moveToEnd
******
* Resumen Función mueve el parametro pos al final de la  lista
******
* Input:
*   La funcion no recibe ningun parametro
* .......
******
* Returns:
*   Al ser una funcion void no retorna nada
*****/


void Lista::prev(){
  
  nodo* temp;
  if (curr == head) return;
  temp = head;
  
  while(temp->sig != curr) {
    temp = temp->sig;
    
    }
  
  curr = temp;
  pos--;
  
}

/*****
* void prev
******
* Resumen Función: mueve el parametro pos un elemento hacia atras
******
* Input:
*   La funcion no recibe ningun parametro
* .......
******
* Returns:
*   Al ser una funcion void no retorna nada
*****/


Lista::Lista(){
  head=tail=curr=new nodo;
  size = 0;
  pos = 0;
  
}

/*****
* Lista
******
* Resumen funcion: inicializa la lista
******
* Input:
*   Sin input 
* .......
******
* Returns:
*   Sin retorno
*****/


int Lista::insert(Element info){
  
  nodo* aux;
  aux = curr->sig;
  curr->sig = new nodo;
  curr->sig->info = info;
  curr->sig->sig = aux;
  
  if (curr == tail) tail = curr->sig;
  size++;
  
  return pos;
}

/*****
* int insert
******
* Inserta un elemento en la lista en la posicion actual
******
* Input:
*   Element info: elemento a insertar en la lista
* .......
******
* Returns:
*   int pos, retorna la posicion donde es insertado el elemento
*****/


string ordenador(string a){
  
  Lista *p = new Lista();
  string final = "";
  
  for (char i : a) {
    string letra(1, i);
    
    if (letra == "<") {
      p->next();
      }
      
    else if (letra == ">") {
      p->prev();
      } 
      
    else if (letra == "[") {
      p->moveToEnd();  
      }
      
    else if (letra == "]") {
      p->moveToStart();} 
      
      else {
        p->insert(letra);
        }
  }
  
  p->moveToEnd();
  
  for (int x = 0; x <= p->lengh(); x++){
    final += p->retorno();
    p->prev();
    
  }
  
  return final;
}

/*****
* string ordenador
******
* Funcion que recibe una string sin traducir y la traduce 
******
* Input:
*   string a : String que contiene el texto sin traducir
* .......
******
* Returns:
*   string final: una string con el texto traducido
*****/


// F U N C I O N  M A I N

int main(){
  
  ifstream archivotxt;
  
  archivotxt.open("teclado-entrada.txt");
  
  ofstream file;
  
  file.open("teclado-salida.txt");
  
  string m;
  
  while (getline(archivotxt, m)){
    if(m != "EOF"){
      string testo = ordenador(m);
      testo += "\n";
      cout << testo;
      file << testo;
    }
    
  }

  
  file.close();
  archivotxt.close();
  
  return 0;
  
}