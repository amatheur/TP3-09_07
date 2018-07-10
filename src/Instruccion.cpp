#include "Instruccion.h"
#include "Utiles.h"

Instruccion::Instruccion(Operacion op){
    _op = op;
}

Instruccion::Instruccion(int val) {
    _op = oPush;
    _val = val;
}

Instruccion::Instruccion(Operacion op, std::string nombre){
    _op = op;
    if(op == oJump or op == oJumpz){
        _rut = nombre;
    } else{
        _var = nombre;
    }
}

Rutina Instruccion::rutina() const {
    return _rut;
}

Variable Instruccion::variable() const {
    return _var;
}

Operacion Instruccion::operacion() const {
    return _op;
}

int Instruccion::Valor() const {
    return _val;
}


/*
Instruccion::Instruccion(Operacion operacion, int valor){
    _operacion = operacion;
    _valor = valor;
}

Instruccion::Instruccion(Operacion operacion) {
    _operacion = operacion;
}

Instruccion::Instruccion(Operacion operacion, Id nombre) {
    _operacion = operacion;
    _nombre = nombre;
}

Operacion Instruccion::operacion() const {
    return _operacion;
}

int Instruccion::valor() const {
    return _valor;
}

Id Instruccion::nombre() const {
    return _nombre;
}



 */