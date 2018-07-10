#include "Programa.h"

Programa::Programa() {
    _rutinas = DiccionarioTrie<Lista_Enlazada<Instruccion>>();
    _cantRut = 0;
}

Programa::~Programa() {}

int Programa::CantidadRutinas() const {
    return _cantRut;
}

void Programa::AgregarInstruccion(Rutina rut, Instruccion inst) {
    if(_rutinas.Definido(rut)){
        _rutinas.Significado(rut).push_back(inst);
    } else {
        Lista_Enlazada<Instruccion> list;
        list.push_back(inst);
        _rutinas.Definir(rut, list);
        _cantRut ++;
    }
}

int Programa::Longitud(Rutina rut) const {
    return _rutinas.Significado(rut).size();
}

Instruccion Programa::instruccion(Rutina rut, int indice) const {
    Lista_Enlazada<Instruccion>::iterator it = _rutinas.Significado(rut).begin();
    advance(it, indice);
    return *(it);
}

Programa::ItPrograma::ItPrograma(DiccionarioTrie<Lista_Enlazada<Instruccion>>::ItDiccTrie it) {
    _it = it;
}


Programa::ItPrograma Programa::CrearIt() const{
    DiccionarioTrie<Lista_Enlazada<Instruccion>>::ItDiccTrie it = _rutinas.CrearIt();
    return ItPrograma(it);
}

tuple<Rutina, Lista_Enlazada<Instruccion>&> Programa::ItPrograma::Actual() {
    return _it.Actual();
}

tuple<Rutina, Lista_Enlazada<Instruccion>&> Programa::ItPrograma::Actual() const{
    return _it.Actual();
}

void Programa::ItPrograma::Avanzar() {
    _it.Actual();
}
Programa::ItPrograma Programa::BuscarIterador(const Rutina &rut) {
    return ItPrograma(_rutinas.BuscarIterador(rut));
}

Programa::ItPrograma& Programa::ItPrograma::operator=(const ItPrograma &it) {
    _it = it._it;
}

Programa& Programa::operator=(const Programa &p){
    _rutinas = p._rutinas;
    _cantRut = p._cantRut;
}

Programa::ItPrograma Programa::ItInvalido(){
    return _rutinas.ItInvalido();
}

void Programa::ItPrograma::AgregarInst(Instruccion &inst) {
    get<1>(Actual()).push_back(inst);
}