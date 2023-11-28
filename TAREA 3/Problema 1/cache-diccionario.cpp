// PROBLEMA 1 - CACHING

//Define
#define VACIA -1
#define M 128


//Librerias
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

typedef int nashe;


//Variables globales
int totalGlob=0;
int Con=0;
int Desc=0;
int CleanUps=0;
int Ace=0;


//Struct
struct diccionario {
    string word;
    string term;

};

struct ranura {
    int consultas=0;
    bool nuncaUsada=true;
    bool ocupada=false;
    bool liberada=false;
    nashe clave;
    diccionario info;
};

ranura HT[M];


//Funciones
int ValorHash(string x) {  //plegamiento
    int i, sum;
    int len = x.length();
    for (sum=0, i=0; i<len; i++) sum += (int) x[i];
    return sum % M;
};

/*****
* int ValorHash(string x)
******
* Retorna el valor hash del string
******
* Input:
* string x : Es el string que se quiere transformar a valor hash
******
* Returns:
* sum % M, Corresponde al valor del hash
*****/


int p(string term, int i){ 
    int u, sum;
    int len = term.length();
    for (sum=0, u=0; i<len; i++) sum += (int) term[u];   
    return (i+sum)%M;
};

/*****
* int p(string term, int i)
******
* Corresponde a la funcion colision, la que se encarga de dar la siguiente clave a consultar.
******
* Input:
* string term : Es el termino que se quiere insertar
* int i : Valor que corresponde a las veces que ha colisionado
******
* Returns:
* (i+sum)%M, Nueva posicion a probar para insertar el termino
*****/


//Class - CacheDiccionario
class CacheDiccionario {
    public:
        CacheDiccionario(); //Constructor 

        void printHash();

        int checkClean();
        
        void insertHelp(int i,string termino,char *term,string significado);

        bool query (string termino, string& significado);

        void insert(string termino, string significado);

        void querystats (int& total, int& conocidos, int& desconocidos);

        void perfstats (int& accesses, int& hits, int& misses, int& cleanups);
        
};

//Funciones - class - CacheDiccionario
CacheDiccionario::CacheDiccionario(){  
    
    for (int i= 0;i<M;i++) {

        HT[i].liberada=false;
        HT[i].ocupada=false;
        HT[i].nuncaUsada=true;
        HT[i].clave=VACIA;
        char empty[1]= "";
        HT[i].info.term= empty;
        HT[i].info.word= empty;
        Ace++;
    }

};

/*****
* CacheDiccionario::CacheDiccionario
******
* Iniciliza el arreglo como una tabla vacia.
******
* Input: No tiene input
******
* Returns: No retorna nada
*****/


void CacheDiccionario::printHash(){
    
    cout<<"TABLA HASH"<<endl;
    for (int i=0;i<M;i++) {

        cout<<"-------------------------------"<<endl;
        cout<<"Termino "<< i+1 <<"   --> "<<HT[i].info.term<<endl;
        cout<<"Significado "<<"--> "<<HT[i].info.word<<endl;   
        Ace++;
    }
    cout<<"-------------------------------"<<endl;
    
};

/*****
* void CacheDiccionario::printHash() 
******
* Imprime la tabla Hash
******
* Input:No tiene inputs 
******
* Returns:No tiene retornos, solamente imprime por pantalla
*****/


int CacheDiccionario::checkClean(){
    int cantArc=0;
    for (int i=0;i<M;i++){
        Ace++;
        if (HT[i].clave != VACIA || HT[i].ocupada ) cantArc++;
    }   
    return cantArc;
};

/*****
* int CacheDiccionario::checkClean()
******
* Verifica las casillas que estan ocupadas y suma en un contador en caso de encontrar.
******
* Input: No tiene inputs 
******
* Returns: cantArc
* Retorna un int que contiene la cantidad de veces que se encontraron casillas con informacion.
*****/


void CacheDiccionario::insertHelp(int i,string termino,char *term,string significado){

    HT[i].clave=ValorHash(termino);
    HT[i].info.term= term;
    HT[i].info.word= significado;
    HT[i].ocupada=true;
    HT[i].nuncaUsada=true;
    Ace++;
    Con++;
};

/*****
* void CacheDiccionario::insertHelp(int i,string termino,char *term,string significado)
******
* Funciona como una funcion recursiva que se encarga de insertar los valores dentro de la tabla hash
******
* Input: 
* int i : Guarda la posicion donde se quiere guardar el termino
* string termino : Termino que se quiere insertar.
* char *term : Puntero que tiene el termino a comparar
* string significado : Es el significado de la palabra que se quiere guardar
******
* Returns: 
* No retorna nada
*****/


