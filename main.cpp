#include <iostream>
#include <functional>
#include <vector>
typedef std::function<int(int)> FuncionUnaria;

template <typename VALUES_TYPE>
auto map(FuncionUnaria fn, std::vector<VALUES_TYPE> inVector) -> std::vector<VALUES_TYPE>
{
    std::vector<VALUES_TYPE> outVector;
    outVector.resize(inVector.size());
    std::transform(std::begin(inVector), std::end(inVector),
            std::begin(outVector),fn);
    return outVector;
}




auto main() -> int
{
    std::vector<int> v1;

    for(int i=0;i<10;i++){
        v1.push_back(i);
    }

    auto v2 = map<int>([](int x){return x+x;},v1);

    std::cout<<std::endl;
    for(auto v:v1) std::cout<< v << "-";
    std::cout<<std::endl;

    std::cout<<std::endl;
    for(auto v:v2) std::cout<< v <<"-";
    std::cout<<std::endl;


    return 0;
}