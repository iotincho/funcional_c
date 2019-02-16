#include <iostream>
#include "high_order_functions.cpp"
#include <vector>

int main()
{
    std::vector<int> v1;

    for(int i=0;i<10;i++){
        v1.push_back(1);
    }
/*
    auto v2 = filter<int>([](int x){return x>5;},v1);

    std::cout<<std::endl;
    for(auto v:v1) std::cout<< v << "-";
    std::cout<<std::endl;

    std::cout<<std::endl;
    for(auto v:v2) std::cout<< v <<"-";
    std::cout<<std::endl;

*/
    auto value = foldl<int>([](int x,int y){return x+y;},0,v1);
    auto value2 = foldr<int>([](int x,int y){return x+y;},0,v1);
    std::cout<<std::endl;
    std::cout<< "foldl = " << value;
    std::cout<<std::endl;
    std::cout<< "foldr = " << value2;
    std::cout<<std::endl;

    return 0;
}