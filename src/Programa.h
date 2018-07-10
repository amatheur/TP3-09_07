#ifndef __PROGRAMA_H__
#define __PROGRAMA_H__

#include <iostream>
#include <vector>
#include <string>
#include "DiccionarioTrie.h"
#include "Instruccion.h"


using namespace std;
// La clase Programa sirve para representar una secuencia de instrucciones.
//
//     Programa programa;
//
//     programa.agregarInstruccion("A", Instruccion(OP_PUSH, 10));
//     programa.agregarInstruccion("A", Instruccion(OP_PUSH, 20));
//     programa.agregarInstruccion("A", Instruccion(OP_ADD));
//     programa.agregarInstruccion("A", Instruccion(OP_JUMP, "A"));
//
//     programa.agregarInstruccion("B", Instruccion(OP_PUSH, 30));
//     programa.agregarInstruccion("B", Instruccion(OP_WRITE, "x"));
//
// Corresponde a las siguientes rutinas:
//
//     --- A ---
//       push(10)
//       push(20)
//       add
//       jump(A)
//
//     --- B ---
//       push(30)
//       write(x)

class Programa {

public:
	Programa();

	~Programa();

    void AgregarInstruccion(Rutina rut, Instruccion inst);

    int CantidadRutinas() const;

    int Longitud(Rutina rut) const;

    Instruccion instruccion(Rutina rut, int indice) const;

	Programa& operator=(const Programa &p);



    class ItPrograma{

        friend class Programa;

    public:

        tuple<Rutina, Lista_Enlazada<Instruccion>&> Actual();

		tuple<Rutina, Lista_Enlazada<Instruccion>&> Actual() const;

		void Avanzar();

		ItPrograma& operator=(const ItPrograma &it);

		void AgregarInst(Instruccion &inst);

    private:

        DiccionarioTrie<Lista_Enlazada<Instruccion>>::ItDiccTrie _it;

		ItPrograma(DiccionarioTrie<Lista_Enlazada<Instruccion>>::ItDiccTrie it);
    };

    ItPrograma CrearIt() const;

	ItPrograma BuscarIterador(const Rutina &rut);

	ItPrograma ItInvalido();

private:

	DiccionarioTrie<Lista_Enlazada<Instruccion>> _rutinas;

	int _cantRut;


    

};

#endif /*__PROGRAMA_H__*/

