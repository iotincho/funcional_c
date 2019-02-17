//
// Created by tincho on 16/02/19.
//

#ifndef FUNCIONAL_HIGH_ORDER_FUNCTIONS_H
#define FUNCIONAL_HIGH_ORDER_FUNCTIONS_H

#include <iostream>
#include <functional>
#include <vector>
#include <numeric>



template <typename RET_OBJ_TYPE,typename OBJ_TYPE>
auto map( std::function<RET_OBJ_TYPE(OBJ_TYPE)> fn,
          std::vector<OBJ_TYPE> inVector)
-> std::vector<RET_OBJ_TYPE>;

template<typename OBJ_TYPE>
auto filter( std::function<bool(OBJ_TYPE)> pr,
             std::vector<OBJ_TYPE> inVector)
             -> std::vector<OBJ_TYPE>;

template<typename OBJ_TYPE>
auto foldl( std::function<OBJ_TYPE(OBJ_TYPE,OBJ_TYPE)> fn,
            OBJ_TYPE initial,
            std::vector<OBJ_TYPE> in_vector)
            -> OBJ_TYPE;

template<typename OBJ_TYPE>
auto foldr( std::function<OBJ_TYPE(OBJ_TYPE,OBJ_TYPE)> fn,
            OBJ_TYPE initial,
            std::vector<OBJ_TYPE> inVector)
            -> OBJ_TYPE;

#endif //FUNCIONAL_HIGH_ORDER_FUNCTIONS_H
