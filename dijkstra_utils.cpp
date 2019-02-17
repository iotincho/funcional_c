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
extern Aristas aristasprueva;

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
        Dijkstra(){};
        Dijkstra(Aristas a,VC vc,VNC vnc, Pacu pacu, Prev prev)
        {
            this->a = a;
            this->vc = vc;
            this->vnc =vnc;
            this->pacu = pacu;
            this->prev = prev;
        }
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
    /**
     * previnicial v = map (\x->if (x==v) then v else verticenulo) verticesprueba
     */
    return map<Vertice,Vertice>([v](Vertice x){
        return (x.nombre == v.nombre)? v:verticenulo;},
                verticesprueva);
}

auto acuinicial(Aristas a, Vertice v) -> Pacu
{
    /**
     * acuinicial a v = map (\x->if (x==v) then 0 else (costo a v x)) verticesprueba
     */
    return map<Peso,Vertice>( [a, v](Vertice x){
                                return (x.nombre==v.nombre)? (Peso)0:costo(a, v, x);},
                             verticesprueva);
}

template<typename A>
auto cambiarnth(A a, int32_t n,std::vector<A> vector) -> std::vector<A>
{
    /**
     * cambiarnth:: a -> Int -> [a] -> [a]
     * cambiarnth a n [] = []
     * cambiarnth a 0 (x:xs) = a:xs
     * cambiarnth a n (x:xs) = x:(cambiarnth a (n-1) xs)
     */
    if (vector.empty()) return std::vector<A>();
    else if (n==0){vector.front()=a; return vector;}
    else {
        auto vaux = cambiarnth(a,n-1,std::vector<A>(vector.begin()+1,vector.end()));
        vaux.insert(vaux.begin(),vector.front());
        return vaux;}
    /* else vector.at(n) = a; // la funcion se puede reducir como esto. pero si esta fuera de rango retorna una exepcion y no es recursivo.*/
}

auto generarinicial(Vertice v) -> Dijkstra
{
    /**
     * generarinicial :: Vertice -> Dijkstra
     * generarinicial v = Dij (aristasprueba) (vercono v) (vernocono v) (acuinicial (aristasprueba) v) (previnicial v)
     */
    return Dijkstra( aristasprueva,
                     vercono(v),
                     vernocono(v),
                     acuinicial(aristasprueva,v),
                     previnicial(v));
}





#endif