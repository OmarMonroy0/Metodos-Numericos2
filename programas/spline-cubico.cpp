#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define endl '\n'
#define endls "\n\n\n"

using namespace std;

typedef struct point {
  double x;
  double y;
} point;

void factorizacionLU(vector<vector<double>> &matriz, vector<vector<double>> &L,
                     vector<vector<double>> &U) {
  int n = matriz.size();

  // Se inicializa la matriz L como matriz identidad
  // y la matriz U como la copia de la matriz original.

  L = vector<vector<double>>(n, vector<double>(n, 0));
  U = matriz;

  for (int i = 0; i < n; i++) {
    L[i][i] = 1;

    // Proceso de eliminacion
    for (int j = i + 1; j < n; j++) {
      double factor = U[j][i] / U[i][i];

      L[j][i] = factor;

      for (int k = i; k < n; k++)
        U[j][k] -= factor * U[i][k];
    }
  }
}

vector<double> SolucionSistema(const vector<vector<double>> &L,
                               const vector<vector<double>> &U,
                               const vector<double> coeficientes) {
  int n = L.size();

  // se resuelve Ly = b mediante sustituación hacia adelante.
  vector<double> y(n);

  for (int i = 0; i < n; i++) {
    double sum = 0;
    for (int j = 0; j < i; j++)
      sum += L[i][j] * y[j];
    y[i] = (coeficientes[i] - sum) / L[i][i];
  }

  // Resolver Ux = y mediante sustitucion hacia atras
  vector<double> x(n);
  for (int i = n - 1; i >= 0; i--) {
    double sum = 0;

    for (int j = i + 1; j < n; j++)
      sum += U[i][j] * x[j];

    x[i] = (y[i] - sum) / U[i][i];
  }
  return x;
}

void MenuPrincipal() {
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
          "__________"
       << endl;
  cout << "|                                                                   "
          "          |"
       << endl;
  cout << "| ¿ Que accion desea realizar?                                      "
          "          |"
       << endl;
  cout << "|___________________________________________________________________"
          "__________|"
       << endl;
  cout << "|Presione 1 para ingresar nuevos datos y obtener nuevos spline "
          "cúbicos        |"
       << endl;
  cout << "|Presione 2 para terminar el programa                               "
          "          |"
       << endl;
  cout << "|___________________________________________________________________"
          "__________|"
       << endl;
}