bool CacheDiccionario::query(string termino , string& significado ){
    totalGlob++;

    for (int i=0;i<M;i++){
        Ace++;
        if (HT[i].info.term==termino) {

            if (HT[i].info.word==""){
                Desc++;
            }       
            significado=HT[i].info.word;
            Con++;            
            HT[i].consultas++;
            return true;
        } 
        
    }

    string vacio="";
    significado=vacio;
    return false;

};

/*****
* bool CacheDiccionario::query(string termino , string& significado )
******
* Busca dentro de la tabla hash el termino que se consulta y retorna true en caso de encontrarlo. Si no se encuentra 
* retorna false.
******
* Input:
* string termino : Contiene el termino que se necesita consultar
* string& significado : Contiene la referencia del significado del termino que se esta consultando
******
* Returns:
* bool retorna un valor true en caso de que encuentre el termino y false en caso de no encontrarlo
*****/  


void CacheDiccionario::insert(string termino, string significado){
    int inicio;
    int pos=inicio=ValorHash(termino);
    int len=termino.length();
    char newTerm[len+1];
    strcpy(newTerm,termino.c_str());
    //proceso de limpieza (en caso de ser necesario)    
    if (checkClean()==M){
        CleanUps++;
        int cantMaxCons;
        int n=checkClean();
        int aux[n]={};
        int num=0;

        for (int i =0; i<M;i++){
            Ace++;
            num = HT[i].consultas;
            (aux[i]) = num;  

        }   
        int var;
        int j;
        for (int i=0;i<M;i++){ //ordena el arreglo de int que se hizo

            for (j=i+1;j<M;j++){
                if(aux[i]<aux[j]){
                    var=aux[i];
                    aux[i]=aux[j];
                    aux[j]=var;
                }
            }
        }

        cantMaxCons=aux[0];
        int temp=0;
        for (int i=0; (i<M) && (temp<M/2); i++){
            Ace++;
            if(HT[i].consultas < cantMaxCons){ 

                HT[i].clave=VACIA;
                char empty[1]= "";
                HT[i].info.term= empty;
                HT[i].liberada=true;
                HT[i].ocupada=false;
                HT[i].info.word= empty;
                temp++;    
            }

        }

    }

    for (int i=1;HT[pos].clave != VACIA && HT[pos].info.term != newTerm; i++) {
        Ace++; pos = (inicio + p(termino,i)) % M;
    }

    if (HT[pos].clave == VACIA){
        Ace++;
        insertHelp(pos,termino,newTerm,significado);
    }    
    
    else if (ValorHash(HT[pos].info.term) == ValorHash(termino)) {
        Ace++;
        insertHelp(pos,termino,newTerm,significado);
    }
  
};

/*****
* void CacheDiccionario::insert(string termino, string significado)
******
* Se encarga de insertar los valores que se quieren insertar en la tabla hash
******
* Input:
* string termino : Es el string que se quiere insertar (tiene que ser un string no vacio)
* string significado : Corresponde al significado del termino que se quiere insertar (puede ser vacio)
******
* Returns:
* No tiene retorno es una funcion void
*****/
   
   
void CacheDiccionario::querystats(int& total, int& conocidos, int& desconocidos){
    total = totalGlob;
    conocidos = Con;
    desconocidos = Desc;
};

/*****
* void CacheDiccionario::querystats(int& total, int& conocidos, int& desconocidos)
******
* Entrega estadisticas de las consultas realizadas sobre el TDA desde su creacion, entregando los siguientes en los
* parametros por referencia
******
* Input:
* int& total : Cantidad total de consultas realizadas
* int& conocidos : Cantidad total de consultas realizadas a terminos con significado no vacio
* int& desconocidos : Cantidad total de consultas realizadas a terminos con significado vacio
* .......
******
* Returns:
* No tiene retorno es una funcion void
*****/


void CacheDiccionario::perfstats(int& accesses, int& hits, int& misses, int& cleanups){
    accesses = Ace; 
    hits = Desc + Con;
    misses = Desc;
    cleanups = CleanUps;
};

/*****
* void CacheDiccionario::perfstats(int& accesses, int& hits, int& misses, int& cleanups)
******
* Entrega las estadisticas de rendimiento del TDA desde su creacion, entregando los siguientes valores en los parametros
* por referencia.
******
* Input:
* int& accesses : la cantidad de accesos realizadas a todas las ranuras de la tabla hashing base del TDA
* int& hits : la cantidad de veces que se encontro un termino consultado
* int& misses : La cantidad de veces queno se encontro un termino consultado
* int&cleanups : la cantidad de veces que nos realizo una limpieza 
* .......
******
* Returns:
* No tiene retorno es una funcion void
*****/
