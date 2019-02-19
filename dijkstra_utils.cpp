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
    return filter<Vertice>([=](Vertice x){ return x==v;},
                            verticesprueva);
}

auto vernocono(Vertice v) -> std::vector<Vertice>
{
    /**
     * vercono v = filter (\x->x==v) verticesprueba
     */
    return filter<Vertice>([=](Vertice x){ return x!=v;},
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
            return (a.orig==o) && (a.dest==d); }, as);};
    if(filtrado().empty()) return INFINITO;
    else return filtrado().front().peso;
}

auto previnicial(Vertice v) -> Prev
{
    /**
     * previnicial v = map (\x->if (x==v) then v else verticenulo) verticesprueba
     */
    return map<Vertice,Vertice>([v](Vertice x){
        return (x == v)? v:verticenulo;},
                verticesprueva);
}

auto acuinicial(Aristas a, Vertice v) -> Pacu
{
    /**
     * acuinicial a v = map (\x->if (x==v) then 0 else (costo a v x)) verticesprueba
     */
    return map<Peso,Vertice>( [a, v](Vertice x){
                                return (x==v)? (Peso)0:costo(a, v, x);},
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


template <typename OBJ_TYPE>
auto elem(OBJ_TYPE o,std::vector<OBJ_TYPE> v) -> bool
{
    if (v.empty()) return false;
    if (v.front() == o) return true;
    return elem<OBJ_TYPE>(o,std::vector(v.begin()+1,v.end()));
}


auto iteracion(Dijkstra d) -> Dijkstra
{
    /**
     * iteracion::Dijkstra -> Dijkstra
     * iteracion d = Dij (a d) (nuevocon d) (nuevonocono d) (nuevoacu d) (nuevoprev d)
     *     where next = foldl (\x y->if ((getpeso (pacu d) x) < (getpeso (pacu d) y)) then x else y) (head $ vnc d) (vnc d)
     *           nuevocon d = (next):(vc d)
     *           nuevonocono d = filter (/=next ) (vnc d)
     *           acandidata = filter (\x-> orig x == next) (a d)
     *           avalidas   = filter (\x-> dest x `elem` (vnc d)) acandidata
     *           resul      = actpeso (pacu d,prev d) avalidas
     *           nuevoacu d = fst resul
     *           nuevoprev d = snd resul
     */
    auto next = foldl<Vertice>([d](Vertice x, Vertice y){
                            return (getpeso(d.pacu, x) < getpeso(d.pacu, y))? x:y;},
                       d.vnc.front(),
                       d.vnc);
    auto nuevocon = [next](Dijkstra dd){dd.vc.insert(dd.vc.begin(),next);return dd.vc;};
    auto nuevonocono = [next](Dijkstra dd){
                                return filter<Vertice>([next](Vertice x){return x!=next;},
                                                       dd.vnc);};
    auto acandidata = filter<Arista>([next](Arista x){return x.orig==next;},
                                        d.a);
    auto avalidas = filter<Arista>([d](Arista x){ return elem<Vertice>(x.dest,d.vnc);},
                                    acandidata);
    auto resul = actpeso(std::make_tuple(d.pacu,d.prev),avalidas);
    auto nuevoacu = [resul](Dijkstra dd){ return std::get<0>(resul);};
    auto nuevoprev = [resul](Dijkstra dd){ return std::get<1>(resul);};

    return Dijkstra(d.a,
                    nuevocon(d),
                    nuevonocono(d),
                    nuevoacu(d),
                    nuevoprev(d));
}

auto caminocorto (Dijkstra d) -> Dijkstra
{
    if(d.vnc.empty()) return d;
    return caminocorto(iteracion(d));
}





#endif