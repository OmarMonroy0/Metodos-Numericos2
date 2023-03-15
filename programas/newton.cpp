#include<bits/stdc++.h>
#define endl '\n'
#define endls "\n\n\n"
using namespace std;


typedef struct tabla{
	int iteracion;
	vector < vector < double  >> x;
	vector < vector < double > > matriz_jacobiana;
	vector < vector < double  >> matriz_inversa;
	vector < vector < double > >  evaluacion;
	vector < vector < double > >  operacion;
	double error_relativo;
	double error_absoluto;
}tabla;

//Se hara el calculo del determinante para verificar si 
//la matriz tiene inversa
//Si el determinante es igual a 0 no tiene matriz inversa

double  TieneInversa(const vector < vector < double >> &matriz){
	if(matriz.size() == 2){
		return (matriz[0][0]*matriz[1][1] - matriz[0][1]*matriz[1][0]);
	}else{
		return (matriz[0][0]*(matriz[1][1]*matriz[2][2]-matriz[2][1]*matriz[1][2]) - matriz[0][1]*(matriz[1][0]*matriz[2][2]-matriz[2][0]*matriz[1][2])
					+ matriz[0][2]*(matriz[1][0]*matriz[2][1]-matriz[2][0]*matriz[1][1]));
	}	
}

//Obtenemos la matriz transpuesta 
vector < vector < double > >  Transpuesta(const vector < vector < double >> &matriz){
	vector < vector < double > > transpuesta(matriz.size(),vector < double > (matriz.size(),0));

	for (int i = 0; i < matriz.size(); i ++){
		for (int j =  0; j < matriz.size(); j ++){
			transpuesta[j][i] = matriz[i][j];
		}
	}
	return transpuesta;
}

//Se obtiene la matriz Adjunta
vector < vector < double > > Adjunta(const vector < vector < double >> &matriz){
	  vector < vector <int >>  signos  = {
				{1,-1,1},
				{-1,1,-1},
				{1,-1,1}
			  };
	vector < vector < double > > adjunta(matriz.size(),vector < double > (matriz.size(),0));

	adjunta[0][0] = signos[0][0]*(matriz[1][1]*matriz[2][2]-matriz[2][1]*matriz[1][2]);
	adjunta[0][1] = signos[0][1]*(matriz[1][0]*matriz[2][2]-matriz[2][0]*matriz[1][2]);
	adjunta[0][2] = signos[0][2]*(matriz[1][0]*matriz[2][1]-matriz[2][0]*matriz[1][1]);
	adjunta[1][0] = signos[1][0]*(matriz[0][1]*matriz[2][2]-matriz[2][1]*matriz[0][2]);
	adjunta[1][1] = signos[1][1]*(matriz[0][0]*matriz[2][2]-matriz[2][0]*matriz[0][2]);
	
	adjunta[1][2] = signos[1][2]*(matriz[0][0]*matriz[2][1]-matriz[2][0]*matriz[0][1]);
	
	adjunta[2][0] = signos[2][0]*(matriz[0][1]*matriz[1][2]-matriz[1][1]*matriz[0][2]);
	adjunta[2][1] = signos[2][1]*(matriz[0][0]*matriz[1][2]-matriz[1][0]*matriz[0][2]);
	adjunta[2][2] = signos[2][2]*(matriz[0][0]*matriz[1][1]-matriz[1][0]*matriz[0][1]);

	return adjunta;

}
//funcion para encontrar la inversa de una matriz
vector<vector<double>> Inversa(const vector < vector < double >> &matriz){
	vector < vector < double > > inversa(matriz.size(),vector < double > (matriz.size(),0));
	double determinante  = TieneInversa(matriz);
	vector < vector < double >> transpuesta = Transpuesta ( matriz );
	vector < vector < double >> adjunta (matriz.size(),vector < double > (matriz.size(),0));

	if (matriz.size() == 2){
		adjunta [0][0] = transpuesta[1][1];
		adjunta [0][1] = transpuesta[1][0] * (-1);
		adjunta [1][0] = transpuesta[0][1] * (-1);
		adjunta [1][1] = transpuesta[0][0];
	}
	else{ 
 		adjunta = Adjunta ( transpuesta );
	}
	for (int i = 0; i  < matriz.size(); i ++){
		for (int j  = 0; j <  matriz.size(); j++){
			inversa[i][j]  = adjunta[i][j] / (double)determinante;
		}
	}
	return inversa;
}


//Evaluacion de las funciones en el punto inicial dado
//F(x^0)
inline double EvaluacionEcuacionUnoSistemaUno(double x,double y){
	return (x*x + x* y - 10);
}

inline double EvaluacionEcuacionDosSistemaUno(double x,double y){
	return ( y + 3*x*y*y - 50);
}

inline double EvaluacionEcuacionUnoSistemaDos(double x,double y){
	return (x*x+y*y-9);
}

