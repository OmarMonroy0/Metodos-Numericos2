#include<bits/stdc++.h>
#define endl '\n'
#define endls "\n\n\n"

using namespace std;

typedef pair<double,double> pdd;
const long  long  minimo = LONG_MIN;
const double eps = 1e-6;


typedef struct tabla {
	int iteracion;
	vector< vector< double > > x;
	vector< vector<double> > matriz_jacobiana;
	vector< vector<double> > matriz_inversa;
	vector< vector<double> > evaluacion;
	vector< vector<double> > operacion;
	double error_relativo;
	double error_absoluto;
} tabla;

typedef struct point{
	double x;
	double y;
}point;


// Se hara el calculo del determinante para verificar si
// la matriz tiene inversa
// Si el determinante es igual a 0 no tiene matriz inversa

double TieneInversa(const vector< vector<double> > &matriz) {
	if (matriz.size() == 2) {
		return (matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0]);
	} else {
		return (matriz[0][0] *
				(matriz[1][1] * matriz[2][2] - matriz[2][1] * matriz[1][2]) -
				matriz[0][1] *
				(matriz[1][0] * matriz[2][2] - matriz[2][0] * matriz[1][2]) +
				matriz[0][2] *
				(matriz[1][0] * matriz[2][1] - matriz[2][0] * matriz[1][1]));
	}
}

// Obtenemos la matriz transpuesta
vector< vector<double> > Transpuesta(const vector< vector<double> > &matriz) {
	vector< vector<double> > transpuesta(matriz.size(),
			vector<double>(matriz.size(), 0));

	for (int i = 0; i < matriz.size(); i++) {
		for (int j = 0; j < matriz.size(); j++) {
			transpuesta[j][i] = matriz[i][j];
		}
	}
	return transpuesta;
}

// Se obtiene la matriz Adjunta
vector< vector<double> > Adjunta(const vector< vector<double> > &matriz) {
	int signos[][3] = {{1, -1, 1}, {-1, 1, -1}, {1, -1, 1}};
	vector< vector<double> > adjunta(matriz.size(),
			vector<double>(matriz.size(), 0));

	adjunta[0][0] = signos[0][0] *
		(matriz[1][1] * matriz[2][2] - matriz[2][1] * matriz[1][2]);
	adjunta[0][1] = signos[0][1] *
		(matriz[1][0] * matriz[2][2] - matriz[2][0] * matriz[1][2]);
	adjunta[0][2] = signos[0][2] *
		(matriz[1][0] * matriz[2][1] - matriz[2][0] * matriz[1][1]);
	adjunta[1][0] = signos[1][0] *
		(matriz[0][1] * matriz[2][2] - matriz[2][1] * matriz[0][2]);
	adjunta[1][1] = signos[1][1] *
		(matriz[0][0] * matriz[2][2] - matriz[2][0] * matriz[0][2]);

	adjunta[1][2] = signos[1][2] *
		(matriz[0][0] * matriz[2][1] - matriz[2][0] * matriz[0][1]);

	adjunta[2][0] = signos[2][0] *
		(matriz[0][1] * matriz[1][2] - matriz[1][1] * matriz[0][2]);
	adjunta[2][1] = signos[2][1] *
		(matriz[0][0] * matriz[1][2] - matriz[1][0] * matriz[0][2]);
	adjunta[2][2] = signos[2][2] *
		(matriz[0][0] * matriz[1][1] - matriz[1][0] * matriz[0][1]);

	return adjunta;
}
// funcion para encontrar la inversa de una matriz
vector< vector<double> > Inversa(const vector< vector<double> > &matriz) {
	vector< vector<double> > inversa(matriz.size(),
			vector<double>(matriz.size(), 0));
	double determinante = TieneInversa(matriz);
	vector< vector<double> > transpuesta = Transpuesta(matriz);
	vector< vector<double> > adjunta(matriz.size(),
			vector<double>(matriz.size(), 0));

	if (matriz.size() == 2) {
		adjunta[0][0] = transpuesta[1][1];
		adjunta[0][1] = transpuesta[1][0] * (-1);
		adjunta[1][0] = transpuesta[0][1] * (-1);
		adjunta[1][1] = transpuesta[0][0];
	} else {
		adjunta = Adjunta(transpuesta);
	}
	for (int i = 0; i < matriz.size(); i++) {
		for (int j = 0; j < matriz.size(); j++) {
			inversa[i][j] = adjunta[i][j] / (double)determinante;
		}
	}
	return inversa;
}

// Evaluacion de las funciones en el punto inicial dado
// F(x^0)
inline double EvaluacionEcuacionUnoSistemaUno(double x, double y) {
	return (x * x + x * y - 10);
}

inline double EvaluacionEcuacionDosSistemaUno(double x, double y) {
	return (y + 3 * x * y * y - 50);
}

inline double EvaluacionEcuacionUnoSistemaDos(double x, double y) {
	return (x * x + y * y - 9);
}

inline double EvaluacionEcuacionDosSistemaDos(double x, double y) {
	return ((-1) * exp(x) - 2 * y - 3);
}

inline double EvaluacionEcuacionUnoSistemaTres(double x, double y, double z) {
	return (2 * x * x - 4 * x + y * y + 3 * z * z + 6 * z + 2);
}

inline double EvaluacionEcuacionDosSistemaTres(double x, double y, double z) {
	return (x * x + y * y - 2 * y + 2 * z * z - 5);
}

inline double EvaluacionEcuacionTresSistemaTres(double x, double y, double z) {
	return (3 * x * x - 12 * x + y * y - 3 * z * z + 8);
}

inline double EvaluacionEcuacionUnoSistemaCuatro(double x, double y) {
	return (x * x - 4 * x + y * y);
}

inline double EvaluacionEcuacionDosSistemaCuatro(double x, double y) {
	return (x * x - x - 12 * y + 1);
}

inline double EvaluacionEcuacionTresSistemaCuatro(double x, double y,
		double z) {
	return (3 * x * x - 12 * x + y * y - 3 * z * z + 8);
}

// EVALUACION DE LAS DERIVADAS
// PRIMER SISTEMA
inline double EvaluacionDerivadaEcuacionUnoSistemaUnoX(double x, double y) {
	return (2 * x + y);
}

