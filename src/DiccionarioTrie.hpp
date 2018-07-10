template <typename T>
DiccionarioTrie<T>::DiccionarioTrie() {
    _raiz = NULL;
}

template <typename T>
DiccionarioTrie<T>::Nodo::Nodo() {
    significado = NULL;
    padre = NULL;
    siguientes = new Nodo*[256];
    for(int i = 0; i < 256; i++){
        siguientes[i] = NULL;
    }
}

template <typename T>
DiccionarioTrie<T>::~DiccionarioTrie(){
    _destroy(_raiz);
}

template <typename T>
typename DiccionarioTrie<T>::ItDiccTrie DiccionarioTrie<T>::Definir(const string& clave, T significado) {
    if (_raiz == NULL) {
        _raiz = new Nodo;
    }
    Nodo* actual = _raiz;
    Nodo* anterior = NULL;

    for (int i = 0; i < clave.size(); i++) {
        if (actual->siguientes[int(clave[i])] == NULL) {
            actual->siguientes[int(clave[i])] = new Nodo;
        }
        if(actual->padre == NULL){
            actual->padre = anterior;
        }
        anterior = actual;
        actual = actual->siguientes[int(clave[i])];
    }
    actual->padre = anterior;
    actual->significado = new T(significado);

    return ItDiccTrie(actual, clave);
}


template <typename T>
bool DiccionarioTrie<T>::Definido(const string &clave) const{
    Nodo *actual = _raiz;
    if (actual == NULL) {
        return false;
    }
    if(clave.size() == 0){
        if(actual->significado == NULL){
            return false;
        } else{
            return true;
        }
    }
    for (int i = 0; i < clave.size(); i++) {
        if (actual->siguientes[int(clave[i])] == NULL) {
            return false;
        } else {
            actual = actual->siguientes[int(clave[i])];
        }
    }
    if (actual->significado == NULL) {
        return false;
    }else{
        return true;
    }
}



template <typename T>
T& DiccionarioTrie<T>::Significado(const string &clave) {
    Nodo *actual = _raiz;
    if(_raiz != NULL) {
        for (int i = 0; i < clave.size(); i++) {
            actual = actual->siguientes[int(clave[i])];
        }
        return *(actual->significado);
    }
}

template <typename T>
T& DiccionarioTrie<T>::Significado(const string &clave) const{
    Nodo *actual = _raiz;
    if(_raiz != NULL) {
        for (int i = 0; i < clave.size(); i++) {
            int letra = int(clave[i]);
            actual = actual->siguientes[letra];
        }
        return *(actual->significado);
    }
}


template <typename T>
void DiccionarioTrie<T>::_destroy(Nodo* raiz) {
    if(raiz != NULL) {
        if(raiz->siguientes != NULL){
            for (int i = 0; i < 256; ++i) {
                if (raiz->siguientes[i] != NULL) {
                    _destroy(raiz->siguientes[i]);
                }
            }
        }
        delete(raiz);
    }
}

template <typename T>
DiccionarioTrie<T>::Nodo::~Nodo() {
    delete(significado);
    delete[](siguientes);
}

template <typename T>
DiccionarioTrie<T>::ItDiccTrie::ItDiccTrie() {
    _actual = NULL;
}

template <typename T>
DiccionarioTrie<T>::ItDiccTrie::ItDiccTrie(Nodo *actual, string clave) {
    _actual = actual;
    _clave = clave;
}

template <typename T>
typename DiccionarioTrie<T>::ItDiccTrie DiccionarioTrie<T>::BuscarIterador(const string &clave) const{
    Nodo* actual = _raiz;
    if(actual != NULL) {
        for (int i = 0; i < clave.size(); i++) {
            actual = actual->siguientes[int(clave[i])];
        }
    }
    return ItDiccTrie(actual, clave);
}

template <typename T>
bool DiccionarioTrie<T>::ItDiccTrie::HaySiguiente(Nodo *actual, int desde) const{
    for (int i = desde + 1; i < 256; ++i) {
        if(actual->siguientes[i] != NULL){
            return true;
        }
    }
    return false;
}

template <typename T>
int DiccionarioTrie<T>::ItDiccTrie::Siguiente(Nodo *actual, int desde) const{
    for (int i = desde + 1; i < 256; ++i) {
        if(actual->siguientes[i] != NULL){
            return i;
        }
    }
}

template <typename T>
typename DiccionarioTrie<T>::ItDiccTrie DiccionarioTrie<T>::CrearIt() const{
    Nodo* actual = _raiz;
    string clave;
    if(actual != NULL) {
        ItDiccTrie s = ItDiccTrie();
        int sig;
        while (actual->significado == NULL && s.HaySiguiente(actual, -1)) {
            sig = s.ItDiccTrie::Siguiente(actual, -1);
            actual = actual->siguientes[sig];
            clave += (char) sig;
        }
    }
    return ItDiccTrie(actual, clave);
}

template <typename T>
tuple<string, T&> DiccionarioTrie<T>::ItDiccTrie::Actual() {
    T* significado = NULL;
    if(_actual and _actual->significado != NULL){
        significado = _actual->significado;
    }
    tuple<string, T &> res(_clave, *significado);

    return res;
}

template <typename T>
tuple<string, T&> DiccionarioTrie<T>::ItDiccTrie::Actual() const{
    T* significado = _actual->significado;
    tuple<string, T &> res(_clave, *significado);

    return res;
}

template <typename T>
void DiccionarioTrie<T>::ItDiccTrie::Avanzar() {
    AvanzarAux();
    while (_actual->significado == NULL){
        AvanzarAux();
    }
}

template <typename T>
void DiccionarioTrie<T>::ItDiccTrie::AvanzarAux() {
    int sig;
    if(HaySiguiente(_actual, -1)){
        sig = Siguiente(_actual, -1);
        _actual = _actual->siguientes[sig];
        _clave += (char)sig;
    } else {
        char ultChar = _clave.back();
        if(HaySiguiente(_actual->padre, int(ultChar))){
            sig = Siguiente(_actual->padre, int(ultChar));
            _actual = _actual->padre->siguientes[sig];
            _clave.pop_back();
            _clave += (char) sig;
        } else {
            _actual = _actual->padre;
            _clave.pop_back();
        }
    }
}

template <typename T>
typename DiccionarioTrie<T>::ItDiccTrie& DiccionarioTrie<T>::ItDiccTrie::operator=(const ItDiccTrie &it) {
    _actual = it._actual;
    _clave = it._clave;
}

template <typename T>
void DiccionarioTrie<T>::_copiar(Nodo*& padre, Nodo* aCopiar) {
    if(aCopiar != NULL){
        padre = new Nodo;
        if(aCopiar->significado != NULL){
            padre->significado = new T(*(aCopiar->significado));
        }
        for (int i = 0; i < 256; i++) {
            if(aCopiar->siguientes[i] != NULL){
                padre->siguientes[i] = aCopiar->siguientes[i];
                _copiar(padre->siguientes[i], aCopiar->siguientes[i]);
            }
        }
    }

}

template <typename T>
DiccionarioTrie<T>& DiccionarioTrie<T>::operator=(const DiccionarioTrie<T>& d) {
    _destroy(_raiz);
    _raiz = NULL;
    _copiar(_raiz, d._raiz);
}

template <typename T>
typename DiccionarioTrie<T>::ItDiccTrie DiccionarioTrie<T>::ItInvalido() {
    return ItDiccTrie(NULL, "");
}