inline double EvaluacionEcuacionDosSistemaDos(double x, double y){
	return ((-1)*exp(x)-2*y-3);
}

inline double EvaluacionEcuacionUnoSistemaTres(double x, double y,double z){
	return(2*x*x-4*x+y*y+3*z*z+6*z+2);
}

inline double EvaluacionEcuacionDosSistemaTres(double x,double y,double z){
	return (x*x+y*y-2*y+2*z*z-5);
}

inline double EvaluacionEcuacionTresSistemaTres(double x,double y,double z){
	return (3*x*x-12*x+y*y-3*z*z+8);
}

inline double EvaluacionEcuacionUnoSistemaCuatro(double x, double y){
	return 	(x*x-4*x+y*y);
}

inline double EvaluacionEcuacionDosSistemaCuatro(double x, double y){
	return (x*x-x-12*y+1);
}

inline double EvaluacionEcuacionTresSistemaCuatro(double x,double y,double z){
	return (3*x*x-12*x+y*y-3*z*z+8);
}

//EVALUACION DE LAS DERIVADAS
//PRIMER SISTEMA
inline double EvaluacionDerivadaEcuacionUnoSistemaUnoX(double x,double y){
	return (2*x+y);
}

inline double EvaluacionDerivadaEcuacionUnoSistemaUnoY(double x){
	return x;
}

inline double EvaluacionDerivadaEcuacionDosSistemaUnoX(double y ){
	return (3*y*y);
}

inline double EvaluacionDerivadaEcuacionDosSistemaUnoY(double x, double y){
	return (1+6*x*y);			
}

//SEGUNDO SISTEMA
inline double EvaluacionDerivadaEcuacionUnoSistemaDosX(double x){
	return (2*x);
}

inline double EvaluacionDerivadaEcuacionUnoSistemaDosY(double y){
	return (2*y);
}

inline double EvaluacionDerivadaEcuacionDosSistemaDosX(double x){
	return ((-1) * exp(x));
}
inline double EvaluacionDerivadaEcuacionDosSistemaDosY(){
	return (-2);
}

//DERIVADAS SISTEMA 3
inline double EvaluacionDerivadaEcuacionUnoSistemaTresX(double x){
	return (4*x-4);
}

inline double EvaluacionDerivadaEcuacionUnoSistemaTresY(double y){
	return (2*y);
}
inline double EvaluacionDerivadaEcuacionUnoSistemaTresZ(double z){
	return (6*z+6);
}

inline double EvaluacionDerivadaEcuacionDosSistemaTresX(double x){
	return (2*x);
} 

inline double EvaluacionDerivadaEcuacionDosSistemaTresY(double y){
	return (2*y-2);
}

inline double EvaluacionDerivadaEcuacionDosSistemaTresZ(double z){
	return (4*z);
}

inline double EvaluacionDerivadaEcuacionTresSistemaTresX(double x){
	return (6*x-12);
}

inline double EvaluacionDerivadaEcuacionTresSistemaTresY(double y){
	return (2*y);
}

inline double EvaluacionDerivadaEcuacionTresSistemaTresZ(double z){
	return ((-6)*z);
}

//EVALUACION DE DERIVADAS DEL CUARTO SISTEMA
inline double EvaluacionDerivadaEcuacionUnoSistemaCuatroX(double x){
	return (2*x-4);
}

inline double EvaluacionDerivadaEcuacionUnoSistemaCuatroY(double y){
	return (2*y);
}

inline double EvaluacionDerivadaEcuacionUnoSistemaCuatroZ(){ return 0; }

inline double EvaluacionDerivadaEcuacionDosSistemaCuatroX(double x){
	return (2*x-1);
}

inline double EvaluacionDerivadaEcuacionDosSistemaCuatroY() { return -12;}

inline double EvaluacionDerivadaEcuacionDosSistemaCuatroZ() { return 0;}

inline double EvaluacionDerivadaEcuacionTresSistemaCuatroX(double x){
	return (6*x-12);
}
inline double EvaluacionDerivadaEcuacionTresSistemaCuatroY(double y){
	return 2*y;
}
inline double EvaluacionDerivadaEcuacionTresSistemaCuatroZ(double z){
	return (-6*z);
}

void MenuPrincipal(){
	cout << " _______________________________________" << endl;
	cout << "|			       		|" << endl;
	cout << "|    Integrantes del equipo		|" << endl;
	cout << "|_______________________________________|" << endl;
	cout << "| Cirilo Huerta Noe Alberto		|" << endl;
	cout << "|					|" << endl;
	cout << "| Lopez Vargas Luis Armando		|" << endl;
	cout << "|					|"<< endl;
	cout << "| Monroy Alarcon Omar Ulises		|"<< endl;
	cout << "|					|" << endl;
	cout << "| Perez Chavez Christopher Omar		|" << endl;
	cout << "|_______________________________________|" << endl;
	cout << endls;
	cout << " _______________________________________________" << endl;
	cout << "|						|"<< endl;	
	cout << "| ¿ Que accion desea realizar? 			|" << endl;
	cout << "|Presione 1 para ir al menu de sistemas 	|" << endl;
	cout << "|Presione 2 para terminar el programa 		|" << endl;
	cout << "|_______________________________________________|" << endl;

}