inline double EvaluacionDerivadaEcuacionUnoSistemaUnoY(double x) { return x; }

inline double EvaluacionDerivadaEcuacionDosSistemaUnoX(double y) {
	return (3 * y * y);
}

inline double EvaluacionDerivadaEcuacionDosSistemaUnoY(double x, double y) {
	return (1 + 6 * x * y);
}

// SEGUNDO SISTEMA
inline double EvaluacionDerivadaEcuacionUnoSistemaDosX(double x) {
	return (2 * x);
}

inline double EvaluacionDerivadaEcuacionUnoSistemaDosY(double y) {
	return (2 * y);
}

inline double EvaluacionDerivadaEcuacionDosSistemaDosX(double x) {
	return ((-1) * exp(x));
}
inline double EvaluacionDerivadaEcuacionDosSistemaDosY() { return (-2); }

// DERIVADAS SISTEMA 3
inline double EvaluacionDerivadaEcuacionUnoSistemaTresX(double x) {
	return (4 * x - 4);
}

inline double EvaluacionDerivadaEcuacionUnoSistemaTresY(double y) {
	return (2 * y);
}
inline double EvaluacionDerivadaEcuacionUnoSistemaTresZ(double z) {
	return (6 * z + 6);
}

inline double EvaluacionDerivadaEcuacionDosSistemaTresX(double x) {
	return (2 * x);
}

inline double EvaluacionDerivadaEcuacionDosSistemaTresY(double y) {
	return (2 * y - 2);
}

inline double EvaluacionDerivadaEcuacionDosSistemaTresZ(double z) {
	return (4 * z);
}

inline double EvaluacionDerivadaEcuacionTresSistemaTresX(double x) {
	return (6 * x - 12);
}

inline double EvaluacionDerivadaEcuacionTresSistemaTresY(double y) {
	return (2 * y);
}

inline double EvaluacionDerivadaEcuacionTresSistemaTresZ(double z) {
	return ((-6) * z);
}

// EVALUACION DE DERIVADAS DEL CUARTO SISTEMA
inline double EvaluacionDerivadaEcuacionUnoSistemaCuatroX(double x) {
	return (2 * x - 4);
}

inline double EvaluacionDerivadaEcuacionUnoSistemaCuatroY(double y) {
	return (2 * y);
}

inline double EvaluacionDerivadaEcuacionUnoSistemaCuatroZ() { return 0; }

inline double EvaluacionDerivadaEcuacionDosSistemaCuatroX(double x) {
	return (2 * x - 1);
}

inline double EvaluacionDerivadaEcuacionDosSistemaCuatroY() { return -12; }

inline double EvaluacionDerivadaEcuacionDosSistemaCuatroZ() { return 0; }

inline double EvaluacionDerivadaEcuacionTresSistemaCuatroX(double x) {
	return (6 * x - 12);
}
inline double EvaluacionDerivadaEcuacionTresSistemaCuatroY(double y) {
	return 2 * y;
}
inline double EvaluacionDerivadaEcuacionTresSistemaCuatroZ(double z) {
	return (-6 * z);
}

void MenuPrincipalNewton() {
	cout << " ____________________________________________________________" << endl;
	cout << "|                                                            |" << endl;
	cout << "| ¿ Que accion desea realizar?                               |" << endl;
	cout << "|Presione 1 para ir al menu de sistemas.                     |" << endl;
	cout << "|Presione 2 para terminar con el metodo de Newton.           |" << endl;
	cout << "|____________________________________________________________|" << endl;
}

void MenuSistemas() {
	cout << "  ______________________________________________________________" << endl;   
	cout << " |                                                              |" << endl;	
	cout << " | Ingrese el sistema del cual busca solucion                   |" << endl;
	cout << " | Las opciones de sistemas son las siguientes                  |" << endl;
	cout << " |                                                              |" << endl;	
	cout << " | Opcion 1:                                                    |" << endl;
	cout << " |          f(x,y) =  x²  + xy-10 = 0                           |" << endl;
	cout << " |          f(x,y) =  y + 3xy²-50  = 0                          |" << endl;
	cout << " |______________________________________________________________|" << endl;
	cout << " | Opcion 2:                                                    |" << endl;
	cout << " |          f(x,y) = x²+y²-9 = 0                                |" << endl;
	cout << " |          f(x,y) = -e^x - 2y - 3 = 0                          |" << endl;
	cout << " |______________________________________________________________|" << endl;
	cout << " | Opcion 3:                                                    |" << endl;
	cout << " |          f(x,y,z) = 2x² - 4x + y² + 3z² + 6z  + 2 = 0        |" << endl;
	cout << " |          f(x,y,z) = x² + y² - 2y + 2z² - 5 = 0               |" << endl;
	cout << " |          f(x,y,z) = 3x²-12x+y²-3z² + 8 = 0                   |"<< endl;
	cout << " |______________________________________________________________|"<< endl;
	cout << " | Opcion 4:                                                    |"<< endl;
	cout << " |          f(x,y,z) = x² - 4x + y²  = 0                        |"<< endl;
	cout << " |          f(x,y,z) = x² - x  - 12y + 1  = 0                   |"<< endl;
	cout << " |          f(x,y,z) = 3x²-12x+y²-3z² + 8 = 0                   |"<< endl;
	cout << " |______________________________________________________________|"<< endl;
	cout << " |                                                              |"<< endl;
	cout << " |  Ingrese 1 Para la opcion 1.                                 |"<< endl;
	cout << " |  Ingrese 2 Para la opcion 2.                                 |" << endl;
	cout << " |  Ingrese 3 Para la opcion 3.                                 |" << endl;
	cout << " |  Ingrese 4 Para la opcion 4.                                 |" << endl;
	cout << " |                                                              |" << endl;
	cout << " |                                                              |" << endl;
	cout << " | INGRESE  5 PARA REGRESAR AL MENU PRINCIPAL DEL METODO        |" << endl;			
	cout << " |______________________________________________________________|" << endl;
}

