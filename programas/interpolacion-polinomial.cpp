#include <bits/stdc++.h>
#define endl '\n'
#define endls "\n\n\n"

using namespace std;
typedef pair<double, double> pdd;
const long long minimo = LONG_MIN;

void ImprimeTabla(const vector<pdd> &tablaI) {
  cout << "\n\t\t\t***VALORES: ***" << endl;
  cout << "i\tx_i\tf(x_i)\n" << endl;
  for (int i = 0; i < tablaI.size(); i++) {
    cout << i << "\t" << tablaI[i].first << "\t" << tablaI[i].second << "\n";
  }
}

bool ElementosOrdenados(const vector<pdd> &tablaI) {
  for (int i = 0; i < (int)tablaI.size() - 1; i++)
    if (tablaI[i] > tablaI[i + 1])
      return false;
  return true;
}
void menuPrincipalInterpolacion() {
  cout << " _______________________________________" << endl;
  cout << "|                                       |" << endl;
  cout << "|    Integrantes del equipo             |" << endl;
  cout << "|_______________________________________|" << endl;
  cout << "| Cirilo Huerta Noe Alberto             |" << endl;
  cout << "|                                       |" << endl;
  cout << "| Lopez Vargas Luis Armando             |" << endl;
  cout << "|                                       |" << endl;
  cout << "| Monroy Alarcon Omar Ulises            |" << endl;
  cout << "|                                       |" << endl;
  cout << "| Perez Chavez Christopher Omar         |" << endl;
  cout << "|_______________________________________|" << endl;
  cout << endls;

  cout << " ___________________________________________________________________"
          "____________________________"
       << endl;
  cout << "|                                                                   "
          "                            |"
       << endl;
  cout << "| ¿ Que accion desea realizar?                                      "
          "                            |"
       << endl;
  cout << "|___________________________________________________________________"
          "____________________________|"
       << endl;
  cout << "|Presione 1 para iniciar el programa.                               "
          "                            |"
       << endl;
  cout << "|Presione 2 para terminar el programa.                              "
          "                            |"
       << endl;
  cout << "|___________________________________________________________________"
          "____________________________|"
       << endl;
}

