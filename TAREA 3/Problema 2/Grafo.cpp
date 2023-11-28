// PROBLEMA 2 - GRAFOS

//LIBRERIAS
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//DEFINE
#define INFINITO 99999

#define MATRIZ_ADYACENCIA "miserables.csv"
#define ID_NOMBRES "miserables_id_to_names.csv"

//TYPEDEF
typedef int tVertice;

//FUNCIONES
int N_Vertices(){
    ifstream matriz(MATRIZ_ADYACENCIA);
    int vertices = 0;
    int i = 0; 

    while(matriz.good()){ 
                
        string line;

        getline(matriz,line,'\n'); 

        stringstream linea(line); 
        string pos;

        int j = 0; 

        while (linea.good()){

            getline(linea, pos , ';');

            if (i == 0){
                if (j != 0){
                    vertices++;
                }
            }
            j = 1;
        }

        i++;
    }
    matriz.close();
    return vertices;
}
/*****
* int N_Vertices
******
* La funcion calcula la cantidad de vertices que contiene la matriz del archivo .csv
******
* Input:
* La funcion no recibe parametros
* .......
******
* Returns:
* int vertices, Devuelve la cantidad de vertices de la matriz
*****/

string NombreID(tVertice numero){
    ifstream n_ID(ID_NOMBRES); 
    string linea;

    getline(n_ID, linea);

    while(n_ID.good()){

        string id, label;

        getline (n_ID, id, ',');
        getline (n_ID, label, '\n');

        int n_id;
        if (id != "") {
            n_id = stoi(id);
        }

        if (n_id == numero){
            n_ID.close();
            return label;
        }
    }
    string no = "-";
    return no;
}
/*****
* string NombreID(tVertice numero)
******
* La funcion recibe un Id y devuelve el Label correspondiente al Id, para esto abre el archivo csv que contiene los datos
******
* Input:
* tVertice numero : Siendo este el Id del cual se quiere obtener el Label
* .......
******
* Returns:
* string label, Retorna el nombre del id. ej: 5,Diego -> Retorna Diego
* string no, Retorna un string "-" si no encontro ningun Nombre asociado al Id
*****/ 

int Valor_Nodo(string linea , int j){
    stringstream primera(linea);
    int n = N_Vertices();
    int vertice_id;
    
    for (int i = 0; i < n ; i++){
        string vertice;
        getline(primera , vertice , ';');

        if (i != 0 &&  vertice != ""){
            if (i == j){
                vertice_id = stoi(vertice);
                return vertice_id;
            }
        }
    }
    return 0;
}
/*****
* int Valor_Nodo(string linea , int j)
******
* La funcion se encarga de recibir la linea 0 de la Matriz (la que contiene los nodos) y la posicion en la que se encuentra en la columna
* Con esto retorna el nodo correspondiente a la columna que se esta consultando
******
* Input:
* string linea : Linea 0 de la Matriz (la que contiene los nodos)
* int j : Posicion en la que se encuentra en la columna
* .......
******
* Returns:
* int vertice_id, retorna el valor del nodo respecto a la columna
* int 0, retorna 0 si no encontro un nodo
*****/

float NotFactorial(int n) {
    int menor = n-1;
    int multiplicar = n*menor;
    float retorno = multiplicar/2;
    return retorno;
}
/*****
* float NotFactorial(int n)
******
* Cacula la combinatoria de los N vertices  (n)
*                                           (2)
******
* Input:
* int n : Siendo n la cantidad de vertices de la matriz
* .......
******
* Returns:
* float retorno, Devuelve el resultado de la combinatoria
*****/

//CLASS
class tGrafo{
    private:
        tVertice** matriz;
        int N;
        float SumatoriaArcos;
        string FirstLine;

    public: 

        tGrafo(int n){
            this->N = n; 
            matriz = new tVertice*[n];

            ifstream nodo(MATRIZ_ADYACENCIA);

            string linea;
            getline(nodo , linea , '\n'); //Primera linea

            this->FirstLine = linea;

            int i = 1; // Empieza de la fila 1

            while(nodo.good()){
                string line;
                getline(nodo , line , '\n');

                int x , y;

                stringstream dash(line);

                int j = 0;
                while(dash.good()){
                    string pos;
                    getline(dash , pos , ';');

                    if (pos != ""){
                        if (j == 0){
                            x = stoi(pos);
                        }
                        else{
                            matriz[x] = new tVertice[n];
                            y = Valor_Nodo(FirstLine,j);
                            matriz[x][y] = 0;
                        }
                    }
                    j++;
                }
                i ++;
            }

            nodo.close();
        };
        /*****
        * tGrafo(int n)
        ******
        * Constructor que inicializa el grafo para n vertices creando una matriz[N][N]
        ******
        * Input:
        * int n : n es la cntidad de vertices del grafo
        * .......
        ******
        * Returns:
        * Sin retorno
        *****/