// Funcion que multiplica dos matrices
vector< vector<double> > MultiplicacionMatrices(const vector< vector<double> > &matriz1,
		const vector< vector<double> > &matriz2) {
	vector< vector<double> > matriz_m(matriz1.size(),
			vector<double>(matriz2[0].size()));
	for (int i = 0; i < matriz1.size(); i++) {
		for (int j = 0; j < matriz2[0].size(); j++) {
			for (int k = 0; k < matriz2.size(); k++) {
				matriz_m[i][j] += matriz1[i][k] * matriz2[k][j];
			}
		}
	}
	return matriz_m;
}
// funcion que imprime las iteraciones obtenidas
void ImprimeResultados(const vector<tabla> &resultado) {
	for (int i = 0; i < resultado.size(); i++) {

		cout << "Iteracion:  " << endl;
		cout << resultado[i].iteracion << endl << endl;

		cout << " x ^ 0 :" << endl;
		for (int j = 0; j < resultado[i].x.size(); j++)
			cout << resultado[i].x[j][0] << "     ";
		cout << endl << endl;

		cout << "Matriz Jacobiana: " << endl;
		for (int j = 0; j < resultado[i].matriz_jacobiana.size(); j++) {
			for (int k = 0; k < resultado[i].matriz_jacobiana.size(); k++)
				cout << resultado[i].matriz_jacobiana[j][k] << "    ";
			cout << endl;
		}
		cout << endl;

		cout << "Matriz Jacobiana Inversa: " << endl;
		for (int j = 0; j < resultado[i].matriz_inversa.size(); j++) {
			for (int k = 0; k < resultado[i].matriz_inversa.size(); k++)
				cout << resultado[i].matriz_inversa[j][k] << "    ";
			cout << endl;
		}
		cout << endl;
		cout << " F(x^k) :" << endl;
		for (int j = 0; j < resultado[i].evaluacion.size(); j++)
			cout << resultado[i].evaluacion[j][0] << "    ";

		cout << endl << endl;
		cout << " X^k - J(x^k)^1*F(x^k): " << endl;
		for (int j = 0; j < resultado[i].operacion.size(); j++)
			cout << resultado[i].operacion[j][0] << "     ";

		cout << endl << endl;
		cout << "Error absoluto: " << endl;
		cout << resultado[i].error_absoluto << endl;
		cout << endl;
		cout << "Error Relativo: " << endl;
		cout << resultado[i].error_relativo << endl;

		cout << "--------------------------------------------" << endl << endl;
	}
}
void MenuCambioDatos() {
	cout << " ______________________________________________________________________________________"  << endl;
	cout << "|	                                                                                |" << endl;
	cout << "|Pesiona 1 si Deseas seguir con el mismo sistema, solo cambiando los valores iniciales |" << endl; 
	cout << "|Presiona 2 si deseas regresar al menu de Sistemas                                     |" << endl;
	cout << "|______________________________________________________________________________________|" << endl;
}

void MostrarResultados(const vector< vector<double> > &resultados) {

	cout << "\t\tLos resultados obtenidos con el sistema son los siguientes: "
		<< endl;
	cout << "\t\t x = "; printf("%.8f", resultados[0][0]); cout  << endl;
	cout << "\t\t y = " ; printf("%.8f", resultados[1][0]); cout << endl;
	if (resultados.size() == 3){
		cout << "\t\t z = "; printf("%.8f", resultados[2][0]); cout  << endl;
	}
}
// funcion que calcula las iteraciones del sistema 1
void Sistema1() {
	double x, y;
	double numero_iteraciones;
	double tolerancia;

	cout << "Ingrese el valor inicial de x: ";
	cin >> x;
	cout << "Ingresa el valor inicial de y: ";
	cin >> y;
	cout << "Ingrese el numero maximo de iteraciones: ";
	cin >> numero_iteraciones;
	cout << "Ingresa la tolerancia: ";
	cin >> tolerancia;

	vector<tabla> soluciones;
	tabla Iteracion;

	// Valores iniciales
	Iteracion.iteracion = 0;
	Iteracion.x.resize(2);

	for (int i = 0; i < 2; i++)
		Iteracion.x[i].resize(1);
	Iteracion.x[0][0] = x;
	Iteracion.x[1][0] = y;

	// Valores para la matriz jacobiana
	Iteracion.matriz_jacobiana.resize(2);
	for (int i = 0; i < 2; i++) {
		Iteracion.matriz_jacobiana[i].resize(2);
	}
	Iteracion.matriz_jacobiana[0][0] =
		EvaluacionDerivadaEcuacionUnoSistemaUnoX(x, y);
	Iteracion.matriz_jacobiana[0][1] =
		EvaluacionDerivadaEcuacionUnoSistemaUnoY(x);
	Iteracion.matriz_jacobiana[1][0] =
		EvaluacionDerivadaEcuacionDosSistemaUnoX(y);
	Iteracion.matriz_jacobiana[1][1] =
		EvaluacionDerivadaEcuacionDosSistemaUnoY(x, y);

	// Se llama  a la matriz jacobiana inversa

	Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);

	// Se evaluan los puntos iniciales en las funciones dadas

	Iteracion.evaluacion.resize(2);
	for (int i = 0; i < 2; i++)
		Iteracion.evaluacion[i].resize(1);
	Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaUno(x, y);
	Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaUno(x, y);

	vector< vector<double> > m_matrices =
		MultiplicacionMatrices(Iteracion.matriz_inversa, Iteracion.evaluacion);

	Iteracion.operacion.resize(2);
	for (int i = 0; i < 2; i++)
		Iteracion.operacion[i].resize(1);

	Iteracion.operacion[0][0] = x - m_matrices[0][0];
	Iteracion.operacion[1][0] = y - m_matrices[1][0];

	double m = -1000000;

	for (int i = 0; i < 2; i++) {
		m = max(m, abs(Iteracion.evaluacion[i][0]));
	}
	Iteracion.error_absoluto = m;

	soluciones.push_back(Iteracion);

	for (int i = 1; i <= numero_iteraciones; i++) {
		x = soluciones[i - 1].operacion[0][0];
		y = soluciones[i - 1].operacion[1][0];
		Iteracion.x[0][0] = x;
		Iteracion.x[1][0] = y;
		Iteracion.iteracion = i;

		// Valores para la matriz jacobiana
		Iteracion.matriz_jacobiana[0][0] =
			EvaluacionDerivadaEcuacionUnoSistemaUnoX(x, y);
		Iteracion.matriz_jacobiana[0][1] =
			EvaluacionDerivadaEcuacionUnoSistemaUnoY(x);
		Iteracion.matriz_jacobiana[1][0] =
			EvaluacionDerivadaEcuacionDosSistemaUnoX(y);
		Iteracion.matriz_jacobiana[1][1] =
			EvaluacionDerivadaEcuacionDosSistemaUnoY(x, y);

		// Se llama  a la matriz jacobiana inversa

		Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);

		// Se evaluan los puntos iniciales en las funciones dadas

		Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaUno(x, y);
		Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaUno(x, y);

		vector< vector<double> > m_matrices =
			MultiplicacionMatrices(Iteracion.matriz_inversa, Iteracion.evaluacion);

		Iteracion.operacion[0][0] = x - m_matrices[0][0];
		Iteracion.operacion[1][0] = y - m_matrices[1][0];

		double m = -1000000;

		for (int j = 0; j < 2; j++) {
			m = max(m, abs(Iteracion.evaluacion[j][0] -
						soluciones[i - 1].evaluacion[j][0]));
		}
		Iteracion.error_absoluto = m;

		double m1 = -10000000;
		m1 = max(x, y);
		Iteracion.error_relativo = abs(m / m1);

		soluciones.push_back(Iteracion);
		if (abs(Iteracion.evaluacion[0][0]) <= tolerancia and
				abs(Iteracion.evaluacion[1][0]) <= tolerancia)
			break;
	}
	ImprimeResultados(soluciones);
	MostrarResultados(soluciones[soluciones.size() - 1].x);
}

