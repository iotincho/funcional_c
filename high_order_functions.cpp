//
// Created by tincho on 16/02/19.
//
#include <iostream>
#include <functional>
#include <vector>
#include <numeric>
#include "high_order_functions.hpp"


template <typename VALUES_TYPE>
auto map(FuncionUnaria fn, std::vector<VALUES_TYPE> inVector) -> std::vector<VALUES_TYPE>
{
    std::vector<VALUES_TYPE> outVector;
    outVector.resize(inVector.size());
    transform( std::begin(inVector),
                    std::end(inVector),
                    std::begin(outVector),
                    fn);
    return outVector;
}

template<typename OBJ_TYPE>
auto filter(Predicado pr,std::vector<OBJ_TYPE> inVector) -> std::vector<OBJ_TYPE>
{
    std::vector<OBJ_TYPE> outVector;
    copy_if( std::begin(inVector),
                  std::end(inVector),
                  std::back_inserter(outVector),
                  pr);
    return outVector;
}

template<typename OBJ_TYPE>
auto foldl(FuncionBinaria fn,OBJ_TYPE initial,std::vector<OBJ_TYPE> inVector) -> OBJ_TYPE
{
    return std::accumulate( std::begin(inVector),
                            std::end(inVector),
                            initial,
                            fn);
}

template<typename OBJ_TYPE>
auto foldr(FuncionBinaria fn,OBJ_TYPE initial,std::vector<OBJ_TYPE> inVector) -> OBJ_TYPE
{
    return std::accumulate( std::rbegin(inVector),
                            std::rend(inVector),
                            initial,
                            fn);
}