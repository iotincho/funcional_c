#include <iostream>
#include <functional>
#include <vector>
typedef std::function<int(int)> FuncionUnaria;
typedef std::function<bool(int)> Predicado;

template <typename VALUES_TYPE>
auto map(FuncionUnaria fn, std::vector<VALUES_TYPE> inVector) -> std::vector<VALUES_TYPE>
{
    std::vector<VALUES_TYPE> outVector;
    outVector.resize(inVector.size());
    std::transform( std::begin(inVector),
                    std::end(inVector),
                    std::begin(outVector),
                    fn);
    return outVector;
}

template<typename OBJ_TYPE>
auto filter(Predicado pr,std::vector<OBJ_TYPE> inVector) -> std::vector<OBJ_TYPE>
{
    std::vector<OBJ_TYPE> outVector;
    std::copy_if( std::begin(inVector),
                  std::end(inVector),
                  std::back_inserter(outVector),
                  pr);
    return outVector;
}



auto main() -> int
{
    std::vector<int> v1;

    for(int i=0;i<10;i++){
        v1.push_back(i);
    }

    auto v2 = filter<int>([](int x){return x>5;},v1);

    std::cout<<std::endl;
    for(auto v:v1) std::cout<< v << "-";
    std::cout<<std::endl;

    std::cout<<std::endl;
    for(auto v:v2) std::cout<< v <<"-";
    std::cout<<std::endl;


    return 0;
}