// T A R E A  1  - I N F 1 3 4 //

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// S T R U C T S //

struct Ticket {
  char rut_funcionario[10];
  int day_of_month;
  char time[6];
};

struct Formato {
  string comida;
  int ticket_diario;
  int ticket_mensual;
  string hora_inicio;
  string hora_termino;
};

struct Imprimir {
  string rut_funcionario;
  int ticket_validos = 0;
  int ticket_invalidos = 0;
  int ticket_totales_emitidos = 0;
};

struct Mes {
  int day;
  string cadena_comida;
};

struct Datos {
  string rut;
  Mes Dia_mes[31];
};

// F U N C I O N E S //

int Cantidad_Rut(int m, Ticket Datos_tickets[]) {
  string Cadena_rut;
  int r = 0; // r = Cantidad ruts

  for (int i = 0; i < m; i++) {
    if (i == 0) {
      Cadena_rut = Cadena_rut + Datos_tickets[i].rut_funcionario + " ";
      r++;
    } else if ((Cadena_rut.find(Datos_tickets[i].rut_funcionario) >= 0) &&
               (Cadena_rut.find(Datos_tickets[i].rut_funcionario) <=
                Cadena_rut.length())) {
    } else {
      Cadena_rut = Cadena_rut + Datos_tickets[i].rut_funcionario + " ";
      r++;
    }
  }

  return r;
}

/*****
 * int Cantidad_Rut
 ******
 * Cantidad_Rut -> Esta funcion contabiliza los ruts (sin repetirse) que tenemos
 *en Datos_Tickets[m] almacenados.
 ******
 * Input:
 * int m : Siendo m la cantidad de Tickets emitidos.
 * Ticket Datos_tickets[] : Datos_Tickets tiene los datos extraidos del arhcivo
 *binario, donde se especifica el rut_funcionario, day_of_month y time, de cada
 *ticket emitido.
 * .......
 ******
 * Returns:
 * int r, Siendo r la cantidad de ruts (sin repetirse) en forma de entero.
 *****/

string Cadena(int m, Ticket Datos_tickets[]) {
  string Cadena_rut;

  for (int i = 0; i < m; i++) {
    if (i == 0) {
      Cadena_rut = Cadena_rut + Datos_tickets[i].rut_funcionario + " ";
    } else if ((Cadena_rut.find(Datos_tickets[i].rut_funcionario) >= 0) &&
               (Cadena_rut.find(Datos_tickets[i].rut_funcionario) <=
                Cadena_rut.length())) {
    } else {
      Cadena_rut = Cadena_rut + Datos_tickets[i].rut_funcionario + " ";
    }
  }

  return Cadena_rut;
}

/*****
 * string Cadena
 ******
 * Cadena -> Esta funcion busca generar una cadena de string con los rut sin
 *repetirse de los funcioanrios.
 ******
 * Input:
 * int m : Siendo m la cantidad de Tickets emitidos.
 * Ticket Datos_tickets[] : Datos_Tickets tiene los datos extraidos del arhcivo
 *binario, donde se especifica el rut_funcionario, day_of_month y time, de cada
 *ticket emitido.
 * .......
 ******
 * Returns:
 * string Cadena_rut, Siendo Cadena_rut una cadena de string con los ruts (sin
 *repetirse) de los funcionarios.
 *****/

string Validar_Hora(string hora, Formato Datos_servicios[], int n) {
  hora.replace(2, 1, ".");
  float time = std::stof(hora);
  time = time;

  string comida, hora_i, hora_f;

  for (int i = 0; i < n; i++) {
    comida = Datos_servicios[i].comida;

    hora_i = Datos_servicios[i].hora_inicio;
    hora_i.replace(2, 1, ".");
    float time_i = std::stof(hora_i);

    hora_f = Datos_servicios[i].hora_termino;
    hora_f.replace(2, 1, ".");
    float time_f = std::stof(hora_f);

    if (time_i > time_f) {
      if (time < 5) {
        if ((24 + time) >= time_i && (24 + time) <= time_f + 24) {
          return comida;
        }
      } else if (time_i <= time) {
        return comida;
      }

    } else if (time >= time_i && time <= time_f) {
      return comida;
    }
  }

  string valor = "Invalido";
  return valor;
}