void MenuSistemas(){
	cout << "  ______________________________________________________________" << endl;   
	cout << " |							  	|" << endl;	
	cout << " | Ingrese el sistema del cual busca solucion            	|" << endl;
	cout << " | Las opciones de sistemas son las siguientes           	|" << endl;
	cout << " |							 	|" << endl;	
	cout << " | Opcion 1:                                             	|" << endl;
	cout << " |          f(x,y) =  x²  + xy-10 = 0   		  	|" << endl;
	cout << " |          f(x,y) =  y + 3xy²-50  = 0                  	|" << endl;
	cout << " |______________________________________________________________|" << endl;
	cout << " | Opcion 2: 					          	|" << endl;
	cout << " |          f(x,y) = x²+y²-9 = 0 			  	|" << endl;
	cout << " |          f(x,y) = -e^x - 2y - 3 = 0   		  	|" << endl;
	cout << " |______________________________________________________________|" << endl;
	cout << " | Opcion 3: 							|" << endl;
	cout << " |          f(x,y,z) = 2x² - 4x + y² + 3z² + 6z  + 2 = 0 	|" << endl;
	cout << " |          f(x,y,z) = x² + y² - 2y + 2z² - 5 = 0 	 	|" << endl;
	cout << " |          f(x,y,z) = 3x²-12x+y²-3z² + 8 = 0 		 	|"<< endl;
	cout << " |______________________________________________________________|"<< endl;
	cout << " | Opcion 4: 							|"<< endl;
	cout << " |          f(x,y,z) = x² - 4x + y²  = 0 			|" << endl;
	cout << " |          f(x,y,z) = x² - x  - 12y + 1  = 0			|" << endl;
	cout << " |          f(x,y,z) = 3x²-12x+y²-3z² + 8 = 0			| " << endl;
	cout << " |______________________________________________________________|" << endl;
	cout << " |								|" << endl;
	cout << " |  Ingrese 1 Para la opcion 1.					|" << endl;
	cout << " |  Ingrese 2 Para la opcion 2.					|" << endl;
	cout << " |  Ingrese 3 Para la opcion 3.					|" << endl;
	cout << " |  Ingrese 4 Para la opcion 4.					|" << endl;
	cout << " |								|" << endl;
	cout << " |								|" << endl;
	cout << " | INGRESE  5 PARA REGRESAR AL MENU PRINCIPAL			|" << endl;			
	cout << " |______________________________________________________________|" << endl;
}