int main() {
  // puntos en la tabla
  int continuar_programa = 1;

  while (continuar_programa == 1) {
    menuPrincipalInterpolacion();
    cin >> continuar_programa;
    if (continuar_programa != 1)
      break;
    char mismos_datos = 's';
    while (mismos_datos == 's' or mismos_datos == 'S') {
      int n;
      cout << "Ingresa el numero de puntos: ";
      cin >> n;
      if (n < 1) {
        cout << "\t\t\t***ERROR***" << endl;
        cout << "\t\t\tN  debe ser  mayor o igual a 1" << endl;
      }
      vector<pdd> tablaI(n + 1, {0.0, 0.0});

      cout << "\nComienza a ingresar los puntos de la tabla (x_i,f(x_i))"
           << endl;

      // se leen los datos de la tabla
      for (int i = 0; i <= n; i++) {
        cout << "\nX[" << i << "]: ";
        cin >> tablaI[i].first;

        cout << "f(x" << i << "):";
        cin >> tablaI[i].second;
      }
      char datos_correctos = 'n';

      while (datos_correctos == 'n') {
        cout << "Los datos de la tabla son los siguientes: \n";
        ImprimeTabla(tablaI);

        cout << "Los datos son correctos? (s/n): \n";
        cin >> datos_correctos;

        if (datos_correctos == 'n') {
          int fila, columna;
          double valor;
          cout << "Qué dato desea reemplazar?: \n";
          cout << "Ingrese la fila, (en el rango [0," << n << "]): \n";
          cin >> fila;
          cout << "Ingrese la columna, (en el rango [0,1]) : \n";
          cout << "0 Indica modificar el valor de xi en esa fila y 1 modificar "
                  "el valor f(xi) en esa fila:\n";
          cin >> columna;
          cout << "Ingrese el nuevo valor: \n";
          cin >> valor;
          if (columna == 0)
            tablaI[fila].first = valor;
          else
            tablaI[fila].second = valor;
        }
      }
      cout << endl;
      ImprimeTabla(tablaI);

      // ordenamiento de los datos leidos
      if (!ElementosOrdenados(tablaI)) {
        cout << "\nLos elementos no estaban ordenados por lo cual fueron "
                "ordenados\n";
        sort(tablaI.begin(), tablaI.end(), [](pdd a, pdd b) {
          if (a.first == b.first)
            return a.second < b.second;
          return a.first < b.first;
        });
        cout << "\n\tAhora la tabla es la siguiente: " << endl;
        ImprimeTabla(tablaI);
      }
      char misma_tabla = 's';
      while (misma_tabla == 's' or misma_tabla == 'S') {
        // lectura de datos de inrerpolacion.
        double x_interpolacion;
        cout << "\nIngrese el valor de x (punto a interpolar):\n";
        cin >> x_interpolacion;

        // verificacion de que sea un punto que se pueda interpolar con los
        // puntos en la tabla.
        if (x_interpolacion < tablaI[0].first or
            x_interpolacion > tablaI[n].first) {
          cout << "\n\t\t\t***INCORRECTO ***" << endl;
          cout << "\n\t\t\tEl valor de x ingresado para interpolar esta fuera "
                  "del rango de los ";
          cout << "datos de la tabla";
          continue;
        }
        int grado_polinomio;
        cout << "\nIngrese el grado del polinomio que desea obtener:\n";
        cin >> grado_polinomio;

        if (n < grado_polinomio) {
          cout << "\n\t\t\t***INCORRECTO ***" << endl;
          cout << "\n\t\t\tNo hay suficientes puntos para obtener dicho grado "
                  "de polinomio."
               << endl;
          continue;
        }
        // Se comienza a calcular la tabla de diferencias divididas.
        vector<vector<double>> diferencias_divididas(
            n + 1, vector<double>(n + 2, minimo));

        for (int i = 0; i <= n; i++) {
          diferencias_divididas[i][0] = tablaI[i].first;
          diferencias_divididas[i][1] = tablaI[i].second;
        }
        int techo = n;
        int salto = 1;

        for (int i = 2; i <= n + 1; i++) {
          for (int j = 0; j < techo; j++) {
            diferencias_divididas[j][i] =
                (diferencias_divididas[j + 1][i - 1] -
                 diferencias_divididas[j][i - 1]) /
                (tablaI[j + salto].first - tablaI[j].first);
          }
          cout << endl;
          techo--;
          salto++;
        }
        techo = n;
        cout << endls;
        cout << "La tabla de diferencias divididas que se obtiene es: \n\n";
        cout << "x_i\t\tf(x_i)\t\t";
        for (int i = 2; i <= n + 1; i++)
          cout << "f^[" << i - 1 << "]\t\t";
        cout << endl;
        for (int i = 0; i <= n; i++) {
          for (int j = 0; j <= n + 1; j++)
            if (diferencias_divididas[i][j] != minimo)
              printf("%.6f\t", diferencias_divididas[i][j]);
          cout << endl;
        }
        int left = 0;
        int pos = 0;

        for (int i = 0; i < n; i++) {
          if (diferencias_divididas[i][0] <= x_interpolacion and
              diferencias_divididas[i + 1][0] >= x_interpolacion) {
            pos = i;
            break;
          }
        }
        // se busca a partir de que punto se comenzará a extrapolar
        int puntos_necesarios = grado_polinomio + 1;
        int hacia_abajo = n - pos + 1 >= puntos_necesarios
                              ? 0
                              : puntos_necesarios - (n - pos + 1);
        pos -= hacia_abajo;

        cout << "\n\t\t\t*** Se comenzara a extrapolar  a partir de la "
                "posicion: "
             << pos << " ***" << endl;
        double producto = 1.0;
        double resultado = diferencias_divididas[pos][1];

        for (int i = pos, j = 2; i <= pos + puntos_necesarios - 2; i++) {
          producto *= (x_interpolacion - diferencias_divididas[i][0]);
          resultado += (diferencias_divididas[pos][j++] * producto);
        }
        printf("\n\t\t\tEl resultado del polinomio es %.6f", resultado);
        cout << endls;

        cout << "Desea buscar otro valor con la misma tabla?(s/n): " << endl;
        cin >> misma_tabla;
      }
      cout << "Desea cambiar la tabla? (s/n): " << endl;
      cin >> mismos_datos;
    }
  }
  return 0;
}