/*****
 * String Validar_Hora
 ******
 * La funcion busca validar la hora en la que el funcionario saco el ticket, con
 *el horario de las comidas establecido en el archivo txt.
 ******
 * Input:
 * string hora : Hora en que el funcionario saco el ticket.
 * Formato contenido[] : llamado a la struct Formato, donde tenemos almacenado
 *los datos de las comidas previstas, como lo son la cantidad de tickets
 *diarios. int n : n representa a la cantidad de comidas previstas.
 * .......
 ******
 * Returns:
 * string comida, Si el ticket que saco el usario es dentro del horario
 *establecido, retorna el nombre de la comida. string valor, Si el ticket que
 *saco el usario es fuera del horario establecido, valor retorna como invalido.
 *****/

string Validar_TicketsDiarios(int n, int r, Formato Datos_servicios[], Datos Funcionario[], string rut, string servicio, int dia) {
  int Tdiario_max; // Tdiario_max = Ticket Diario Maximo de la comida
  int contador =0; // contador = Cantidad de veces que uso el servicio en el dia
  int operacion; // operacion = resta de valores
  string valor;  // valor = String que devolvera el retorno
  string cadena; // cadena = cadena de string que viene del struct Datos    
  string mini;   // mini = cadena reducida

  for (int x = 0; x < n; x++) {
    if (Datos_servicios[x].comida == servicio) {
      Tdiario_max = Datos_servicios[x].ticket_diario;
    }
  }

  for (int i = 0; i < r; i++) {
    if (Funcionario[i].rut == rut) {
      for (int t = 0; t < 31; t++) {
        if (Funcionario[i].Dia_mes[t].day == dia) {
          cadena = Funcionario[i].Dia_mes[t].cadena_comida;
  
          int p = 0; // p = Contador para el ciclo while
          int cad = cadena.length();

          while (p < cad) {
            mini = cadena.substr(p, servicio.length());

            if (mini == servicio) {
              contador += 1;
            }

            p += 1;
          }
        }
      }
    }
  }

  if (Tdiario_max >= contador) {
    valor = "V," + to_string(contador);
    return valor;

  } 
  else if (Tdiario_max < contador) {
    operacion = contador - Tdiario_max;
    valor = "I," + to_string(operacion);
    return valor;
  } 
  return "V,0";
}

/*****
 * string Validar_TicketsDiarios
 ******
 * Validar_TicketsDiarios -> La funcion como su nombre lo dice, busca validar el
 *uso de tickes diarios de un servicio.
 ******
 * Input:
 * int n : n es la cantidad de servicios.
 * int r : r es la cantidad de funcionarios
 * Formato Datos_servicios[] : llamado a la struct Formato Datos_servicios[],
 *donde tenemos almacenado los datos de las comidas previstas, como lo son la
 *cantidad de tickets diarios. Datos Funcionario[] : llamado a la struct Datos
 *Funcionario[], donde tenemos almacenado todos los datos por funcinario, como
 *lo son su rut, dias en los que uso ciertos servicios, etc. string rut : rut
 *del funcionario que se quiere revisar el uso de cierto servicio string
 *servicio : nombre del servicio int dia : dia que se quiere revisar el uso del
 *servicio
 * .......
 ******
 * Returns:
 * string valor, Hay 2 tipos de return valor en la funcion de la forma
 *(I/V,tickets).
 * 1. return ("V",q) -> El retorno es Valido, y la cantidad a sumar en tickets
 *validos es q.
 * 2. return ("I",q) -> El retorno es Invalido, y la cantidad a sumar en tickets
 *validos es q (notar que se hace una operacion para saber dentro de todos los
 *tickes que uso cuales son los validos).
 * 3. return ("V",0) -> 0 no afecta al contador.
 *****/

string Validar_TicketsMensuales(int n, int r, Formato Datos_servicios[],Datos Funcionario[], string rut, string servicio) {
  int Tmensual; // Tdiario_max = Ticket Mensual Maximo de la comida
  int contador =
      0;         // contador = Cantidad de veces que uso el servicio en el mes
  int operacion; // operacion = resta de valores
  int p = 0;     // p = Contador para el ciclo while
  string valor;  // valor = String que devolvera el retorno
  string cadena; // cadena = cadena de string que viene del struct Datos
                 // Funcionario
  string mini;   // mini = cadena reducida

  for (int x = 0; x < n; x++) {
    if (Datos_servicios[x].comida == servicio) {
      Tmensual = Datos_servicios[x].ticket_mensual;
    }
  }

  for (int i = 0; i < r; i++) {
    if (Funcionario[i].rut == rut) {
      for (int t = 0; t < 31; t++) {
        cadena = Funcionario[i].Dia_mes[t].cadena_comida;

        int cad = cadena.length();
        while (p < cad) {
          mini = cadena.substr(p, servicio.length());

          if (mini == servicio) {
            contador += 1;
          }
          p += servicio.length();
        }
      }
    }
  }

  if (Tmensual >= contador) {
    valor = "No";
    return valor;
  } else if (Tmensual < contador) {
    operacion = contador - Tmensual;
    valor = "I," + to_string(operacion);
    return valor;
  } else {
    valor = "No";
    return valor;
  }
}