//Funcion que multiplica dos matrices 
vector < vector < double >> MultiplicacionMatrices(const vector < vector < double >> &matriz1, const vector < vector < double >> &matriz2){
	vector < vector < double > > matriz_m (matriz1.size(),vector < double > (matriz2[0].size()));
	for (int i = 0; i <  matriz1.size(); i++){
		for (int j  = 0; j < matriz2[0].size(); j ++){
			for (int k  = 0; k < matriz2.size(); k ++){
				matriz_m[i][j] += matriz1[i][k] * matriz2[k][j];
			}
		} 
	}
	return matriz_m;
	
}
//funcion que imprime las iteraciones obtenidas
void ImprimeResultados(const vector < tabla > &resultado){
	for (int i = 0;  i < resultado.size(); i ++){
		
		cout << "Iteracion:  " << endl;
		cout << resultado[i].iteracion << endl << endl;
		
		cout << " x ^ 0 :" << endl;
		for (int j = 0; j < resultado[i].x.size(); j++)
			cout << resultado[i].x[j][0] << "     ";
		cout << endl << endl;
		
		cout << "Matriz Jacobiana: " << endl;
		for (int j = 0; j < resultado[i].matriz_jacobiana.size(); j++){
			for (int k = 0; k  < resultado[i].matriz_jacobiana.size(); k++)
				cout << resultado[i].matriz_jacobiana[j][k] << "    ";
			cout << endl;
		}
		cout << endl;


		cout << "Matriz Jacobiana Inversa: " << endl;
		for (int j = 0; j < resultado[i].matriz_inversa.size(); j++){
			for (int k = 0;   k < resultado[i].matriz_inversa.size(); k++)
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
		cout << resultado[i].error_relativo  << endl;


		cout << "--------------------------------------------" << endl << endl;

	}
	
}
void MenuCambioDatos(){
	cout << " ______________________________________________________________________________________"  << endl;
	cout << "|											|" << endl;
	cout << "|Pesiona 1 si Deseas seguir con el mismo sistema, solo cambiando los valores iniciales |" << endl; 
	cout << "|Presiona 2 si deseas regresar al menu de Sistemas					|" << endl;
	cout << "|______________________________________________________________________________________|" << endl;
}


void MostrarResultados (const vector < vector < double >> &resultados){
	
	cout << "\t\tLos resultados obtenidos con el sistema son los siguientes: " << endl;
	cout << "\t\t x = " << resultados[0][0] << endl;
	cout << "\t\t y = " << resultados[1][0] << endl;
	if(resultados.size() == 3)
		cout << "\t\t z = " << resultados[2][0] << endl;
}
//funcion que calcula las iteraciones del sistema 1
void Sistema1(){
	double x,y;
	double numero_iteraciones;
	double tolerancia;

	cout << "Ingrese el valor inicial de x: "; cin >> x;
	cout << "Ingresa el valor inicial de y: "; cin >> y;
	cout << "Ingrese el numero maximo de iteraciones: "; cin >> numero_iteraciones;
	cout << "Ingresa la tolerancia: "; cin >> tolerancia;	
	
	vector < tabla > soluciones;
	tabla Iteracion;
	
	//Valores iniciales
	Iteracion.iteracion = 0;
	Iteracion.x.resize(2);
	
	for (int i = 0; i < 2; i ++) Iteracion.x[i].resize(1);
	Iteracion.x[0][0] = x;
	Iteracion.x[1][0] = y;


	//Valores para la matriz jacobiana
	Iteracion.matriz_jacobiana.resize(2);
	for (int i = 0 ; i < 2; i ++){
		Iteracion.matriz_jacobiana[i].resize(2);
	} 
	Iteracion.matriz_jacobiana[0][0] = EvaluacionDerivadaEcuacionUnoSistemaUnoX(x,y);
	Iteracion.matriz_jacobiana[0][1] = EvaluacionDerivadaEcuacionUnoSistemaUnoY(x);
	Iteracion.matriz_jacobiana[1][0] = EvaluacionDerivadaEcuacionDosSistemaUnoX(y);
	Iteracion.matriz_jacobiana[1][1] = EvaluacionDerivadaEcuacionDosSistemaUnoY(x,y);

	//Se llama  a la matriz jacobiana inversa
	
	Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);
	
	//Se evaluan los puntos iniciales en las funciones dadas

	Iteracion.evaluacion.resize(2);
	for (int i = 0; i < 2; i ++) Iteracion.evaluacion[i].resize(1);
	Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaUno(x,y);
	Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaUno(x,y);


	vector < vector < double >> m_matrices = MultiplicacionMatrices(Iteracion.matriz_inversa,Iteracion.evaluacion);
	

	Iteracion.operacion.resize(2);
	for (int i = 0; i < 2; i ++) Iteracion.operacion[i].resize(1);

	Iteracion.operacion[0][0] = x- m_matrices[0][0];
	Iteracion.operacion[1][0] = y - m_matrices[1][0];

	double m = -1000000;

	for (int i =0 ; i < 2; i ++){
		m = max(m,abs(Iteracion.evaluacion[i][0]));
	}
	Iteracion.error_absoluto = m;
		
	soluciones.push_back(Iteracion);

	for (int i = 1; i <= numero_iteraciones; i ++){
		x = soluciones[i-1].operacion[0][0];
		y = soluciones[i-1].operacion[1][0];
		Iteracion.x[0][0] = x;
		Iteracion.x[1][0] = y;
		Iteracion.iteracion = i;

		//Valores para la matriz jacobiana
		Iteracion.matriz_jacobiana[0][0] = EvaluacionDerivadaEcuacionUnoSistemaUnoX(x,y);
		Iteracion.matriz_jacobiana[0][1] = EvaluacionDerivadaEcuacionUnoSistemaUnoY(x);
		Iteracion.matriz_jacobiana[1][0] = EvaluacionDerivadaEcuacionDosSistemaUnoX(y);
		Iteracion.matriz_jacobiana[1][1] = EvaluacionDerivadaEcuacionDosSistemaUnoY(x,y);

		//Se llama  a la matriz jacobiana inversa

		Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);

		//Se evaluan los puntos iniciales en las funciones dadas

		Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaUno(x,y);
		Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaUno(x,y);


		vector < vector < double >> m_matrices = MultiplicacionMatrices(Iteracion.matriz_inversa,Iteracion.evaluacion);

		Iteracion.operacion[0][0] = x- m_matrices[0][0];
		Iteracion.operacion[1][0] = y - m_matrices[1][0];

		double m = -1000000;

		for (int j =0 ; j < 2; j ++){
			m = max(m,abs(Iteracion.evaluacion[j][0]-soluciones[i-1].evaluacion[j][0]));
		}
		Iteracion.error_absoluto = m;
		
		double m1 = -10000000;
		m1 = max(x,y);
		Iteracion.error_relativo  = abs(m/m1);
		
		soluciones.push_back(Iteracion);
		if (abs(Iteracion.evaluacion[0][0]) <= tolerancia and abs(Iteracion.evaluacion[1][0]) <= tolerancia) break;
	}
	ImprimeResultados(soluciones);
	MostrarResultados(soluciones[soluciones.size()-1].x);
}