void Sistema2() {
	double x, y;
	double numero_iteraciones;
	double tolerancia;
	cout << "Ingrese el valor inicial de x: ";
	cin >> x;
	cout << "Ingresa el valor inicial de y: ";
	cin >> y;
	cout << "Ingrese el numero maximo de iteraciones: ";
	cin >> numero_iteraciones;
	cout << "Ingrese la tolerancia: ";
	cin >> tolerancia;

	vector<tabla> soluciones;
	tabla Iteracion;

	// Valores iniciales
	Iteracion.iteracion = 0;
	Iteracion.x.resize(2);

	for (int i = 0; i < 2; i++)
		Iteracion.x[i].resize(1);
	Iteracion.x[0][0] = x;
	Iteracion.x[1][0] = y;

	// Valores para la matriz jacobiana
	Iteracion.matriz_jacobiana.resize(2);
	for (int i = 0; i < 2; i++) {
		Iteracion.matriz_jacobiana[i].resize(2);
	}
	Iteracion.matriz_jacobiana[0][0] =
		EvaluacionDerivadaEcuacionUnoSistemaDosX(x);
	Iteracion.matriz_jacobiana[0][1] =
		EvaluacionDerivadaEcuacionUnoSistemaDosY(y);
	Iteracion.matriz_jacobiana[1][0] =
		EvaluacionDerivadaEcuacionDosSistemaDosX(x);
	Iteracion.matriz_jacobiana[1][1] = EvaluacionDerivadaEcuacionDosSistemaDosY();

	// Se llama  a la matriz jacobiana inversa

	Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);

	// Se evaluan los puntos iniciales en las funciones dadas

	Iteracion.evaluacion.resize(2);
	for (int i = 0; i < 2; i++)
		Iteracion.evaluacion[i].resize(1);
	Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaDos(x, y);
	Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaDos(x, y);

	vector< vector<double> > m_matrices =
		MultiplicacionMatrices(Iteracion.matriz_inversa, Iteracion.evaluacion);

	Iteracion.operacion.resize(2);
	for (int i = 0; i < 2; i++)
		Iteracion.operacion[i].resize(1);

	Iteracion.operacion[0][0] = x - m_matrices[0][0];
	Iteracion.operacion[1][0] = y - m_matrices[1][0];

	double m = -1000000;

	for (int i = 0; i < 2; i++) {
		m = max(m, abs(Iteracion.evaluacion[i][0]));
	}
	Iteracion.error_absoluto = m;

	soluciones.push_back(Iteracion);

	for (int i = 1; i <= numero_iteraciones; i++) {
		x = soluciones[i - 1].operacion[0][0];
		y = soluciones[i - 1].operacion[1][0];
		Iteracion.x[0][0] = x;
		Iteracion.x[1][0] = y;
		Iteracion.iteracion = i;

		// Valores para la matriz jacobiana
		Iteracion.matriz_jacobiana[0][0] =
			EvaluacionDerivadaEcuacionUnoSistemaDosX(x);
		Iteracion.matriz_jacobiana[0][1] =
			EvaluacionDerivadaEcuacionUnoSistemaDosY(y);
		Iteracion.matriz_jacobiana[1][0] =
			EvaluacionDerivadaEcuacionDosSistemaDosX(x);
		Iteracion.matriz_jacobiana[1][1] =
			EvaluacionDerivadaEcuacionDosSistemaDosY();

		// Se llama  a la matriz jacobiana inversa

		Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);

		// Se evaluan los puntos iniciales en las funciones dadas

		Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaDos(x, y);
		Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaDos(x, y);

		vector< vector<double> > m_matrices =
			MultiplicacionMatrices(Iteracion.matriz_inversa, Iteracion.evaluacion);

		Iteracion.operacion[0][0] = x - m_matrices[0][0];
		Iteracion.operacion[1][0] = y - m_matrices[1][0];

		double m = -1000000;

		for (int j = 0; j < 2; j++) {
			m = max(m, abs(Iteracion.evaluacion[j][0] -
						soluciones[i - 1].evaluacion[j][0]));
		}
		Iteracion.error_absoluto = m;

		double m1 = -10000000;
		m1 = max(x, y);
		Iteracion.error_relativo = abs(m / m1);

		soluciones.push_back(Iteracion);
		if (abs(Iteracion.evaluacion[0][0]) <= tolerancia and
				abs(Iteracion.evaluacion[1][0]) <= tolerancia)
			break;
	}
	ImprimeResultados(soluciones);
	MostrarResultados(soluciones[soluciones.size() - 1].x);
}

