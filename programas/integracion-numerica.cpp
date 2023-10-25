#include <bits/stdc++.h>
#define endl "\n"
#define endls "\n\n\n"

using namespace std;
typedef pair<double, double> pdd;

const double eps = 1e-6;

inline double EvaluacionFuncion1(double x) {
  return (pow(x, 4) * (pow(3 + 2 * pow(x, 2), 1.0 / 2.0) / (3.0)));
}

inline double EvaluacionFuncion2(double x) {
  return ((pow(x, 5)) / (pow(pow(x, 2) + 4, 1.0 / 5.0)));
}

vector<pdd> TablaValoresFuncion1(double limite_inferior, double limite_superior,
                                 double subintervalos) {
  double h = (limite_superior - limite_inferior) / subintervalos;
  vector<pdd> valores;

  for (double i = limite_inferior; i <= limite_superior + eps; i += h) {
    double evaluacion = EvaluacionFuncion1(i);
    valores.push_back(make_pair(i, evaluacion));
  }

  return valores;
}

vector<pdd> TablaValoresFuncion2(double limite_inferior, double limite_superior,
                                 double subintervalos) {
  double h = (limite_superior - limite_inferior) / subintervalos;
  vector<pdd> valores;

  for (double i = limite_inferior; i <= limite_superior + eps; i += h) {
    double evaluacion = EvaluacionFuncion2(i);
    valores.push_back(make_pair(i, evaluacion));
  }
  return valores;
}

double ReglaTrapecio(const vector<pdd> &valores, const int &n) {
  double h = valores[1].first - valores[0].first;
  double suma = valores[0].second + valores[n].second;

  for (int i = 1; i < n; i++)
    suma += 2 * (valores[i].second);
  cout << n << endl;
  return (suma * (h / 2));
}

double Simpson13(const vector<pdd> &valores, const int &n) {

  double h = valores[1].first - valores[0].first;
  double suma = valores[0].second + valores[n].second;

  for (int i = 1; i < n; i += 2)
    suma += (4 * valores[i].second);

  for (int i = 2; i < n; i += 2)
    suma += (2 * valores[i].second);

  return (suma * (h / 3.0));
}

double Simpson38(const vector<pdd> &valores, const int &n) {
  double h = valores[1].first - valores[0].first;

  double suma = valores[0].second + valores[n].second;

  for (int i = 1; i < n; i++) {
    suma += (3 * valores[i].second);
    if (!(i % 3))
      suma -= valores[i].second;
  }

  return ((double)((3.0 * h) / 8.0) * (suma));
}

