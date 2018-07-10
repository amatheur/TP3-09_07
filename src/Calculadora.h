#ifndef __CALCULADORA_H__
#define __CALCULADORA_H__

#include "Programa.h"
#include "Ventana.h"
#include <iostream>
#include <vector>
#include <string>

class Calculadora {

public:

    Calculadora();

    ~Calculadora();

    Calculadora(const Programa &prog, const Rutina &rut, int tam);

    bool Finalizo() const;

    void EjecutarUnPaso();

    void AsignarVariable(const Variable &var, int val);

    int InstanteActual() const;

    int IndiceInstActual() const;

    int ValorHistorico(Variable var, int inst) const;

    int ValorActual(Variable var) const;

    Pila<int> pila() const;

    Calculadora& operator=(const Calculadora& c);

private:
    struct InstConIt;

    typedef tuple<Lista_Enlazada<Ventana<tuple<int, int>>>::iterator, Lista_Enlazada<tuple<int, int>>> Var;
    typedef Lista_Enlazada<InstConIt> Rut;
    typedef DiccionarioTrie<tuple<Lista_Enlazada<Ventana<tuple<int, int>>>::iterator,Lista_Enlazada<tuple<int, int>>>>::ItDiccTrie ItVar;
    typedef DiccionarioTrie<Lista_Enlazada<InstConIt>>::ItDiccTrie ItRut;
    typedef Lista_Enlazada<Ventana<tuple<int, int>>> ListVent;
    typedef Lista_Enlazada<Ventana<tuple<int, int>>>::iterator ItListVent;



    struct InstConIt{

        Operacion _op;
        ItVar _var;
        ItRut _rut;
        int _val;

        InstConIt(Operacion op, const ItVar &var, ItRut rut, const int val);

    };

    DiccionarioTrie<Rut> _programa;

    DiccionarioTrie<Var> _variables;

    ListVent _ventanas;

    ItRut _rutinaActual;

    Rut::iterator _instruccionAEjecutar;

    int _nInstruccionActual;

    int _instanteActual;

    Pila<int> _pila;

    int _tamVentana;

    int _cantRut;

    int _longRut;

    void Sigo();

    int DevolverYSacarDePila();

    int BuscarEnVentana(const Ventana<tuple<int, int>>& v, int instante, int inicio, int fin) const;

    int BuscarEnLista(const Lista_Enlazada<tuple<int, int>> &ls, int instante, int inicio, int fin) const;

    //Pre: pos esta en rango.
    tuple<int, int> PosicionLista(const Lista_Enlazada<tuple<int, int>> &ls, int pos) const;
};

#endif /*__CALCULADORA_H__*/