void Sistema3() {
	double x, y, z;
	double numero_iteraciones;
	double tolerancia;
	cout << "Ingrese el valor inicial de x: ";
	cin >> x;
	cout << "Ingresa el valor inicial de y: ";
	cin >> y;
	cout << "Ingresa el valor inicial de z: ";
	cin >> z;
	cout << "Ingrese el numero maximo de iteraciones: ";
	cin >> numero_iteraciones;
	cout << "ingrese  la tolerancia: ";
	cin >> tolerancia;

	vector<tabla> soluciones;
	tabla Iteracion;

	// Valores iniciales
	Iteracion.iteracion = 0;
	Iteracion.x.resize(3);

	for (int i = 0; i < 3; i++)
		Iteracion.x[i].resize(1);
	Iteracion.x[0][0] = x;
	Iteracion.x[1][0] = y;
	Iteracion.x[2][0] = z;

	// Valores para la matriz jacobiana
	Iteracion.matriz_jacobiana.resize(3);
	for (int i = 0; i < 3; i++) {
		Iteracion.matriz_jacobiana[i].resize(3);
	}
	Iteracion.matriz_jacobiana[0][0] =
		EvaluacionDerivadaEcuacionUnoSistemaTresX(x);
	Iteracion.matriz_jacobiana[0][1] =
		EvaluacionDerivadaEcuacionUnoSistemaTresY(y);
	Iteracion.matriz_jacobiana[0][2] =
		EvaluacionDerivadaEcuacionUnoSistemaTresZ(z);
	Iteracion.matriz_jacobiana[1][0] =
		EvaluacionDerivadaEcuacionDosSistemaTresX(x);
	Iteracion.matriz_jacobiana[1][1] =
		EvaluacionDerivadaEcuacionDosSistemaTresY(y);
	Iteracion.matriz_jacobiana[1][2] =
		EvaluacionDerivadaEcuacionDosSistemaTresZ(z);
	Iteracion.matriz_jacobiana[2][0] =
		EvaluacionDerivadaEcuacionTresSistemaTresX(x);
	Iteracion.matriz_jacobiana[2][1] =
		EvaluacionDerivadaEcuacionTresSistemaTresY(y);
	Iteracion.matriz_jacobiana[2][2] =
		EvaluacionDerivadaEcuacionTresSistemaTresZ(z);

	// Se llama  a la matriz jacobiana inversa

	Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);

	// Se evaluan los puntos iniciales en las funciones dadas

	Iteracion.evaluacion.resize(3);
	for (int i = 0; i < 3; i++)
		Iteracion.evaluacion[i].resize(1);
	Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaTres(x, y, z);
	Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaTres(x, y, z);
	Iteracion.evaluacion[2][0] = EvaluacionEcuacionTresSistemaTres(x, y, z);

	vector< vector<double> > m_matrices =
		MultiplicacionMatrices(Iteracion.matriz_inversa, Iteracion.evaluacion);
	Iteracion.operacion.resize(3);
	for (int i = 0; i < 3; i++)
		Iteracion.operacion[i].resize(1);

	Iteracion.operacion[0][0] = x - m_matrices[0][0];
	Iteracion.operacion[1][0] = y - m_matrices[1][0];
	Iteracion.operacion[2][0] = z - m_matrices[2][0];

	double m = -1000000;

	for (int i = 0; i < 3; i++) {
		m = max(m, abs(Iteracion.evaluacion[i][0]));
	}
	Iteracion.error_absoluto = m;

	soluciones.push_back(Iteracion);

	for (int i = 1; i <= numero_iteraciones; i++) {
		x = soluciones[i - 1].operacion[0][0];
		y = soluciones[i - 1].operacion[1][0];
		z = soluciones[i - 1].operacion[2][0];

		Iteracion.x[0][0] = x;
		Iteracion.x[1][0] = y;
		Iteracion.x[2][0] = z;
		Iteracion.iteracion = i;

		// Valores para la matriz jacobiana
		Iteracion.matriz_jacobiana[0][0] =
			EvaluacionDerivadaEcuacionUnoSistemaTresX(x);
		Iteracion.matriz_jacobiana[0][1] =
			EvaluacionDerivadaEcuacionUnoSistemaTresY(y);
		Iteracion.matriz_jacobiana[0][2] =
			EvaluacionDerivadaEcuacionUnoSistemaTresZ(z);
		Iteracion.matriz_jacobiana[1][0] =
			EvaluacionDerivadaEcuacionDosSistemaTresX(x);
		Iteracion.matriz_jacobiana[1][1] =
			EvaluacionDerivadaEcuacionDosSistemaTresY(y);
		Iteracion.matriz_jacobiana[1][2] =
			EvaluacionDerivadaEcuacionDosSistemaTresZ(z);
		Iteracion.matriz_jacobiana[2][0] =
			EvaluacionDerivadaEcuacionTresSistemaTresX(x);
		Iteracion.matriz_jacobiana[2][1] =
			EvaluacionDerivadaEcuacionTresSistemaTresY(y);
		Iteracion.matriz_jacobiana[2][2] =
			EvaluacionDerivadaEcuacionTresSistemaTresZ(z);

		// Se llama  a la matriz jacobiana inversa

		Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);

		// Se evaluan los puntos iniciales en las funciones dadas

		Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaTres(x, y, z);
		Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaTres(x, y, z);
		Iteracion.evaluacion[2][0] = EvaluacionEcuacionTresSistemaTres(x, y, z);

		vector< vector<double> > m_matrices =
			MultiplicacionMatrices(Iteracion.matriz_inversa, Iteracion.evaluacion);
		Iteracion.operacion[0][0] = x - m_matrices[0][0];
		Iteracion.operacion[1][0] = y - m_matrices[1][0];
		Iteracion.operacion[2][0] = z - m_matrices[2][0];

		double m = -1000000;

		for (int j = 0; j < 3; j++) {
			m = max(m, abs(Iteracion.evaluacion[j][0] -
						soluciones[i - 1].evaluacion[j][0]));
		}
		Iteracion.error_absoluto = m;

		double m1 = -10000000;
		m1 = max(x, y);
		Iteracion.error_relativo = abs(m / m1);

		soluciones.push_back(Iteracion);
		if (abs(Iteracion.evaluacion[0][0]) <= tolerancia and
				abs(Iteracion.evaluacion[1][0]) <= tolerancia and
				abs(Iteracion.evaluacion[2][0]) <= tolerancia)
			break;
	}
	ImprimeResultados(soluciones);
	MostrarResultados(soluciones[soluciones.size() - 1].x);
}