        void AgregarArcos(){
            ifstream Arcos(MATRIZ_ADYACENCIA);
            string Linea;
            getline(Arcos, Linea, '\n'); // Se salta la primera linea
            int cont_arcos = 0;

            int i = 1; //Empieza en la Linea 1
            while(Arcos.good()){
                string boom;
                getline(Arcos, boom, '\n');

                stringstream Line(boom);
                int x , y , peso;

                int j=0;
                while(Line.good()){
                    string node;
                    getline(Line, node , ';');

                    if (node != ""){
                        if (j == 0){
                            x = stoi(node);
                        }
                        else{
                            y = Valor_Nodo(FirstLine,j);
                            peso = stoi(node);
                            if(peso != 0){cont_arcos+=peso;}
                            matriz[x][y] = peso;
                        }
                    }
                    j++;
                }
                i++;
            }
            this->SumatoriaArcos = cont_arcos;
            Arcos.close();
        };
        /*****
        * void AgregarArcos()
        ******
        * Agrega los Valores de los Arcos que vienen en el archivo csv
        ******
        * Input:
        * No recibe parametros
        * .......
        ******
        * Returns:
        * Sin retorno
        *****/
        
        void setEdge(tVertice v1, tVertice v2, int peso){
            matriz[v1][v2] = peso;
            matriz[v2][v1] = peso;
        };
        /*****
        * void setEdge(tVertice v1, tVertice v2, int peso)
        ******
        * Funcion asigna un peso entre dos vertices  
        ******
        * Input:
        * tVertice v1: vertice 1 al que se creara un arco (asignando un peso)
        tVertice v2: vertice 2 al que se creara un arco (asignando un peso)
        int peso: peso del arco
        * .......
        ******
        * Returns:
        *void sin retorno
        *****/

        tVertice Prota(){
            tVertice id;
            int mayor = 0;

            for (int i = 0 ; i<N ; i++){
                int grado = 0;
                for(int j = 0 ; j<N ; j++){
                    int peso = matriz[i][j];
                    if (peso != 0){
                        grado++;
                    }
                }
                if (grado>mayor){
                    mayor = grado;
                    id = i;
                }
            }

            return id;
        };
        /*****
        * tVertice Prota()
        ******
        * Funcion que calcula el personaje con mayor grado 
        ******
        * Input:
        * no recibe input
        * .......
        ******
        * Returns:
        * tVertice id: id del protagonista
        *****/

        void FloydWarshall(){
            int i, j, k;
            for (i = 0; i < N; i++ ){
                for(j = 0 ; j < N; j++){
                   if(i != j && matriz[i][j] == 0){
                    setEdge(i,j,INFINITO);
                   }
                } 
            }
            for (k = 0; k < N; k++) {
                for (i = 0; i < N; i++) {
                  for (j = 0; j < N; j++) {
                    int a,b,c;
                    a = matriz[i][k];
                    b = matriz[k][j];
                    c = matriz[i][j];
                    if (c > (a + b) && (b != INFINITO) &&(a != INFINITO)){
                       int suma = a+b;
                       setEdge(i,j,suma); 
                    }
                  }    
                }
              }
        };   
        /*****
        * void FloydWarshall()
        ******
        * Funcion que modifica el grafo aplicando floywarshall
        ******
        * Input:
        * no recibe input
        * .......
        ******
        * Returns:
        * void, sin retorno
        *****/

        tVertice Secundario(tVertice Prota){
            tVertice Secundario;
            int mayor=0;
            for (int x = 0 ; x < N ; x++){
                int valor = matriz[Prota][x];
                if (valor > mayor && valor != INFINITO){
                    mayor = valor;
                    Secundario = x;
                }
            }
            return Secundario;
        };
        /*****
        * tVertice Secundario(tVertice Prota)
        ******
        * Funcion que compara cada vertice con respecto al protagonista para encontrar el de camino mas largo
        ******
        * Input:
        * tVertice Prota: vertice del protagonista
        * .......
        ******
        * Returns:
        * tVertice secundario: id del personaje secundario
        *****/

        void averageDistance(){
            int i, j;
          
            int suma = 0;
          
            for (i = 0; i < N; i++ ){
                for(j = 0 ; j < N; j++){
                    if(matriz[i][j] != 0 && matriz[i][j] != INFINITO){
                        suma++;
                    }
                }
            }

            float k = NotFactorial(N);
            float retor = suma / k;

            cout<< "Diametro: " << fixed << setprecision(3) << retor << endl;
        };
        /*****
        * void averageDistance()
        ******
        * Funcion que calcula la distancia promedio promedio tomando en cuenta el camino mas corto in contar los pesos
        ******
        * Input:
        * sin inputs 
        * .......
        ******
        * Returns:
        * void, sin retorno
        *****/ 
         
        void averageWeightedDistance(){
            int i, j;
            int suma = 0;
            for (i = 0; i < N; i++ ){
                for(j = 0 ; j < N; j++){
                    if(matriz[i][j] != 0 && matriz[i][j] != INFINITO){
                        suma += matriz[i][j];
                    }
                }
            }
          
            float retor = suma / SumatoriaArcos;

            cout<< "Diametro (con pesos): " << fixed << setprecision(3) << retor << endl;
        };
        /*****
        * void averageWeightedDistance()
        ******
        * Funcion que calcula la distancia promedio tomando en cuenta el camino mas corto  contando los pesos
        ******
        * Input:
        * sin inputs 
        * .......
        ******
        * Returns:
        * void, sin retorno
        *****/
      
};

//MAIN
int main(){
    int Vertex = N_Vertices();
    tGrafo G(Vertex);

    G.AgregarArcos();

    tVertice Naruto = G.Prota();
    cout<< "Personaje Principal: " << NombreID(Naruto) << endl;
   
    G.FloydWarshall();

    tVertice Kakashi = G.Secundario(Naruto);
    cout<< "Personaje Secundario Mas Relevante: " << NombreID(Kakashi) << endl;
    

    G.averageDistance();
    G.averageWeightedDistance();
    
    return 0;
}