void Sistema2(){
	double x,y;
	double numero_iteraciones;
	double tolerancia;
	cout << "Ingrese el valor inicial de x: "; cin >> x;
	cout << "Ingresa el valor inicial de y: "; cin >> y;
	cout << "Ingrese el numero maximo de iteraciones: "; cin >> numero_iteraciones;
	cout << "Ingrese la tolerancia: "; cin >> tolerancia;

	vector < tabla > soluciones;
	tabla Iteracion;
	
	//Valores iniciales
	Iteracion.iteracion = 0;
	Iteracion.x.resize(2);
	
	for (int i = 0; i < 2; i ++) Iteracion.x[i].resize(1);
	Iteracion.x[0][0] = x;
	Iteracion.x[1][0] = y;


	//Valores para la matriz jacobiana
	Iteracion.matriz_jacobiana.resize(2);
	for (int i = 0 ; i < 2; i ++){
		Iteracion.matriz_jacobiana[i].resize(2);
	} 
	Iteracion.matriz_jacobiana[0][0] = EvaluacionDerivadaEcuacionUnoSistemaDosX(x);
	Iteracion.matriz_jacobiana[0][1] = EvaluacionDerivadaEcuacionUnoSistemaDosY(y);
	Iteracion.matriz_jacobiana[1][0] = EvaluacionDerivadaEcuacionDosSistemaDosX(x);
	Iteracion.matriz_jacobiana[1][1] = EvaluacionDerivadaEcuacionDosSistemaDosY();

	//Se llama  a la matriz jacobiana inversa
	
	Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);
	
	//Se evaluan los puntos iniciales en las funciones dadas

	Iteracion.evaluacion.resize(2);
	for (int i = 0; i < 2; i ++) Iteracion.evaluacion[i].resize(1);
	Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaDos(x,y);
	Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaDos(x,y);


	vector < vector < double >> m_matrices = MultiplicacionMatrices(Iteracion.matriz_inversa,Iteracion.evaluacion);


	Iteracion.operacion.resize(2);
	for (int i = 0; i < 2; i ++) Iteracion.operacion[i].resize(1);

	Iteracion.operacion[0][0] = x- m_matrices[0][0];
	Iteracion.operacion[1][0] = y - m_matrices[1][0];

	double m = -1000000;

	for (int i =0 ; i < 2; i ++){
		m = max(m,abs(Iteracion.evaluacion[i][0]));
	}
	Iteracion.error_absoluto = m;
		
	soluciones.push_back(Iteracion);

	for (int i = 1; i <= numero_iteraciones; i ++){
		x = soluciones[i-1].operacion[0][0];
		y = soluciones[i-1].operacion[1][0];
		Iteracion.x[0][0] = x;
		Iteracion.x[1][0] = y;
		Iteracion.iteracion = i;

		//Valores para la matriz jacobiana
		Iteracion.matriz_jacobiana[0][0] = EvaluacionDerivadaEcuacionUnoSistemaDosX(x);
		Iteracion.matriz_jacobiana[0][1] = EvaluacionDerivadaEcuacionUnoSistemaDosY(y);
		Iteracion.matriz_jacobiana[1][0] = EvaluacionDerivadaEcuacionDosSistemaDosX(x);
		Iteracion.matriz_jacobiana[1][1] = EvaluacionDerivadaEcuacionDosSistemaDosY();


		//Se llama  a la matriz jacobiana inversa

		Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);

		//Se evaluan los puntos iniciales en las funciones dadas

		Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaDos(x,y);
		Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaDos(x,y);

		

		vector < vector < double >> m_matrices = MultiplicacionMatrices(Iteracion.matriz_inversa,Iteracion.evaluacion);

		Iteracion.operacion[0][0] = x- m_matrices[0][0];
		Iteracion.operacion[1][0] = y - m_matrices[1][0];

		double m = -1000000;

		for (int j =0 ; j < 2; j ++){
			m = max(m,abs(Iteracion.evaluacion[j][0]-soluciones[i-1].evaluacion[j][0]));
		}
		Iteracion.error_absoluto = m;
		
		double m1 = -10000000;
		m1 = max(x,y);
		Iteracion.error_relativo  = abs(m/m1);
		
		soluciones.push_back(Iteracion);
		if (abs(Iteracion.evaluacion[0][0]) <= tolerancia and abs(Iteracion.evaluacion[1][0]) <= tolerancia) break;
	}
	ImprimeResultados(soluciones);
	MostrarResultados(soluciones[soluciones.size()-1].x);

}