void Sistema4() {
	double x, y, z;
	double numero_iteraciones;
	double tolerancia;
	cout << "Ingrese el valor inicial de x: ";
	cin >> x;
	cout << "Ingresa el valor inicial de y: ";
	cin >> y;
	cout << "Ingresa el valor inicial de z: ";
	cin >> z;

	cout << "Ingrese el numero maximo de iteraciones: ";
	cin >> numero_iteraciones;
	cout << "Ingrese la tolerancia: ";
	cin >> tolerancia;

	vector<tabla> soluciones;
	tabla Iteracion;

	// Valores iniciales
	Iteracion.iteracion = 0;
	Iteracion.x.resize(3);

	for (int i = 0; i < 3; i++)
		Iteracion.x[i].resize(1);
	Iteracion.x[0][0] = x;
	Iteracion.x[1][0] = y;
	Iteracion.x[2][0] = z;

	// Valores para la matriz jacobiana
	Iteracion.matriz_jacobiana.resize(3);
	for (int i = 0; i < 3; i++) {
		Iteracion.matriz_jacobiana[i].resize(3);
	}
	Iteracion.matriz_jacobiana[0][0] =
		EvaluacionDerivadaEcuacionUnoSistemaCuatroX(x);
	Iteracion.matriz_jacobiana[0][1] =
		EvaluacionDerivadaEcuacionUnoSistemaCuatroY(y);
	Iteracion.matriz_jacobiana[0][2] =
		EvaluacionDerivadaEcuacionUnoSistemaCuatroZ();
	Iteracion.matriz_jacobiana[1][0] =
		EvaluacionDerivadaEcuacionDosSistemaCuatroX(x);
	Iteracion.matriz_jacobiana[1][1] =
		EvaluacionDerivadaEcuacionDosSistemaCuatroY();
	Iteracion.matriz_jacobiana[1][2] =
		EvaluacionDerivadaEcuacionDosSistemaCuatroZ();
	Iteracion.matriz_jacobiana[2][0] =
		EvaluacionDerivadaEcuacionTresSistemaCuatroX(x);
	Iteracion.matriz_jacobiana[2][1] =
		EvaluacionDerivadaEcuacionTresSistemaCuatroY(y);
	Iteracion.matriz_jacobiana[2][2] =
		EvaluacionDerivadaEcuacionTresSistemaCuatroZ(z);

	// Se llama  a la matriz jacobiana inversa

	Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);

	// Se evaluan los puntos iniciales en las funciones dadas

	Iteracion.evaluacion.resize(3);
	for (int i = 0; i < 3; i++)
		Iteracion.evaluacion[i].resize(1);
	Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaCuatro(x, y);
	Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaCuatro(x, y);
	Iteracion.evaluacion[2][0] = EvaluacionEcuacionTresSistemaCuatro(x, y, z);

	vector< vector<double> > m_matrices =
		MultiplicacionMatrices(Iteracion.matriz_inversa, Iteracion.evaluacion);
	Iteracion.operacion.resize(3);
	for (int i = 0; i < 3; i++)
		Iteracion.operacion[i].resize(1);

	Iteracion.operacion[0][0] = x - m_matrices[0][0];
	Iteracion.operacion[1][0] = y - m_matrices[1][0];
	Iteracion.operacion[2][0] = z - m_matrices[2][0];

	double m = -1000000;

	for (int i = 0; i < 3; i++) {
		m = max(m, abs(Iteracion.evaluacion[i][0]));
	}
	Iteracion.error_absoluto = m;

	soluciones.push_back(Iteracion);

	for (int i = 1; i <= numero_iteraciones; i++) {
		x = soluciones[i - 1].operacion[0][0];
		y = soluciones[i - 1].operacion[1][0];
		z = soluciones[i - 1].operacion[2][0];

		Iteracion.x[0][0] = x;
		Iteracion.x[1][0] = y;
		Iteracion.x[2][0] = z;
		Iteracion.iteracion = i;

		// Valores para la matriz jacobiana

		Iteracion.matriz_jacobiana[0][0] =
			EvaluacionDerivadaEcuacionUnoSistemaCuatroX(x);
		Iteracion.matriz_jacobiana[0][1] =
			EvaluacionDerivadaEcuacionUnoSistemaCuatroY(y);
		Iteracion.matriz_jacobiana[0][2] =
			EvaluacionDerivadaEcuacionUnoSistemaCuatroZ();
		Iteracion.matriz_jacobiana[1][0] =
			EvaluacionDerivadaEcuacionDosSistemaCuatroX(x);
		Iteracion.matriz_jacobiana[1][1] =
			EvaluacionDerivadaEcuacionDosSistemaCuatroY();
		Iteracion.matriz_jacobiana[1][2] =
			EvaluacionDerivadaEcuacionDosSistemaCuatroZ();
		Iteracion.matriz_jacobiana[2][0] =
			EvaluacionDerivadaEcuacionTresSistemaCuatroX(x);
		Iteracion.matriz_jacobiana[2][1] =
			EvaluacionDerivadaEcuacionTresSistemaCuatroY(y);
		Iteracion.matriz_jacobiana[2][2] =
			EvaluacionDerivadaEcuacionTresSistemaCuatroZ(z);
		// Se llama  a la matriz jacobiana inversa

		Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);

		// Se evaluan los puntos iniciales en las funciones dadas

		Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaCuatro(x, y);
		Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaCuatro(x, y);
		Iteracion.evaluacion[2][0] = EvaluacionEcuacionTresSistemaCuatro(x, y, z);

		vector< vector<double> > m_matrices =
			MultiplicacionMatrices(Iteracion.matriz_inversa, Iteracion.evaluacion);

		Iteracion.operacion[0][0] = x - m_matrices[0][0];
		Iteracion.operacion[1][0] = y - m_matrices[1][0];
		Iteracion.operacion[2][0] = z - m_matrices[2][0];

		double m = -1000000;

		for (int j = 0; j < 3; j++) {
			m = max(m, abs(Iteracion.evaluacion[j][0] -
						soluciones[i - 1].evaluacion[j][0]));
		}
		Iteracion.error_absoluto = m;

		double m1 = -10000000;
		m1 = max(x, y);
		Iteracion.error_relativo = abs(m / m1);

		soluciones.push_back(Iteracion);

		if (abs(Iteracion.evaluacion[0][0]) <= tolerancia and
				abs(Iteracion.evaluacion[1][0]) <= tolerancia and
				abs(Iteracion.evaluacion[2][0]) <= tolerancia)
			break;
	}
	ImprimeResultados(soluciones);
	MostrarResultados(soluciones[soluciones.size() - 1].x);
}

