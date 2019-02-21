//
// Created by tincho on 17/02/19.
//
#ifndef GRAFO_UTILS
#define GRAFO_UTILS

#include <cstdint>
#include <vector>
#include <string>
#include <ostream>

class Vertice{
    public:
        int32_t nombre;

        Vertice(){}
        Vertice(int32_t nombre)
        {
            this->nombre = nombre;
        }
        bool operator==(Vertice v)
        {
            return this->nombre==v.nombre;
        }
        bool operator!=(Vertice v)
        {
            return this->nombre!=v.nombre;
        }

};

std::ostream& operator<<(std::ostream& os, const Vertice& v)
{
    /**
     * esta definido fuera de la clase xq debe ser implementada como funcion no miembro
     * instance Show (Vertice) where show (Vertice n) = show (n)
     */
    os << v.nombre;
    return os;
}



class Arista{
    public:
        Vertice orig;
        Vertice dest;
        int32_t peso;

        Arista(Vertice orig, Vertice dest,int32_t peso)
        {
            this->orig = orig;
            this->dest = dest;
            this->peso = peso;
        }

        bool operator==(Arista a)
        {
            return this->orig==a.orig && this->dest==a.dest;
        }
};


std::ostream& operator<<(std::ostream& os, const Arista& a)
{
    /**
     * esta definido fuera de la clase xq debe ser implementada como funcion no miembro
     * instance Show (Arista) where show (Arista orig dest peso) = "("++(show orig)++"->"++(show dest)++","++(show peso)++")")
     */
    os <<"( "<<a.orig<<"->"<<a.dest<<" , "<<a.peso<<" )" ;
    return os;
}

class Grafo{
    public:
        std::vector<Vertice> vertices;
        std::vector<Arista> aristas;

        Grafo(std::vector<Vertice> vertices,std::vector<Arista>aristas){
            this->aristas = aristas;
            this->vertices = vertices;
        }

};

#endif