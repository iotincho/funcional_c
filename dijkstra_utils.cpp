//
// Created by tincho on 17/02/19.
//

#ifndef DIJKSTRA
#define DIJKSTRA
#include <vector>
#include "grafo_utils.cpp"
#include "high_order_functions.cpp"
#include <tuple>

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

template <typename A>
auto at(std::vector<A> xs, int32_t i) -> A
{
    /**
     * at:: [a] -> Int -> a
     * at xs i = xs !! (i-1)
     */
    return xs.at(i-1);
}

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

auto getpeso(Pacu p, Vertice v) ->Peso
{
    /**
     * getpeso:: Pacu -> Vertice -> Peso
     * getpeso p v = at p (nombre v)
     */
    return at<Peso>(p,v.nombre);
}


auto actpeso(std::tuple<Pacu,Prev> t, Aristas ars) -> std::tuple<Pacu,Prev>
{
    /**
     *  actpeso::(Pacu , Prev) -> Aristas ->(Pacu,Prev)
     *  actpeso (p, pr) [] = (p,pr)
     *  actpeso (p, pr) (a:as) = actpeso (nuevocos,nuevopre)   as
     *     where cambiar  = cambiarnth (costonuevo) (nombre (dest a)-1) p
     *           cambiarpre = cambiarnth (orig a) (nombre (dest a)-1) pr
     *          costonuevo = (peso a) + getpeso p (orig a)
     *           nuevocos  = if ((costonuevo) < getpeso p (dest a)) then cambiar else p
     *           nuevopre  = if ((costonuevo) < getpeso p (dest a)) then cambiarpre else pr
     */

    if(ars.empty()) return t;

    //unpacking de datos
    Pacu p;
    Prev pr;
    tie(p,pr)=t;  // unpacking
    auto a = ars.front(); // desligo la cabeza
    Aristas as;
    std::copy(ars.begin()+1,ars.end(),std::back_inserter(as)); // copio tail

    auto costonuevo = a.peso + getpeso(p ,a.orig);
    auto cambiar = cambiarnth(costonuevo , a.dest.nombre-1, p);
    auto cambiarpre = cambiarnth(a.orig, a.dest.nombre-1,pr);
    auto nuevocos = (costonuevo < getpeso(p,a.dest))? cambiar:p;
    auto nuevopre = (costonuevo < getpeso(p,a.dest))? cambiarpre:pr;

    return actpeso(std::make_tuple(nuevocos,nuevopre),as);
}







#endif