void ImprimeTabla(const vector<pdd> &tablaI) {
	cout << "\n\t\t\t***VALORES: ***" << endl;
	cout << "i\tx_i\tf(x_i)\n" << endl;
	for (int i = 0; i < tablaI.size(); i++) {
		cout << i << "\t"; printf("%.4f",tablaI[i].first); cout  << "\t"; printf("%.4f",tablaI[i].second); cout << "\n";
	}
}

bool ElementosOrdenados(const vector<pdd> &tablaI) {
	for (int i = 0; i < (int)tablaI.size() - 1; i++)
		if (tablaI[i] > tablaI[i + 1])
			return false;
	return true;
}
void menuPrincipalInterpolacion() {
	

	cout << " _______________________________________________________________________________________________" << endl;
	cout << "|                                                                                               |"<< endl;	
	cout << "| ¿ Que accion desea realizar?                                                                  |"<< endl;
	cout << "|_______________________________________________________________________________________________|"<< endl;
	cout << "|Presione 1 para iniciar con el metodo de diferencias divididas                                 |"<< endl;
	cout << "|Presione 2 para terminar el metodo de diferencias divididas                                    |"<< endl;
	cout << "|_______________________________________________________________________________________________|"<< endl;
}

void factorizacionLU(vector< vector<double> > &matriz, vector< vector<double> > &L,
		vector< vector<double> > &U) {
	int n = matriz.size();

	// Se inicializa la matriz L como matriz identidad
	// y la matriz U como la copia de la matriz original.

	L = vector< vector<double> >(n, vector<double>(n, 0));
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

vector<double> SolucionSistema(const vector< vector<double> > &L,
		const vector< vector<double> > &U,
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

void MenuPrincipalSpline() {
	cout << " _____________________________________________________________________________" << endl;
	cout << "|                                                                             |"<< endl;	
	cout << "| ¿ Que accion desea realizar?                                                |" << endl;
   	cout << "|_____________________________________________________________________________|" << endl;
	cout << "|Presione 1 para ingresar nuevos datos y obtener nuevos spline cúbicos        |" << endl;
	cout << "|Presione 2 para terminar con el metodo de spline cubico.                     |" << endl;
	cout << "|_____________________________________________________________________________|" << endl;

}


void  SistemasNoLineales() {
	int menu_principal = 1;
	while (menu_principal != 2) {
		MenuPrincipalNewton();
		cin >> menu_principal;
		int menu_sistemas = 1;
		if (menu_principal == 1) {
			while (menu_sistemas == 1 or menu_sistemas == 2 or menu_sistemas == 3 or
					menu_sistemas == 4) {
				MenuSistemas();
				cin >> menu_sistemas;
				if (menu_sistemas == 1) {
					cout << "Se resolvera el sistema 1" << endl;
					Sistema1();
					int menu_datos = 1;
					while (menu_datos == 1) {
						MenuCambioDatos();
						cin >> menu_datos;
						if (menu_datos == 1)
							Sistema1();
					}
				} else if (menu_sistemas == 2) {
					cout << "Se resolvera el sistema  2" << endl;
					Sistema2();
					int menu_datos = 1;
					while (menu_datos == 1) {
						MenuCambioDatos();
						cin >> menu_datos;
						if (menu_datos == 1)
							Sistema2();
					}
				} else if (menu_sistemas == 3) {
					cout << "Se resolvera el sistema 3" << endl;
					Sistema3();
					int menu_datos = 1;
					while (menu_datos == 1) {
						MenuCambioDatos();
						cin >> menu_datos;
						if (menu_datos == 1)
							Sistema3();
					}
				} else if (menu_sistemas == 4) {
					cout << "Se resolvera el sistema 4" << endl;
					Sistema4();
					int menu_datos = 1;
					while (menu_datos == 1) {
						MenuCambioDatos();
						cin >> menu_datos;
						if (menu_datos == 1)
							Sistema4();
					}

				} else {
					cout << "Adios" << endl;
				}
			}
		}
	}

}

bool cmp(pdd a, pdd b){
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}
void InterpolacionPolinomial() {
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
				sort(tablaI.begin(), tablaI.end(), cmp);
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
				vector< vector<double> > diferencias_divididas(
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
}

void SplineCubico() {

	int seguir_en_programa = 1;
	while (seguir_en_programa == 1) {
		MenuPrincipalSpline();
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
			cout << i << "\t\t"; printf("%.4f",coordenadas[i].x); cout << "\t\t"; printf("%.6f",coordenadas[i].y);
			cout << endl;
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
			cout << i << "\t\t" << intervaloH[i] << "\t\t"; printf ("%.4f",diferencias[i]); cout << endl;
		}
		cout << endls;
		// Se calcula el sistema.
		vector< vector<double> > sistema(n_puntos, vector<double>(n_puntos + 1, 0.0));
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
		vector< vector<double> > matriz_sistema(n_puntos - 1,
				vector<double>(n_puntos - 1, 0.0));

		vector<double> coeficientes_matriz(n_puntos - 1, 0.0);

		for (int i = 1; i <= n_puntos - 1; i++)
			for (int j = 1; j <= n_puntos - 1; j++)
				matriz_sistema[i - 1][j - 1] = sistema[i][j];

		for (int i = 1; i <= n_puntos - 1; i++)
			coeficientes_matriz[i - 1] = coeficientes_sistema[i];

		// Se implementa la solucion del sistema mediante
		// la factorizacion LU

		vector< vector<double> > L, U;

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
		for (int i = 0; i <= n_puntos; i++){
			cout << "S_" << i << " = "; printf("%.6f",soluciones[i]); cout << endl;
		}
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
	return ;
}



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

	cout << " __________________________________________________________________"<< endl;
	cout << "|                                                                  |"<< endl;
	cout << "|FUNCIONES DE LAS CUALES SE BUSCARA UNA APROXIMACION A SU INTEGRAL |"<< endl;
	cout << "|__________________________________________________________________|"<< endl;
	cout << "|                                                                  |"<< endl;
	cout << "|                  1.- x⁴ * ( sqrt(3+2*x²) /3)                     |"<< endl;
	cout << "|                  2.- x⁵ /( ( x² + 4) ^ (1/5))                    |"<< endl;
	cout << "|__________________________________________________________________|"<< endl;
	cout << endl;

	cout << " _______________________________________________________________________________________________" << endl;
	cout << "|                                                                                               |"<< endl;	
	cout << "| ¿ Que accion desea realizar?                                                                  |"<< endl;
	cout << "|_______________________________________________________________________________________________|"<< endl;
	cout << "|Presione 1 para buscar una aproximacion de la integral de una de las funciones                 |"<< endl;
	cout << "|Presione 2 para terminar con el metodo de integracion numerica.                                |"<< endl;
	cout << "|_______________________________________________________________________________________________|"<< endl;
}
void menuFunciones() {
	cout << endls;
	cout << " ____________________________________________________________________________________________________" << endl;
	cout << "|                                                                                                    |"<< endl;	
	cout << "| ¿ Que accion desea realizar?                                                                       |"<< endl;
	cout << "|____________________________________________________________________________________________________|"<< endl;
	cout << "|Presione 1 para buscar una aproximacion a la integral de la funcion: x⁴ * ( sqrt(3+2*x²) /3)        |"<< endl;
	cout << "|Presione 2 para buscar una aproximacion a la integral de la funcion: x⁵ /( ( x² + 4) ^ (1/5))       |"<< endl;
	cout << "|Presione 3 para volver al menu principal del metodo                                                 |"<< endl;
	cout << "|____________________________________________________________________________________________________|"<< endl;
}
void IntegracionNumerica() {
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
					for (int i = 0; i < simpson1_3.size(); i++){
						cout << "\t" << i << "\t"; printf("%.4f",simpson1_3[i].first); cout<< "\t\t";
							printf("%.4f",simpson1_3[i].second); cout << endl;
					}
					cout << endls;
					cout << "\tTABLA A EVALUAR CON REGLA DE SIMPSON 3/8" << endl;
					for (int i = 0; i < simpson3_8.size(); i++){
						cout << "\t" << i << "\t"; printf("%.4f", simpson3_8[i].first); cout << "\t\t";
							printf("%.4f",simpson3_8[i].second); cout << endl;
					}
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
					for (int i = 0; i < simpson3_8.size(); i++){
						cout << "\t" << i << "\t"; printf("%.4f",simpson3_8[i].first); cout << "\t\t";
							printf("%.4f", simpson3_8[i].second); cout << endl;
					}
					cout << endls;

					cout << "\tTABLA A EVALUAR CON REGLA DE SIMPSON 1/3" << endl;
					for (int i = 0; i < simpson1_3.size(); i++){
						cout << "\t" << i << "\t"; printf("%.4f",simpson1_3[i].first); cout << "\t\t";
							printf("%.4f",simpson1_3[i].second); cout << endl;
					}
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
	return ;
}

void menuPrincipal(){
    cout << " _________________________________________" << endl;
    cout << "|                                         |" << endl;
    cout << "| *******     PAQUETE FINAL ******        |" << endl;
    cout << "|                                         |" << endl;
    cout << "|_________________________________________|" << endl;  
    
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

    cout << " ___________________________________________________________________" << endl;
    cout << "|                                                                   |" << endl;
    cout << "| Que accion desea realizar?                                        |" << endl;
    cout << "|___________________________________________________________________|" << endl;
    cout << "|                                                                   |" << endl;
    cout << "| Presione 1 para para ir a alguno de los metodos vistos en el curso|" << endl;
    cout << "| Presiona 2 para salir del paquete de programas y terminar         |" << endl;
    cout << "|___________________________________________________________________|" << endl;

}

void menuMetodos(){
    cout << " ______________________________________________________" << endl;
    cout << "|                                                      |"<< endl;
    cout << "| Que metodo deseas emplear?                           |"<< endl;
    cout << "|______________________________________________________|"<< endl;
    cout << "|                                                      |"<< endl;
    cout << "| Presiona 1 para emplear el metodo de Newton          |" << endl;
    cout << "|                                                      | " << endl;
    cout << "| Presione 2 para emplear Interpolacion Polinomial     |" << endl;
    cout << "|                                                      |"<< endl;
    cout << "| Presione 3 para emplear Spline Cubico                |"<< endl;
    cout << "|                                                      |" << endl;
    cout << "| Presione 4 para emplear Integracion Numerica         |" << endl;
    cout << "|                                                      |" << endl;
    cout << "|Presione 5 para regresar al menu principal            |"<< endl;
    cout << "|______________________________________________________|" << endl;




}
int main (){

    int terminar_programa = 1;
    while (terminar_programa == 1){
        menuPrincipal();
        cin >> terminar_programa;

        if (terminar_programa == 2) break;

        int metodo  = 1;
        while (metodo == 1 or metodo == 2 or metodo == 3 or metodo == 4 ){
            menuMetodos();
            cin >> metodo;
            if (metodo == 5) break;
            if (metodo == 1){
                cout << "\n\t\t\t***METODOO DE NEWTON***" << endl;
                SistemasNoLineales();
            }
            else if (metodo == 2){
                cout << "\n\t\t\t***DIFERENCIAS DIVIDIDAS***" << endl;
                InterpolacionPolinomial();
            }else if (metodo == 3){
                cout << "\n\t\t\t***SPLINE CUBICO***" << endl;
                SplineCubico();
            }else if (metodo == 4){
                cout << "\n\t\t\t***INTEGRACION NUMERICA***" << endl;
                IntegracionNumerica();
            }
        }
    }
    return 0;
}
