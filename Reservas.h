#ifndef RESERVAS_H_INCLUDED
#define RESERVAS_H_INCLUDED
#include <string>
#include <iostream>
#include <cassert>
#include <map>
#include <utility>
#include "Vertice.h"
using namespace std;

class Reservas
{
    public:
        Reservas();
        ~Reservas();
        void cargarReservas(int origen, int destino, string aerolinea, int reserva);
        void getReservas(list<string>&l_reservas, Vertice &v);
        int getAsientosReservados(int origen, int destino, string aerolinea)const;

    private:
        map<int, map<int, map<string,int> > > reservas;
};
Reservas::Reservas()
{

}
Reservas::~Reservas()
{
    reservas.clear();
}
void Reservas::cargarReservas(int origen, int destino, string aerolinea, int reserva)
{
    reservas[origen][destino][aerolinea] = reserva;
}


void Reservas::getReservas(list<string>&l_reservas, Vertice &v){
     string a;
     map<int, map<int, map<string,int> > >:: const_iterator it;
     map<int, map<string,int> > :: const_iterator it_2;
     map<string,int>:: const_iterator it_3;
     for (it = reservas.begin();it!=reservas.end();it++){
         for(it_2 = it -> second.begin();it_2!=it -> second.end();it_2++){
            for(it_3 = it_2 -> second.begin(); it_3!=it_2->second.end();it_3++){
                a = "origen: " + v.getAeropuertoAsociado(it->first) + "\n" + "destino: " + v.getAeropuertoAsociado(it_2->first) + "\n"
                +  "aerolinea: " + it_3->first + "\n"
                + "reservas: " + to_string(it_3->second) + "\n";
                l_reservas.push_back(a);}
         }
     }
}

int Reservas::getAsientosReservados(int origen, int destino, string aerolinea)const
{
    map<int, map<int, map<string,int> > >:: const_iterator it = reservas.find(origen);
    if(it != reservas.end())
    {
    map<int, map<string,int> > :: const_iterator it_2 = it -> second.find(destino);
    if(it_2 == it -> second.end())
    {
        return 0;
    }
    else
    {
        map<string,int>:: const_iterator it_3 = it_2 -> second.find(aerolinea);
        if(it_3 == it_2 -> second.end())
        {
            return 0;
        }
        else return it_3 -> second;
    }
    } else return 0;
}
#endif // RESERVAS_H_INCLUDED
