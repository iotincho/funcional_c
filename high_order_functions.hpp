//
// Created by tincho on 16/02/19.
//

#ifndef FUNCIONAL_HIGH_ORDER_FUNCTIONS_H
#define FUNCIONAL_HIGH_ORDER_FUNCTIONS_H

#include <iostream>
#include <functional>
#include <vector>
#include <numeric>


typedef std::function<int(int)> FuncionUnaria;
typedef std::function<bool(int)> Predicado;
typedef std::function<int(int,int)> FuncionBinaria;

template <typename VALUES_TYPE>
auto map(FuncionUnaria fn, std::vector<VALUES_TYPE> inVector) -> std::vector<VALUES_TYPE>;

template<typename OBJ_TYPE>
auto filter(Predicado pr,std::vector<OBJ_TYPE> inVector) -> std::vector<OBJ_TYPE>;

template<typename OBJ_TYPE>
auto foldl(FuncionBinaria fn,OBJ_TYPE initial,std::vector<OBJ_TYPE> in_vector) -> OBJ_TYPE;

template<typename OBJ_TYPE>
auto foldr(FuncionBinaria fn,OBJ_TYPE initial,std::vector<OBJ_TYPE> inVector) -> OBJ_TYPE;

#endif //FUNCIONAL_HIGH_ORDER_FUNCTIONS_H
