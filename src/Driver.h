#ifndef DRIVER_CALCULADORA_H
#define DRIVER_CALCULADORA_H

#include <string>
#include "Calculadora.h"

using namespace std;

class Driver {
public:
	Driver();
	~Driver();

	// Operaciones para agregar instrucciones
	void begin(const string &rutina);
	void end(const string &rutina);
	void push(int n);
	void add();
	void sub();
	void mul();
	void read(const string &variable);
	void write(const string &variable);
	void jump(const string &rutina);
	void jumpz(const string &rutina);

	// Operaciones para ejecutar programas
	void comenzarEjecucion(const string &rutina, int capacidadVentana);
	void asignarVariable(const string &idVariable, int valor);
	bool ejecucionFinalizada() const;
	void ejecutarInstruccionActual();
	int topePila() const; // Si la pila está vacía, devuelve 0.
	int valorVariable(const string &idVariable) const;
	int valorHistoricoVariable(const string &idVariable, int t) const;
	int instanteActual() const;

private:

	Programa _prog;
	Rutina _actual;
	Calculadora _calc;
};

#endif
