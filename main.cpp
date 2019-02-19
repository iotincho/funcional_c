#include <iostream>
#include <vector>
#include "high_order_functions.cpp"
#include "grafo_utils.cpp"
#include "dijkstra_utils.cpp"

auto v1 = Vertice(1);
auto v2 = Vertice(2);
auto v3 = Vertice(3);
auto v4 = Vertice(4);
auto v5 = Vertice(5);

auto a1= Arista(v1,v2,5);
auto a2= Arista(v1,v3,2);
auto a3= Arista(v1,v4,3);
auto a4= Arista(v2,v5,1);
auto a5= Arista(v3,v2,7);
auto a6= Arista(v4,v2,1);
auto a7= Arista(v4,v3,4);
auto a8= Arista(v4,v5,7);

std::vector<Vertice> verticesprueva = {v1,v2,v3,v4,v5};
std::vector<Arista> aristasprueva = {a1,a2,a3,a4,a5,a6,a7,a8};

int main()
{
    auto grafoprueva = Grafo(verticesprueva, aristasprueva);

    auto res = elem<Vertice>(v4,verticesprueva);

    auto dij = generarinicial(v3);
    auto cc = caminocorto(dij);
    std::cout<< "res: "<< res ;

    return 0;
}