void menuPrincipalIntegracion() {
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

  cout << " __________________________________________________________________"
       << endl;
  cout << "|                                                                  |"
       << endl;
  cout << "|FUNCIONES DE LAS CUALES SE BUSCARA UNA APROXIMACION A SU INTEGRAL |"
       << endl;
  cout << "|__________________________________________________________________|"
       << endl;
  cout << "|                                                                  |"
       << endl;
  cout << "|                  1.- x⁴ * ( sqrt(3+2*x²) /3)                     |"
       << endl;
  cout << "|                  2.- x⁵ /( ( x² + 4) ^ (1/5))                    |"
       << endl;
  cout << "|__________________________________________________________________|"
       << endl;
  cout << endl;

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
  cout << "|Presione 1 para buscar una aproximacion de la integral de una de "
          "las funciones                 |"
       << endl;
  cout << "|Presione 2 para terminar el programa                               "
          "                            |"
       << endl;
  cout << "|___________________________________________________________________"
          "____________________________|"
       << endl;
}
void menuFunciones() {
  cout << endls;
  cout << " ___________________________________________________________________"
          "_________________________________"
       << endl;
  cout << "|                                                                   "
          "                                 |"
       << endl;
  cout << "| ¿ Que accion desea realizar?                                      "
          "                                 |"
       << endl;
  cout << "|___________________________________________________________________"
          "_________________________________|"
       << endl;
  cout << "|Presione 1 para buscar una aproximacion a la integral de la "
          "funcion: x⁴ * ( sqrt(3+2*x²) /3)        |"
       << endl;
  cout << "|Presione 2 para buscar una aproximacion a la integral de la "
          "funcion: x⁵ /( ( x² + 4) ^ (1/5))       |"
       << endl;
  cout << "|Presione 3 para volver al menu principal                           "
          "                                 |"
       << endl;
  cout << "|___________________________________________________________________"
          "_________________________________|"
       << endl;
}
int main() {
  int continuar_programa = 1;

  while (continuar_programa == 1) {
    menuPrincipalIntegracion();
    cin >> continuar_programa;
    if (continuar_programa != 1)
      break;

    int menu_funciones;
    do {
      menuFunciones();
      cin >> menu_funciones;

      if (menu_funciones != 1 and menu_funciones != 2)
        break;

      double intervalos, h, limite_inferior, limite_superior;
      double res = 0.0;

      cout << "Ingresa el limite inferior:  ";
      cin >> limite_inferior;
      cout << "Ingresa el limite superior:  ";
      cin >> limite_superior;
      cout << "Ingresa el numero de intervalos que deseas tener: ";
      cin >> intervalos;
      if (limite_inferior == limite_superior) {
        cout << "\n\t\t\tNo fue necesario aplicar ningun metodo pues si el "
                "limite inferior y superior son iguales";
        cout << "\t\t\tel resultado es 0" << endl;
        cout << "\n\t\t\t***RESULTADO: 0" << endl;
      } else if (limite_inferior > limite_superior) {
        cout << "\n\t\t\t***ERROR***" << endl;
        cout << "\t\t\tEl limite inferior NO puede ser mayor que el limite "
                "superior"
             << endl;
      } else {
        vector<pdd> valores;
        if (menu_funciones == 1)
          valores = TablaValoresFuncion1(limite_inferior, limite_superior,
                                         intervalos);
        else
          valores = TablaValoresFuncion2(limite_inferior, limite_superior,
                                         intervalos);

        int n = valores.size() - 1;

        double resultado = 0.0;
        if (n <= 1) {
          cout << "\nEl valor de 'n' debe ser mayor  a 1" << endl;
          continue;
        } else if (n % 2 == 0) {
          cout << "\n\t\t\t***COMO N ES PAR SOLO SE USARA LA REGLA DE SIMPSON "
                  "1/3***\n\n";
          res = Simpson13(valores, n);
        } else if (n == 3) {
          cout << "\n\t\t\t***SE USARA LA REGLA DE SIMPSON 3/8***\n" << endl;

          res = Simpson38(valores, n);
        } else if (n % 3 == 0) {
          int aux_n = n - 3;
          vector<pdd> simpson1_3(valores.begin(), valores.begin() + aux_n + 1),
              simpson3_8(valores.begin() + aux_n, valores.begin() + n + 1);
          cout << "\n\t\t\t***SE USARA LA REGLA DE SIMPSON 1/3 PARA EL "
                  "INTERVALO [0,"
               << aux_n << "]  Y";
          cout << "\n\t\t\tSE USARA LA REGLA DE SIMPSON 3/8 PARA EL INTERVALO ["
               << aux_n << "," << n << "] ***";
          cout << "\n\t\t\t POR LO TANTO LAS  TABLAS QUEDAN DE LA SIGUIENTE "
                  "MANERA: "
               << endl
               << endl;

          cout << "\tTABLA A EVALUAR CON REGLA DE SIMPSON 1/3" << endl;
          for (int i = 0; i < simpson1_3.size(); i++)
            cout << "\t" << i << "\t" << simpson1_3[i].first << "\t\t"
                 << simpson1_3[i].second << endl;

          cout << endls;
          cout << "\tTABLA A EVALUAR CON REGLA DE SIMPSON 3/8" << endl;
          for (int i = 0; i < simpson3_8.size(); i++)
            cout << "\t" << i << "\t" << simpson3_8[i].first << "\t\t"
                 << simpson3_8[i].second << endl;

          int s1 = simpson1_3.size() - 1;
          int s2 = simpson3_8.size() - 1;

          res += Simpson13(simpson1_3, s1);
          res += Simpson38(simpson3_8, s2);
        } else {
          vector<pdd> simpson1_3(valores.begin() + 3, valores.begin() + n + 1),
              simpson3_8(valores.begin(), valores.begin() + 4);
          cout << "\n\t\t\t***SE USARA LA REGLA DE SIMPSON 3/8 PARA EL "
                  "INTERVALO [0,3]  Y";
          cout << "\n\t\t\tSE USARA LA REGLA DE SIMPSON 1/3 PARA EL INTERVALO "
                  "[3,"
               << n << "] ***";
          cout << "\n\t\t\t POR LO TANTO LAS  TABLAS QUEDAN DE LA SIGUIENTE "
                  "MANERA: "
               << endl
               << endl;

          cout << "\tTABLA A EVALUAR CON REGLA DE SIMPSON 3/8" << endl;
          for (int i = 0; i < simpson3_8.size(); i++)
            cout << "\t" << i << "\t" << simpson3_8[i].first << "\t\t"
                 << simpson3_8[i].second << endl;

          cout << endls;

          cout << "\tTABLA A EVALUAR CON REGLA DE SIMPSON 1/3" << endl;
          for (int i = 0; i < simpson1_3.size(); i++)
            cout << "\t" << i << "\t" << simpson1_3[i].first << "\t\t"
                 << simpson1_3[i].second << endl;

          int s1 = simpson1_3.size() - 1;
          int s2 = simpson3_8.size() - 1;

          res += Simpson13(simpson1_3, s1);
          res += Simpson38(simpson3_8, s2);
        }
        cout << "\n\n\t\t\t*** LA APROXIMACION A LA INTEGRAL DE LA FUNCION "
                "DADA ES: ";
        printf("%.12f", res);
        cout << " *** " << endl;
      }
    } while (menu_funciones == 1 or menu_funciones == 2);
  }
  return 0;
}
