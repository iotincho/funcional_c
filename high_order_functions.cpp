//
// Created by tincho on 16/02/19.
//

#ifndef FUNCIONAL_HIGH_ORDER_FUNCTIONS_CPP
#define FUNCIONAL_HIGH_ORDER_FUNCTIONS_CPP

#include <iostream>
#include <functional>
#include <vector>
#include <numeric>
#include "high_order_functions.h"


template <typename RET_OBJ_TYPE,typename OBJ_TYPE>
auto map( std::function<RET_OBJ_TYPE(OBJ_TYPE)> fn,
          std::vector<OBJ_TYPE> inVector)
          -> std::vector<OBJ_TYPE>
{
    std::vector<OBJ_TYPE> outVector;
    outVector.resize(inVector.size());
    transform( std::begin(inVector),
                    std::end(inVector),
                    std::begin(outVector),
                    fn);
    return outVector;
}


template<typename OBJ_TYPE>
auto filter( std::function<bool(OBJ_TYPE)> pr,
             std::vector<OBJ_TYPE> inVector)
             -> std::vector<OBJ_TYPE>
{
    std::vector<OBJ_TYPE> outVector;
    copy_if( std::begin(inVector),
                  std::end(inVector),
                  std::back_inserter(outVector),
                  pr);
    return outVector;
}

template<typename OBJ_TYPE>
auto foldl( std::function<OBJ_TYPE(OBJ_TYPE,OBJ_TYPE)> fn,
            OBJ_TYPE initial,
            std::vector<OBJ_TYPE> inVector)
            -> OBJ_TYPE
{
    return std::accumulate( std::begin(inVector),
                            std::end(inVector),
                            initial,
                            fn);
}

template<typename OBJ_TYPE>
auto foldr( std::function<OBJ_TYPE(OBJ_TYPE,OBJ_TYPE)> fn,
            OBJ_TYPE initial,
            std::vector<OBJ_TYPE> inVector)
            -> OBJ_TYPE
{
    return std::accumulate( std::rbegin(inVector),
                            std::rend(inVector),
                            initial,
                            fn);
}

#endif