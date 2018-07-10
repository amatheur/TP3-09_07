#ifndef __UTILES_H__
#define __UTILES_H__

#include <stack>
#include <list>
#include <vector>
#include <tuple>

//typedef int Operacion;

typedef enum{oPush, oAdd, oSub, oMul, oWrite, oRead, oJump, oJumpz} Operacion;


typedef std::string Variable;
typedef std::string Rutina;

template <typename T>
using Pila = std::stack<T>;


template <typename T>
using Lista_Enlazada = std::list<T>;


#endif /*__UTILES_H__*/
