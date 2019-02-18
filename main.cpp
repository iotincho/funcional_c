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

    auto res2 = generarinicial(v2);


    for(auto r : res2.vc) {
        std::cout << "vc:" << r.nombre<< std::endl;
    }
    for(auto r : res2.vnc) {
        std::cout << "vnc:" << r.nombre<< std::endl;
    }
    for(auto r : res2.a) {
        std::cout << "arista:" << r.peso<< std::endl;
    }
    int i = 1;
    for(auto r : res2.pacu) {
        std::cout << "pacu to "<< i++ << ": " << r << std::endl;
    }
    for(auto r : res2.prev) {
        std::cout << "prev: " << r.nombre<< std::endl;
    }

    std::cout<<"getpeso : "<< getpeso(res2.pacu,v5);

    return 0;
}