void Sistema3(){
	double x,y,z;
	double numero_iteraciones;
	double tolerancia;
	cout << "Ingrese el valor inicial de x: "; cin >> x;
	cout << "Ingresa el valor inicial de y: "; cin >> y;
	cout << "Ingresa el valor inicial de z: "; cin >> z;
	cout << "Ingrese el numero maximo de iteraciones: "; cin >> numero_iteraciones;
	cout << "ingrese  la tolerancia: "; cin >> tolerancia;
	
	vector < tabla > soluciones;
	tabla Iteracion;
	
	//Valores iniciales
	Iteracion.iteracion = 0;
	Iteracion.x.resize(3);
	
	for (int i = 0; i < 3; i ++) Iteracion.x[i].resize(1);
	Iteracion.x[0][0] = x;
	Iteracion.x[1][0] = y;
	Iteracion.x[2][0] = z;


	//Valores para la matriz jacobiana
	Iteracion.matriz_jacobiana.resize(3);
	for (int i = 0 ; i < 3; i ++){
		Iteracion.matriz_jacobiana[i].resize(3);
	} 
	Iteracion.matriz_jacobiana[0][0] = EvaluacionDerivadaEcuacionUnoSistemaTresX(x);
	Iteracion.matriz_jacobiana[0][1] = EvaluacionDerivadaEcuacionUnoSistemaTresY(y);
	Iteracion.matriz_jacobiana[0][2] = EvaluacionDerivadaEcuacionUnoSistemaTresZ(z);
	Iteracion.matriz_jacobiana[1][0] = EvaluacionDerivadaEcuacionDosSistemaTresX(x);
	Iteracion.matriz_jacobiana[1][1] = EvaluacionDerivadaEcuacionDosSistemaTresY(y);
	Iteracion.matriz_jacobiana[1][2] = EvaluacionDerivadaEcuacionDosSistemaTresZ(z);
	Iteracion.matriz_jacobiana[2][0] = EvaluacionDerivadaEcuacionTresSistemaTresX(x);
	Iteracion.matriz_jacobiana[2][1] = EvaluacionDerivadaEcuacionTresSistemaTresY(y);
	Iteracion.matriz_jacobiana[2][2] = EvaluacionDerivadaEcuacionTresSistemaTresZ(z);
	

	//Se llama  a la matriz jacobiana inversa
	
	Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);
	
	//Se evaluan los puntos iniciales en las funciones dadas

	Iteracion.evaluacion.resize(3);
	for (int i = 0; i < 3; i ++) Iteracion.evaluacion[i].resize(1);
	Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaTres(x,y,z);
	Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaTres(x,y,z);
	Iteracion.evaluacion[2][0] = EvaluacionEcuacionTresSistemaTres(x,y,z);

	vector < vector < double >> m_matrices = MultiplicacionMatrices(Iteracion.matriz_inversa,Iteracion.evaluacion);
	Iteracion.operacion.resize(3);
	for (int i = 0; i < 3; i ++) Iteracion.operacion[i].resize(1);

	Iteracion.operacion[0][0] = x- m_matrices[0][0];
	Iteracion.operacion[1][0] = y - m_matrices[1][0];
	Iteracion.operacion[2][0] = z - m_matrices[2][0];

	double m = -1000000;

	for (int i =0 ; i < 3; i ++){
		m = max(m,abs(Iteracion.evaluacion[i][0]));
	}
	Iteracion.error_absoluto = m;
		
	soluciones.push_back(Iteracion);

	for (int i = 1; i <= numero_iteraciones; i ++){
		x = soluciones[i-1].operacion[0][0];
		y = soluciones[i-1].operacion[1][0];
		z = soluciones[i-1].operacion[2][0];

		Iteracion.x[0][0] = x;
		Iteracion.x[1][0] = y;
		Iteracion.x[2][0] = z;
		Iteracion.iteracion = i;

		//Valores para la matriz jacobiana
		Iteracion.matriz_jacobiana[0][0] = EvaluacionDerivadaEcuacionUnoSistemaTresX(x);
		Iteracion.matriz_jacobiana[0][1] = EvaluacionDerivadaEcuacionUnoSistemaTresY(y);
		Iteracion.matriz_jacobiana[0][2] = EvaluacionDerivadaEcuacionUnoSistemaTresZ(z);
		Iteracion.matriz_jacobiana[1][0] = EvaluacionDerivadaEcuacionDosSistemaTresX(x);
		Iteracion.matriz_jacobiana[1][1] = EvaluacionDerivadaEcuacionDosSistemaTresY(y);
		Iteracion.matriz_jacobiana[1][2] = EvaluacionDerivadaEcuacionDosSistemaTresZ(z);
		Iteracion.matriz_jacobiana[2][0] = EvaluacionDerivadaEcuacionTresSistemaTresX(x);
		Iteracion.matriz_jacobiana[2][1] = EvaluacionDerivadaEcuacionTresSistemaTresY(y);
		Iteracion.matriz_jacobiana[2][2] = EvaluacionDerivadaEcuacionTresSistemaTresZ(z);

		//Se llama  a la matriz jacobiana inversa

		Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);

		//Se evaluan los puntos iniciales en las funciones dadas
		

		Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaTres(x,y,z);
		Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaTres(x,y,z);
		Iteracion.evaluacion[2][0] = EvaluacionEcuacionTresSistemaTres(x,y,z);

		
		vector < vector < double >> m_matrices = MultiplicacionMatrices(Iteracion.matriz_inversa,Iteracion.evaluacion);
		Iteracion.operacion[0][0] = x- m_matrices[0][0];
		Iteracion.operacion[1][0] = y - m_matrices[1][0];
		Iteracion.operacion[2][0] = z - m_matrices[2][0];


		double m = -1000000;

		for (int j =0 ; j < 3; j ++){
			m = max(m,abs(Iteracion.evaluacion[j][0]-soluciones[i-1].evaluacion[j][0]));
		}
		Iteracion.error_absoluto = m;
		
		double m1 = -10000000;
		m1 = max(x,y);
		Iteracion.error_relativo  = abs(m/m1);
		
		soluciones.push_back(Iteracion);
		if (abs(Iteracion.evaluacion[0][0]) <= tolerancia and abs(Iteracion.evaluacion[1][0]) <= tolerancia and abs(Iteracion.evaluacion[2][0]) <= tolerancia) break;
	}
	ImprimeResultados(soluciones);
	MostrarResultados(soluciones[soluciones.size()-1].x);

}

