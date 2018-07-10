//
// Created by Manuel on 4/7/2018.
//

#include "Driver.h"
#include "Calculadora.h"

Driver::Driver() {
    _prog = Programa();
}

Driver::~Driver() {

}

void Driver::begin(const string &rutina) {
    _actual = rutina;
}

void Driver::end(const string &utina) {
    _actual = "";
}

void Driver::push(int n) {
    _prog.AgregarInstruccion(_actual,Instruccion(n));
}

void Driver::add() {
    _prog.AgregarInstruccion(_actual,Instruccion(oAdd));
}

void Driver::sub() {
    _prog.AgregarInstruccion(_actual,Instruccion(oSub));
}

void Driver::mul() {
    _prog.AgregarInstruccion(_actual,Instruccion(oMul));
}

void Driver::read(const string &variable) {
    _prog.AgregarInstruccion(_actual,Instruccion(oRead, variable));
}

void Driver::write(const string &variable) {
    _prog.AgregarInstruccion(_actual,Instruccion(oWrite, variable));
}

void Driver::jump(const string &rutina) {
    _prog.AgregarInstruccion(_actual,Instruccion(oJump,rutina));
}

void Driver::jumpz(const string &rutina) {
    _prog.AgregarInstruccion(_actual,Instruccion(oJumpz,rutina));
}

void Driver::comenzarEjecucion(const string &rutina, int capacidadVentana) {
    _calc = Calculadora(_prog, rutina, capacidadVentana);
}

void Driver::asignarVariable(const string &idVariable, int valor) {
    _calc.AsignarVariable(idVariable, valor);
}

bool Driver::ejecucionFinalizada() const {
    return _calc.Finalizo();
}

void Driver::ejecutarInstruccionActual() {
    _calc.EjecutarUnPaso();
}

int Driver::topePila() const {
    if(!_calc.pila().empty()) {
        return _calc.pila().top();
    }else{
        return 0;
    }
}

int Driver::valorVariable(const string &idVariable) const {
    return _calc.ValorActual(idVariable);
}

int Driver::valorHistoricoVariable(const string &idVariable, int t) const {
    return _calc.ValorHistorico(idVariable, t);
}

int Driver::instanteActual() const {
    return _calc.InstanteActual();
}
