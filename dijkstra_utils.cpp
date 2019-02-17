//
// Created by tincho on 17/02/19.
//

#ifndef DIJKSTRA
#define DIJKSTRA
#include <vector>
#include "grafo_utils.cpp"
#include "high_order_functions.cpp"

#define INFINITO 100



typedef std::vector<Vertice> VC;
typedef std::vector<Vertice> VNC;
typedef int32_t Peso;
typedef std::vector<Peso> Pacu;
typedef std::vector<Vertice> Prev;
typedef std::vector<Arista> Aristas;

extern std::vector<Vertice> verticesprueva;

static const auto verticenulo = Vertice(0);

auto vercono(Vertice v) -> std::vector<Vertice>
{
    /**
     * vercono v = filter (\x->x==v) verticesprueba
     */
    return filter<Vertice>([=](Vertice x){ return x.nombre==v.nombre;},
                            verticesprueva);
}

auto vernocono(Vertice v) -> std::vector<Vertice>
{
    /**
     * vercono v = filter (\x->x==v) verticesprueba
     */
    return filter<Vertice>([=](Vertice x){ return x.nombre!=v.nombre;},
                           verticesprueva);
}

class Dijkstra{
    /**
     * data Dijkstra = Dij {a::Aristas, vc::VC, vnc::VNC, pacu::Pacu, prev::Prev} deriving Show
     */
    public:
        Aristas a;
        VC vc;
        VNC vnc;
        Pacu pacu;
        Prev prev;
        Dijkstra(){}
};

auto costo(Aristas as, Vertice o, Vertice d) -> Peso
{
    /**
     * costo::Aristas -> Vertice -> Vertice -> Peso
     * costo as o d = if (filtrado == []) then oo else (peso $ head $ filtrado)
     *      where filtrado = filter (\a->(orig a == o && dest a == d)) as
     */
    auto filtrado = [as, o, d]() -> Aristas {
        return filter<Arista>( [=](Arista a){
            return (a.orig.nombre==o.nombre) && (a.dest.nombre==d.nombre); }, as);};
    if(filtrado().empty()) return INFINITO;
    else return filtrado().front().peso;
}

auto previnicial(Vertice v) -> Prev
{
    return map<Vertice,Vertice>([v](Vertice x){
        return (x.nombre == v.nombre)? v:verticenulo;},
                verticesprueva);
}






#endif