/*****
 * string Validar_TicketsMensuales
 ******
 * Validar_TicketsMensuales -> La funcion como su nombre lo dice, busca validar
 *el uso de tickes diarios de un servicio.
 ******
 * Input:
 * int n : n es la cantidad de servicios.
 * int r : r es la cantidad de funcionarios
 * Formato Datos_servicios[] : llamado a la struct Formato Datos_servicios[],
 *donde tenemos almacenado los datos de las comidas previstas, como lo son la
 *cantidad de tickets diarios. Datos Funcionario[] : llamado a la struct Datos
 *Funcionario[], donde tenemos almacenado todos los datos por funcinario, como
 *lo son su rut, dias en los que uso ciertos servicios, etc. string rut : rut
 *del funcionario que se quiere revisar el uso de cierto servicio mensual.
 * string servicio : nombre del servicio
 * .......
 ******
 * Returns:
 * string valor, valor = "No" -> No se hace ningun cambio.
 * string valor, valor = (I,q) -> se suma q como invalido.
 *****/

int MensualesTotales(int r, Imprimir Pantalla[], string rut) {
  int operacion;

  for (int i = 0; i < r; i++) {
    if (rut == Pantalla[i].rut_funcionario) {
      operacion = 100 - Pantalla[i].ticket_validos;
      return operacion;
    }
  }

  return 1;
}

/*****
 * int MensualesTotales
 ******
 * MensualesTotales -> Esta funcion hace una operacion sencilla, la cual es que
 *al 100 siempre se le restan los tickets totales emitidos.
 ******
 * Input:
 * int r : Cantidad de Rut sin repetir
 * Imprimir Pantalla[] : Struct con todos los datos almacenados de tickets
 *(validos, invalidos) por funcionario. string rut : Rut del Funcionario que se
 *quiere evaluar.
 * .......
 ******
 * Returns:
 * int operacion, Si es operacion es negativo significa que el funcionario
 *sobrepaso los tickets mensuales totales.
 *****/

// M A I N //