int main() {

  int seguir_en_programa = 1;
  while (seguir_en_programa == 1) {
    MenuPrincipal();
    cin >> seguir_en_programa;
    if (seguir_en_programa == 2)
      break;

    int n_puntos;
    vector<point> coordenadas;

    // lectura de datos
    cout << "Ingrese  el valor de 'n', recuerda que tendrás que ingresar n + 1 "
            "puntos: ";
    cin >> n_puntos;
    coordenadas.resize(n_puntos + 1);

    for (int i = 0; i <= n_puntos; i++) {
      point aux;
      cout << "Punto " << i << endl;
      cout << "Coordenada x: ";
      cin >> aux.x;
      cout << "Coordenada y: ";
      cin >> aux.y;
      coordenadas[i] = aux;
    }
    int datos_correctos = 2;

    // validacion de datos correctos.

    while (datos_correctos == 2) {
      cout << "¿Los datos son correctos? " << endl;
      cout << "Presione 1 si son correctos,  2 si desea modficar: ";
      cin >> datos_correctos;

      if (datos_correctos == 2) {
        int position;
        point aux;
        cout << "Ingrese el indice del punto a modificar [0," << n_puntos
             << "]: ";
        cin >> position;

        while (position < 0 or position > n_puntos) {
          cout << "El indice es incorrecto, hazlo de nuevo " << endl;
          cout << "El indice debe ser mayor o igual a 0 y menor o igual a "
               << n_puntos << endl;
          cout << "Ingrese el indice del punto a modificar, [0," << n_puntos
               << "]: ";
          cin >> position;
        }
        cout << "Ingresa la coordenada de x: ";
        cin >> aux.x;
        cout << "Ingresa la coordenada de y: ";
        cin >> aux.y;

        coordenadas[position] = aux;
      }
    }
    // se ordenan los elementos ingresados

    // impresion de datos ingreasados por el usuario.
    cout << endl;
    cout << "LOS DATOS INICIALES SON: " << endl;
    cout << "i"
         << "\t\t"
         << "x_i\t\ty_i" << endl;

    for (int i = 0; i <= n_puntos; i++) {
      cout << i << "\t\t" << coordenadas[i].x << "\t\t" << coordenadas[i].y
           << endl;
    }
    cout << endls;
    // Se comienza a realizar el método del spline cúbico.

    // se calculan los intervalos h y las diferencias divididas.
    vector<double> intervaloH(n_puntos, 0.0);
    vector<double> diferencias(n_puntos, 0.0);

    for (int i = 0; i < n_puntos; i++) {
      intervaloH[i] = coordenadas[i + 1].x - coordenadas[i].x;
      diferencias[i] =
          (coordenadas[i + 1].y - coordenadas[i].y) * (1 / intervaloH[i]);
    }

    // impresion de las hi y las diferencias divididas
    cout << "\t\t\t***H_i y DIFERENCIAS***" << endl;
    cout << "i\t\th_i\t\tdiferencias" << endl;
    for (int i = 0; i < n_puntos; i++) {
      cout << i << "\t\t" << intervaloH[i] << "\t\t" << diferencias[i] << endl;
    }
    cout << endls;
    // Se calcula el sistema.
    vector<vector<double>> sistema(n_puntos, vector<double>(n_puntos + 1, 0.0));
    vector<double> coeficientes_sistema(n_puntos);

    for (int i = 1; i < n_puntos; i++) {
      sistema[i][i - 1] = intervaloH[i - 1];
      sistema[i][i] = 2 * (intervaloH[i - 1] + intervaloH[i]);
      sistema[i][i + 1] = intervaloH[i];

      // Ax = b <- buscamos la b
      // se calcula el vector de coeficientes.
      coeficientes_sistema[i] = 6 * (diferencias[i] - diferencias[i - 1]);
    }

    // Se obtienen los coeficientes solucion del sistema
    vector<vector<double>> matriz_sistema(n_puntos - 1,
                                          vector<double>(n_puntos - 1, 0.0));

    vector<double> coeficientes_matriz(n_puntos - 1, 0.0);

    for (int i = 1; i <= n_puntos - 1; i++)
      for (int j = 1; j <= n_puntos - 1; j++)
        matriz_sistema[i - 1][j - 1] = sistema[i][j];

    for (int i = 1; i <= n_puntos - 1; i++)
      coeficientes_matriz[i - 1] = coeficientes_sistema[i];

    // Se implementa la solucion del sistema mediante
    // la factorizacion LU

    vector<vector<double>> L, U;

    // Se llama a la funcion que creará las matrices LOWER y UPPER para resovler
    // el sistema
    factorizacionLU(matriz_sistema, L, U);

    // Se llama a la funcion que resolvera el sistema.
    vector<double> solucion = SolucionSistema(L, U, coeficientes_matriz);

    vector<double> soluciones(solucion.size() + 2, 0.0);

    for (int i = 1; i <= solucion.size(); i++)
      soluciones[i] = solucion[i - 1];

    // Se calculan los coeficientes para los n - 1 polinomios
    vector<double> a(n_puntos), b(n_puntos), c(n_puntos), d(n_puntos);
    cout << endls;

    // Se imprimen las soluciones del sistema
    cout << "\t\t\t***SOLUCIONES DEL SISTEMA OBTENIDO***" << endl;
    for (int i = 0; i <= n_puntos; i++)
      cout << "S_" << i << " = " << soluciones[i] << endl;
    cout << endls;

    for (int i = 0; i < n_puntos; i++) {
      a[i] = (soluciones[i + 1] - soluciones[i]) / (6 * intervaloH[i]);
      b[i] = soluciones[i] / 2.0;
      c[i] = diferencias[i] -
             ((soluciones[i + 1] + 2 * soluciones[i]) / 6.0) * intervaloH[i];
      d[i] = coordenadas[i].y;
    }
    // impresion de polinomios

    cout << "\t\t\t***POLINOMIOS RESULTANTES\t\t\tINTERVALOS***" << endl;
    for (int i = 0; i < n_puntos; i++) {
      bool band_a = false, band_b = false, band_c = false, band_d = false;

      cout << "P_" << i << "( x ) = ";
      if (a[i] != 0) {
        printf("%.8f", a[i]);
        cout << "(x-" << coordenadas[i].x << ")³ ";
        band_a = true;
      }
      if (!band_a)
        cout << "\t";
      if (b[i] != 0) {
        if (b[i] > 0 && (band_a == true))
          cout << "+ ";
        printf("%.8f", b[i]);
        cout << "(x-" << coordenadas[i].x << ")² ";
        band_b = true;
      }
      if (!band_b)
        cout << "\t";

      if (c[i] != 0) {
        if (c[i] > 0 and (band_a == true or band_c == true))
          cout << "+ ";
        band_c = true;
      }
      if (!band_c)
        cout << "\t";

      printf("%.8f", c[i]);
      cout << "(x-" << coordenadas[i].x << ") ";
      if (d[i] != 0) {
        if (d[i] > 0 and (band_a == true or band_b == true or band_c == true))
          cout << "+ ";
        printf("%.8f", d[i]);
        band_d = true;
      }
      if (!band_d)
        cout << "\t";

      cout << ",\t\t\t" << coordenadas[i].x
           << " <= x <= " << coordenadas[i + 1].x << endl;
      cout << endl;
    }
  }
  return 0;
}