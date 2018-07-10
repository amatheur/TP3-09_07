#include "Calculadora.h"

Calculadora::Calculadora() {
}

Calculadora::~Calculadora() {
}

Calculadora::Calculadora(const Programa &prog,const Rutina &rut, int tam) {
    _instanteActual = 0;
    _nInstruccionActual = 0;
    _tamVentana = tam;
    _cantRut = prog.CantidadRutinas();
    if(_cantRut > 0) {
        int nRutina = 0;
        Programa::ItPrograma itProg = prog.CrearIt();
        int nInstruccion;

        while (nRutina < prog.CantidadRutinas()) {

            nInstruccion = 0;

            Rutina nombreRutActual = get<0>(itProg.Actual());

            ItRut itNuevaRut;

            if (_programa.Definido(nombreRutActual)) {

                itNuevaRut = _programa.BuscarIterador(nombreRutActual);
            } else {
                Rut list;

                itNuevaRut = _programa.Definir(nombreRutActual, list);
            }
            Lista_Enlazada<Instruccion>::iterator itInstActual = (get<1>(itProg.Actual())).begin();

            while (nInstruccion < (get<1>(itProg.Actual())).size()) {

                Instruccion instActual = *(itInstActual);
                if (instActual.operacion() == oWrite or instActual.operacion() == oRead) {
                    ItVar itVariable;
                    if (!_variables.Definido(instActual.variable())) {
                        _ventanas.push_front(Ventana<tuple<int, int>>(tam));
                        ItListVent itVentana = _ventanas.begin();
                        Lista_Enlazada<tuple<int, int>> listVar;
                        Var nuevaVar(itVentana, listVar);
                        itVariable = _variables.Definir(instActual.variable(), nuevaVar);
                    } else {
                        itVariable = _variables.BuscarIterador(instActual.variable());
                    }
                    InstConIt instConIt(instActual.operacion(), itVariable, _programa.CrearIt(), 0);
                    (get<1>(itNuevaRut.Actual())).push_back(instConIt);

                } else if (instActual.operacion() == oJump or instActual.operacion() == oJumpz) {
                    ItRut itRutina;
                    if (!_programa.Definido(instActual.rutina())) {
                        Rut nuevaRut;
                        itRutina = _programa.Definir(instActual.rutina(), nuevaRut);
                    } else {
                        itRutina = _programa.BuscarIterador(instActual.rutina());
                    }
                    InstConIt instConIt(instActual.operacion(), _variables.CrearIt(), itRutina, 0);
                    (get<1>(itNuevaRut.Actual())).push_back(instConIt);
                } else if (instActual.operacion() == oPush) {
                    int val = instActual.Valor();
                    InstConIt instConIt(oPush, _variables.CrearIt(), _programa.CrearIt(), val);
                    get<1>(itNuevaRut.Actual()).push_back(instConIt);

                } else {
                    InstConIt instConIt(instActual.operacion(), _variables.CrearIt(), _programa.CrearIt(), 0);
                    get<1>(itNuevaRut.Actual()).push_back(instConIt);
                }
                nInstruccion++;
                itInstActual++;
            }
            itProg.Avanzar();
            nRutina++;
        }
        _rutinaActual = _programa.BuscarIterador(rut);
        _longRut = get<1>(_rutinaActual.Actual()).size();
        _instruccionAEjecutar = get<1>(_rutinaActual.Actual()).begin();
    }
}

bool Calculadora::Finalizo() const{
    bool algunaRutina = _cantRut == 0;
    bool enRango = !(_nInstruccionActual < _longRut);
    return enRango or algunaRutina;
}

void Calculadora::Sigo(){
    if(_nInstruccionActual < get<1>(_rutinaActual.Actual()).size()){
        _instruccionAEjecutar++;
    }
}

int Calculadora::DevolverYSacarDePila() {
    int res = 0;
    if(!_pila.empty()){
        res = _pila.top();
        _pila.pop();
    }
    return res;
}