int main() {
  ifstream archivotxt;
  archivotxt.open("servicios.txt");

  int n; // n = Cantidad de servicios
  archivotxt >> n;

  Formato Datos_servicios[n];

  for (int i = 0; i < n; i++) {
    archivotxt >> Datos_servicios[i].comida;
    archivotxt >> Datos_servicios[i].ticket_diario;
    archivotxt >> Datos_servicios[i].ticket_mensual;
    archivotxt >> Datos_servicios[i].hora_inicio;
    archivotxt >> Datos_servicios[i].hora_termino;
  }

  archivotxt.close();

  ifstream archivobinario;
  archivobinario.open("tickets.dat", ios::binary);

  int m; // m = Numero de Tickets
  archivobinario.read((char *)&m, sizeof(int));

  Ticket Datos_tickets[m];

  archivobinario.read((char *)Datos_tickets, m * sizeof(Ticket));

  archivobinario.close();

  int r = Cantidad_Rut(m, Datos_tickets); // r = Cantidad de Rut de Funcionarios

  Datos Funcionario[r];

  Imprimir Pantalla[r];

  string cadena_rut = Cadena(
      m, Datos_tickets); // cadena_rut = Cadena de rut_funcionario sin repetirse

  string mini; // mini = cadena_rut recortada

  int f = 0; // t = Contador ciclo while // f = Contador para ingresar al struct
             // Datos
  int x = 0, y = 9; // x = Inicio Rut // y = Donde finaliza el Rut

  // Ingresar Rut a Funcionario[r] y a Pantalla[r]
  int cad_rut = cadena_rut.length();
  while (x < cad_rut) {
    mini = cadena_rut.substr(x, 9);
    x = y + 1;
    y += 10;

    Funcionario[f].rut = mini;
    Pantalla[f].rut_funcionario = mini;
    f++;
  }

  int d = 0; // d = Dia del Mes

  // Ingresar Dias del Mes para cada funcionario.
  for (int i = 0; i < r; i++) {
    for (int t = 0; t < 31; t++) {
      d = t + 1;
      Funcionario[i].Dia_mes[t].day = d;
    }
  }

  string hora, rut_c, valor; // hora = Hora en el que se retiro el Ticket // rut_c = Rut Ciclo // valor = Tendra almacenada el valor que devuelva la funcion.
  int day, day_c; // day = Dia del retiro del Ticket // day_c = Dia Ciclo

  // Ingreso Uso de ticket por funcionario.
  for (int x = 0; x < m; x++) {
    string rut(Datos_tickets[x].rut_funcionario);
    day = Datos_tickets[x].day_of_month;
    hora = string(Datos_tickets[x].time);

    for (int i = 0; i < r; i++) {
      rut_c = Funcionario[i].rut;

      if (rut == rut_c) {
        for (int z = 0; z < 31; z++) {
          day_c = Funcionario[i].Dia_mes[z].day;

          if (day == day_c) {
            valor = Validar_Hora(hora, Datos_servicios, n);
          
            if (valor != "Invalido") {
              valor += "/";
              Funcionario[i].Dia_mes[z].cadena_comida += valor;

              for (int t = 0; t < r; t++) {
                if (rut_c == Pantalla[t].rut_funcionario) {
                  Pantalla[t].ticket_totales_emitidos += 1;
                }
              }
            }

            else {
              for (int t = 0; t < r; t++) {
                if (rut_c == Pantalla[t].rut_funcionario) {
                  Pantalla[t].ticket_totales_emitidos += 1;
                  Pantalla[t].ticket_invalidos += 1;
                }
              }
            }
          }
        }
      }
    }
  }

  string rut_d, servicio, retorno, iov;
  int dia_d, ticket_numero;

  // Ticket Diarios Validos
  for (int x = 0; x < r; x++) {
    rut_d = Funcionario[x].rut;
    for (int i = 0; i < n; i++) {
      servicio = Datos_servicios[i].comida;
      for (int z = 0; z < 31; z++) {
        dia_d = Funcionario[x].Dia_mes[z].day;

        retorno = Validar_TicketsDiarios(n, r, Datos_servicios, Funcionario, rut_d, servicio, dia_d);
        iov = retorno.substr(0, 1);
        string k = retorno.substr(2, retorno.length());
        ticket_numero = stoi(k);
        if (iov == "V") {
          if (ticket_numero != 0) {
            for (int p = 0; p < r; p++) {
              if (Pantalla[p].rut_funcionario == rut_d) {
                  Pantalla[p].ticket_validos += ticket_numero;
      
              }
            }
          }

        } 
        else {
          for (int p = 0; p < r; p++) {
            if (Pantalla[p].rut_funcionario == rut_d) {
              Pantalla[p].ticket_validos += ticket_numero;
            }
          }
        }
      }
    }
  }

  // Ticket Mensuales Invalidos
  for (int x = 0; x < r; x++) {
    rut_d = Funcionario[x].rut;
    for (int i = 0; i < n; i++) {
      servicio = Datos_servicios[i].comida;
      retorno = Validar_TicketsMensuales(n, r, Datos_servicios, Funcionario, rut_d, servicio);
      cout <<retorno.substr(2, retorno.length());
      iov = retorno.substr(0, 1);
      if(retorno.substr(2, retorno.length()) != "" ){
        ticket_numero = stoi(retorno.substr(2, retorno.length()));
        }

      if (iov == "I") {
        if (ticket_numero != 0) {
          for (int p = 0; p < r; p++) {
            if (Pantalla[p].rut_funcionario == rut_d) {
              Pantalla[p].ticket_invalidos += ticket_numero;
              Pantalla[p].ticket_totales_emitidos += ticket_numero;
            }
          }
        }
      }
    }
  }

  string rut_f;
  int resultado;

  // Ticket Mensuales Totales
  for (int x = 0; x < r; x++) {
    rut_f = Pantalla[x].rut_funcionario;
    resultado = MensualesTotales(r, Pantalla, rut_f);

    if (resultado < 0) {
      Pantalla[x].ticket_invalidos += (resultado * -1);
      Pantalla[x].ticket_totales_emitidos += (resultado * -1);
    }
  }

  // Imprimir Por Pantalla
  for (int x = 0; x < r; x++) {
    cout << Pantalla[x].rut_funcionario << " " << Pantalla[x].ticket_validos
         << "/" << Pantalla[x].ticket_totales_emitidos << endl;
  }

  return 0;
}