void Sistema4(){
	double x,y,z;
	double numero_iteraciones;
	double tolerancia;
	cout << "Ingrese el valor inicial de x: "; cin >> x;
	cout << "Ingresa el valor inicial de y: "; cin >> y;
	cout << "Ingresa el valor inicial de z: "; cin >> z;

	cout << "Ingrese el numero maximo de iteraciones: "; cin >> numero_iteraciones;
	cout << "Ingrese la tolerancia: "; cin >> tolerancia;

	vector < tabla > soluciones;
	tabla Iteracion;
	
	//Valores iniciales
	Iteracion.iteracion = 0;
	Iteracion.x.resize(3);
	
	for (int i = 0; i < 3; i ++) Iteracion.x[i].resize(1);
	Iteracion.x[0][0] = x;
	Iteracion.x[1][0] = y;
	Iteracion.x[2][0] = z;


	//Valores para la matriz jacobiana
	Iteracion.matriz_jacobiana.resize(3);
	for (int i = 0 ; i < 3; i ++){
		Iteracion.matriz_jacobiana[i].resize(3);
	} 
	Iteracion.matriz_jacobiana[0][0] = EvaluacionDerivadaEcuacionUnoSistemaCuatroX(x);
	Iteracion.matriz_jacobiana[0][1] = EvaluacionDerivadaEcuacionUnoSistemaCuatroY(y);
	Iteracion.matriz_jacobiana[0][2] = EvaluacionDerivadaEcuacionUnoSistemaCuatroZ();
	Iteracion.matriz_jacobiana[1][0] = EvaluacionDerivadaEcuacionDosSistemaCuatroX(x);
	Iteracion.matriz_jacobiana[1][1] = EvaluacionDerivadaEcuacionDosSistemaCuatroY();
	Iteracion.matriz_jacobiana[1][2] = EvaluacionDerivadaEcuacionDosSistemaCuatroZ();
	Iteracion.matriz_jacobiana[2][0] = EvaluacionDerivadaEcuacionTresSistemaCuatroX(x);
	Iteracion.matriz_jacobiana[2][1] = EvaluacionDerivadaEcuacionTresSistemaCuatroY(y);
	Iteracion.matriz_jacobiana[2][2] = EvaluacionDerivadaEcuacionTresSistemaCuatroZ(z);
	

	//Se llama  a la matriz jacobiana inversa
	
	Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);
	
	//Se evaluan los puntos iniciales en las funciones dadas

	Iteracion.evaluacion.resize(3);
	for (int i = 0; i < 3; i ++) Iteracion.evaluacion[i].resize(1);
	Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaCuatro(x,y);
	Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaCuatro(x,y);
	Iteracion.evaluacion[2][0] = EvaluacionEcuacionTresSistemaCuatro(x,y,z);

	vector < vector < double >> m_matrices = MultiplicacionMatrices(Iteracion.matriz_inversa,Iteracion.evaluacion);
	Iteracion.operacion.resize(3);
	for (int i = 0; i < 3; i ++) Iteracion.operacion[i].resize(1);

	Iteracion.operacion[0][0] = x- m_matrices[0][0];
	Iteracion.operacion[1][0] = y - m_matrices[1][0];
	Iteracion.operacion[2][0] = z - m_matrices[2][0];

	double m = -1000000;

	for (int i =0 ; i < 3; i ++){
		m = max(m,abs(Iteracion.evaluacion[i][0]));
	}
	Iteracion.error_absoluto = m;
		
	soluciones.push_back(Iteracion);

	for (int i = 1; i <= numero_iteraciones; i ++){
		x = soluciones[i-1].operacion[0][0];
		y = soluciones[i-1].operacion[1][0];
		z = soluciones[i-1].operacion[2][0];

		Iteracion.x[0][0] = x;
		Iteracion.x[1][0] = y;
		Iteracion.x[2][0] = z;
		Iteracion.iteracion = i;

		//Valores para la matriz jacobiana
		
		Iteracion.matriz_jacobiana[0][0] = EvaluacionDerivadaEcuacionUnoSistemaCuatroX(x);
		Iteracion.matriz_jacobiana[0][1] = EvaluacionDerivadaEcuacionUnoSistemaCuatroY(y);
		Iteracion.matriz_jacobiana[0][2] = EvaluacionDerivadaEcuacionUnoSistemaCuatroZ();
		Iteracion.matriz_jacobiana[1][0] = EvaluacionDerivadaEcuacionDosSistemaCuatroX(x);
		Iteracion.matriz_jacobiana[1][1] = EvaluacionDerivadaEcuacionDosSistemaCuatroY();
		Iteracion.matriz_jacobiana[1][2] = EvaluacionDerivadaEcuacionDosSistemaCuatroZ();
		Iteracion.matriz_jacobiana[2][0] = EvaluacionDerivadaEcuacionTresSistemaCuatroX(x);
		Iteracion.matriz_jacobiana[2][1] = EvaluacionDerivadaEcuacionTresSistemaCuatroY(y);
		Iteracion.matriz_jacobiana[2][2] = EvaluacionDerivadaEcuacionTresSistemaCuatroZ(z);
		//Se llama  a la matriz jacobiana inversa

		Iteracion.matriz_inversa = Inversa(Iteracion.matriz_jacobiana);

		//Se evaluan los puntos iniciales en las funciones dadas

		Iteracion.evaluacion[0][0] = EvaluacionEcuacionUnoSistemaCuatro(x,y);
		Iteracion.evaluacion[1][0] = EvaluacionEcuacionDosSistemaCuatro(x,y);
		Iteracion.evaluacion[2][0] = EvaluacionEcuacionTresSistemaCuatro(x,y,z);
		
		

		vector < vector < double >> m_matrices = MultiplicacionMatrices(Iteracion.matriz_inversa,Iteracion.evaluacion);
		
		Iteracion.operacion[0][0] = x- m_matrices[0][0];
		Iteracion.operacion[1][0] = y - m_matrices[1][0];
		Iteracion.operacion[2][0] = z - m_matrices[2][0];


		double m = -1000000;

		for (int j =0 ; j < 3; j ++){
			m = max(m,abs(Iteracion.evaluacion[j][0]-soluciones[i-1].evaluacion[j][0]));
		}
		Iteracion.error_absoluto = m;
		
		double m1 = -10000000;
		m1 = max(x,y);
		Iteracion.error_relativo  = abs(m/m1);
		
		soluciones.push_back(Iteracion);
			
		if (abs(Iteracion.evaluacion[0][0]) <= tolerancia and abs(Iteracion.evaluacion[1][0]) <= tolerancia and abs(Iteracion.evaluacion[2][0]) <= tolerancia) break;		
	}
	ImprimeResultados(soluciones);
	MostrarResultados(soluciones[soluciones.size()-1].x);
}
int main (){
	int menu_principal = 1;
	while (menu_principal != 2){
		MenuPrincipal();
		cin >> menu_principal;
		int menu_sistemas = 1;
		if (menu_principal == 1){
			while (menu_sistemas == 1 or menu_sistemas == 2 or menu_sistemas == 3 or menu_sistemas == 4){
				MenuSistemas();
				cin >> menu_sistemas;
				if (menu_sistemas == 1){
					cout << "Se resolvera el sistema 1" << endl;
					Sistema1();
					int menu_datos = 1;
					while (menu_datos == 1){
						MenuCambioDatos();
						cin >> menu_datos;
						if (menu_datos == 1)
							Sistema1();
					}
				}
				else if (menu_sistemas == 2){
					cout << "Se resolvera el sistema  2" << endl;
					Sistema2();
					int menu_datos = 1;
					while (menu_datos == 1){
						MenuCambioDatos();
						cin >> menu_datos;
						if (menu_datos == 1)
							Sistema2();
					}
				}
				else if (menu_sistemas == 3){
					cout << "Se resolvera el sistema 3" << endl;
					Sistema3();
					int menu_datos = 1;
					while (menu_datos == 1){
						MenuCambioDatos();
						cin >> menu_datos;
						if (menu_datos == 1)
							Sistema3();
					}
				}
				else if (menu_sistemas == 4){
					cout << "Se resolvera el sistema 4" << endl;
					Sistema4();
					int menu_datos = 1;
					while (menu_datos == 1){
						MenuCambioDatos();
						cin >> menu_datos;
						if (menu_datos == 1)
							Sistema4();
					}

				}
				else {
					cout << "Adios" << endl;
				}
			}
		}
	}	
	
	return 0;
}
