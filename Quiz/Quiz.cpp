#include <iostream>
#include <stdlib.h> //para utlizar system
#include <thread> //para utlizar sleep
#include <chrono> // Para usar temporizador
using namespace std;

//Metodos
void limpiarPantalla();
int mostrarMenu();
void crearPreguntas();
void jugar();
//preguntas

struct preguntas
{
	int bien;
	string pregunta, r1, r2, r3;
}p[5];

//clase 

class Ranking {
private:
	static const int MAX_JUGADORES = 10;

	struct Jugador {
		string nombre;
		int tiempo;
	};

	Jugador ranking[MAX_JUGADORES];
	int cantidadJugadores;


public:
	Ranking() : cantidadJugadores(0) {} 

	void guardarNombre(const string& nombre, int tiempo) {
		if (cantidadJugadores < MAX_JUGADORES) {
			ranking[cantidadJugadores].nombre = nombre;
			ranking[cantidadJugadores].tiempo = tiempo;
			cantidadJugadores++;
			ordenarPorTiempo();
		}
		else {
			cout << "El Ranking solo acepta a los primeros 10" << endl;
		}
	}

	void mostrarNombres() const {
		cout << "Ranking del QUIZ:" << endl;
		for (int i = 0; i < cantidadJugadores; ++i) {
			cout << (i + 1) << ". " << ranking[i].nombre << "...............  " << ranking[i].tiempo << " segundos" << endl;
		}
	}

	void ordenarPorTiempo() {
		for (int i = 0; i < cantidadJugadores - 1; ++i) {
			for (int j = i + 1; j < cantidadJugadores; ++j) {
				if (ranking[i].tiempo > ranking[j].tiempo) {
					Jugador temp = ranking[i];
					ranking[i] = ranking[j];
					ranking[j] = temp;
				}
			}
		}
	}
};

//variable global
Ranking personas;

//Corazon
int main()
{
	
	crearPreguntas();
	while (true) {

		if (mostrarMenu() == 0) {
			return 0;
		}
	}
	return 0;
}


//Desarollo de metodos

void limpiarPantalla()
{
	int estado = system("cls");
	if (estado == -1) {
		mostrarMenu();
	}
}

int mostrarMenu() {

	
	limpiarPantalla();
	int opcion;
	cout << "QUIZ" << endl;
	cout << "\n";
	cout << "1) Empezar" << endl;
	cout << "2) Salir" << endl;
	cout << "3) Ver Ranking" << endl;
	cin >> opcion;

	switch (opcion)
	{
	case 1:
		limpiarPantalla();
		jugar();
		break;
	case 2:
		return 0;
		break;
	case 3:
		limpiarPantalla();
		personas.mostrarNombres();
		cout << "\n";
		cout << "\n";
		system("Pause");
		limpiarPantalla();
		mostrarMenu();
		break;

	default: 
		cout << "No existe esa opcion\n";
		cout << "En breve se volvera a cargar el menu" << endl;
		_Thrd_sleep_for(2000);
		mostrarMenu();
		break;
	}
}

void jugar() {

	
	int puntaje = 0;
	srand((unsigned)time(0)); //genera numero aleatorios
	int aleatorio, aleatorio_arreglo[5];
	bool repetido = false;

	auto inicio = chrono::high_resolution_clock::now();//inicia temporizador

	for (int i = 0; i < 5; i++) {

		do {
			repetido = false;
			aleatorio = rand() % (4 - 0 + 1) + 0; //genera un numero aleatorio entre 0 y 4
			for (int j = 0; j < i; j++) {
				if (aleatorio_arreglo[j] == aleatorio) {
					repetido = true;
				}
			}
		} while (repetido); // este do-while sirve para verificar que el numero aleatorio no haya salido antes, y si ya se uso se recorre para generear un nuevo numero aleatorio


		aleatorio_arreglo[i] = aleatorio;
		int respuesta;

		cout << p[aleatorio].pregunta << endl;
		cout << p[aleatorio].r1 << endl;
		cout << p[aleatorio].r2 << endl;
		cout << p[aleatorio].r3 << endl;
		cin >> respuesta;

		if (respuesta == p[aleatorio].bien) {
			cout << "Correcto" << endl;
			puntaje += 10;
		}
		else {
			cout << "Incorrecto" << endl;
			cout << "La opcion Correcta es la: " << p[aleatorio].bien << endl;
		}

		if (i == 4) { //verifica si ya termino el numero de preguntas

			auto fin = chrono::high_resolution_clock::now();
			auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio).count();
			//termina el temporizador

			if (puntaje == 50) {
				cout << "Felicidades por terminar el quiz con el puntaje perfecto" << endl;
				cout << "Tiempo transcurrido: " << duracion << " segundos." << endl;
				cout << "Agrega tu nombre al salon de la fama" << endl;
				string nombre;
				cin >> nombre;
				personas.guardarNombre(nombre,duracion);
			}
			else {
				cout << "Tu puntaje es de " << puntaje << "/50 puntos." << endl;
			}
			system("pause"); 
			return;

		}else{
			cout << "Desea continuar s/n." << endl;
			char continuar;
			cin >> continuar;
			limpiarPantalla();

			auto fin = chrono::high_resolution_clock::now();
			auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio).count();
			//termina el temporizador

			if (continuar != 's') {
				cout << "Tu puntaje es de " << puntaje << "/" << (i + 1) * 10 << "puntos." << endl;
				cout << "Tiempo transcurrido: " << duracion << " segundos." << endl;
				system("pause");
				return;
			}
		}
		
	}
}


void crearPreguntas() {
	p[0].pregunta = "Que es un compilador en programacion?";
	p[0].r1 = "1) Un software que ejecuta programas directamente";
	p[0].r2 = "2) Un software que traduce codigo fuente a codigo maquina";
	p[0].r3 = "3) Un editor de texto para escribir codigo";
	p[0].bien = 2;

	p[1].pregunta = "Cual es el proposito principal de un sistema operativo?";
	p[1].r1 = "1) Proveer servicios de red";
	p[1].r2 = "2) Administrar los recursos de hardware y software de una computadora";
	p[1].r3 = "3) Compilar programas";
	p[1].bien = 2;

	p[2].pregunta = "Que es una variable en programacion?";
	p[2].r1 = "1) Un tipo de dato que nunca cambia";
	p[2].r2 = "2) Un espacio de memoria para almacenar valores que pueden cambiar";
	p[2].r3 = "3) Una funcion matematica en un programa";
	p[2].bien = 2;

	p[3].pregunta = "Cual de los siguientes lenguajes de programacion es conocido por su uso en inteligencia artificial?";
	p[3].r1 = "1) C++";
	p[3].r2 = "2) Python";
	p[3].r3 = "3) CSS";
	p[3].bien = 2;

	p[4].pregunta = "Que significa HTML?";
	p[4].r1 = "1) Hypertext Markup Language";
	p[4].r2 = "2) Hyperlink and Text Markup Language";
	p[4].r3 = "3) Home Tool Markup Language";
	p[4].bien = 1;
}

