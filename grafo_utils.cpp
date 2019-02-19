//
// Created by tincho on 17/02/19.
//
#ifndef GRAFO_UTILS
#define GRAFO_UTILS

#include <cstdint>
#include <vector>

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