void Calculadora::EjecutarUnPaso() {
    InstConIt instActual = *(_instruccionAEjecutar);
    Operacion operacionActual = instActual._op;

    int s1 = 0;
    int s2 = 0;

    tuple<int, int> aRegistrar;

    switch (operacionActual){
        case oPush:
            _pila.push(instActual._val);
            _nInstruccionActual++;
            Sigo();
            break;
        case oAdd:
            s1 = DevolverYSacarDePila();
            s2 = DevolverYSacarDePila();
            _pila.push(s1 + s2);
            _nInstruccionActual++;
            Sigo();
            break;
        case oSub:
            s1 = DevolverYSacarDePila();
            s2 = DevolverYSacarDePila();
            _pila.push(s2 - s1);
            _nInstruccionActual++;
            Sigo();
            break;
        case oMul:
            s1 = DevolverYSacarDePila();
            s2 = DevolverYSacarDePila();
            _pila.push(s2*s1);
            _nInstruccionActual++;
            Sigo();
            break;
        case oWrite:
            s1 = DevolverYSacarDePila();
            get<0>(aRegistrar) = _instanteActual;
            get<1>(aRegistrar) = s1;
            get<1>(get<1>(instActual._var.Actual())).push_back(aRegistrar);
            (*(get<0>(get<1>(instActual._var.Actual())))).registrar(aRegistrar);
            _nInstruccionActual++;
            Sigo();
            break;
        case oRead:
            _pila.push(get<1>(get<1>(get<1>(instActual._var.Actual())).back()));
            _nInstruccionActual++;
            Sigo();
            break;
        case oJump:
            _rutinaActual = instActual._rut;
            _longRut = get<1>(_rutinaActual.Actual()).size();
            _nInstruccionActual = 0;
            if(_nInstruccionActual < get<1>(_rutinaActual.Actual()).size() - 1){
                _instruccionAEjecutar = get<1>(_rutinaActual.Actual()).begin();
            }
            break;
        case oJumpz:
            s1 = DevolverYSacarDePila();
            if(s1 == 0){
                _rutinaActual = instActual._rut;
                _longRut = get<1>(_rutinaActual.Actual()).size();
                _nInstruccionActual = 0;
                if(_nInstruccionActual < get<1>(_rutinaActual.Actual()).size() - 1){
                    _instruccionAEjecutar = get<1>(_rutinaActual.Actual()).begin();
                }
            } else {
                _nInstruccionActual++;
                Sigo();
            }
            break;
    }
    _instanteActual++;
}

void Calculadora::AsignarVariable(const Variable &var, int val) {
    if(!_variables.Definido(var)){
        Lista_Enlazada<tuple<int, int>> lsDef;
        _ventanas.push_back(Ventana<tuple<int, int>>(_tamVentana));
        Var significado(_ventanas.end(), lsDef);
        _variables.Definir(var, significado);
    }
    Lista_Enlazada<tuple<int, int>> &ls = get<1>(_variables.Significado(var));
    Ventana<tuple<int, int>> &v = *(get<0>(_variables.Significado(var)));

    tuple<int, int> aRegistrar(_instanteActual, val);
    if(get<0>(ls.back()) != _instanteActual){
        ls.push_back(aRegistrar);
        v.registrar(aRegistrar);
    } else {
        get<1>(ls.back()) = val;
        if(v.tam() > 0) {
            get<1>(v.operator[](v.tam() - 1)) = val;
        } else{
            v.registrar(aRegistrar);
        }
    }

}

int Calculadora::InstanteActual() const{
    return _instanteActual;
}

int Calculadora::IndiceInstActual() const {
    return _nInstruccionActual;
}

int Calculadora::BuscarEnVentana(const Ventana<tuple<int, int>> &v, int instante, int inicio, int fin) const{
    if(inicio == fin){
        return get<1>(v[inicio]);
    }
    int medio = (inicio + fin) / 2;
    if(get<0>(v[medio]) <= instante){
        if(get<0>(v[medio + 1]) > instante){
            return get<1>(v[medio]);
        } else {
            return BuscarEnVentana(v, instante, medio + 1, fin);
        }
    } else {
        return BuscarEnVentana(v, instante, inicio, medio);
    }
}

int Calculadora::ValorHistorico(Variable var, int inst) const{
    if(inst >= get<0>((*(get<0>(_variables.Significado(var))))[0])){
        return BuscarEnVentana((*(get<0>(_variables.Significado(var)))), inst, 0, _tamVentana);
    } else {
        return BuscarEnLista(get<1>(_variables.Significado(var)), inst, 0 , get<1>(_variables.Significado(var)).size());
    }
}

int Calculadora::ValorActual(Variable var) const{
    return get<1>(get<1>(_variables.Significado(var)).back());
}

Pila<int> Calculadora::pila() const {
    return _pila;
}

Calculadora::InstConIt::InstConIt(Operacion op, const ItVar &var, ItRut rut, const int val) {
    _op = op;
    _var = var;
    _rut = rut;
    _val = val;
}

tuple<int, int> Calculadora::PosicionLista(const Lista_Enlazada<tuple<int, int>> &ls, int pos) const{
    auto it = ls.begin();
    advance(it, pos);
    return *it;
}

int Calculadora::BuscarEnLista(const Lista_Enlazada<tuple<int, int>> &ls, int instante, int inicio, int fin) const{
    if(inicio == fin){
        return get<1>(PosicionLista(ls, inicio));
    }
    int medio = (inicio + fin) / 2;
    if(get<0>(PosicionLista(ls, medio)) <= instante){
        if(get<0>(PosicionLista(ls, medio + 1)) > instante){
            return get<1>(PosicionLista(ls, medio));
        } else {
            return BuscarEnLista(ls, instante, medio + 1, fin);
        }
    } else {
        return BuscarEnLista(ls, instante, inicio, medio);
    }
}

Calculadora& Calculadora::operator=(const Calculadora& c){
    _programa = c._programa;
    _variables = c._variables;
    _ventanas = c._ventanas;
    _rutinaActual = c._rutinaActual;
    _instruccionAEjecutar = c._instruccionAEjecutar;
    _nInstruccionActual = c._nInstruccionActual;
    _instanteActual = c._instanteActual;
    _pila = c._pila;
    _tamVentana = c._tamVentana;
    _cantRut = c._cantRut;
    _longRut = c._longRut;
}