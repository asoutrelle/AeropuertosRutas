#ifndef ARCODATOS_H_INCLUDED
#define ARCODATOS_H_INCLUDED
#include "Vertice.h"
#include <map>
#include <list>
#include <cassert>
class ArcoDatos{
   public:
        ArcoDatos();
        ~ArcoDatos();

        set<string> conjuntoAerolineas(int origen, int destino) const;
        int asientosTotales(int origen, int destino, string aerolinea) const;
        int getCabotaje(int origen, int destino) const;
        void cargarArco(int origen, int destino, map<string,int>  & aerolineas, bool cab);
        bool existeAerolinea(int origen, int destino, string aerolinea) const;

   private:
       struct datos{
         map<string,int> aerolineas;
         int cabotaje;
       };
        map<int, map<int, datos>> arco;
};

 ArcoDatos::ArcoDatos(){
    // Inicializa el mapa arco en el constructor
}

 ArcoDatos::~ArcoDatos()
{
    arco.clear();
}
void  ArcoDatos::cargarArco(int origen, int destino,map<string,int> & aerolinea, bool cab)
{
    datos d;
    d.cabotaje = cab;
    d.aerolineas = aerolinea;
    arco[origen][destino] = d;
    arco[destino][origen] = d;
}
int ArcoDatos::getCabotaje(int origen, int destino) const
{
    map<int, map<int, datos> >::const_iterator it = arco.find(origen);
    if (it != arco.end())
    {
        map<int, datos>::const_iterator it_2 = it->second.find(destino);


        if (it_2 != it->second.end()) {
            return it_2->second.cabotaje;
        }
    }
    else
      return -1;

}
 set <string> ArcoDatos::conjuntoAerolineas(int origen, int destino) const
{
    set<string> conjunto;
    map<int, map<int, datos> >::const_iterator it = arco.find(origen);
    if (it != arco.end())
    {
       map<int, datos>::const_iterator it_2 = it->second.find(destino);

        if (it_2 != it->second.end())
        {
           map<string,int> ::const_iterator it_3 = it_2 -> second.aerolineas.begin();
           while (it_3 != it_2 -> second.aerolineas.end())
           {
               conjunto.insert(it_3 -> first);
               it_3 ++;
           }
        return conjunto;
        }
    }else return conjunto;
}
int ArcoDatos::asientosTotales(int origen, int destino, string aerolinea) const
{
    map<int, map<int, datos> >::const_iterator it = arco.find(origen);
    if (it != arco.end())
    {
        map<int, datos>::const_iterator it_2 = it->second.find(destino);

        if (it_2 != it->second.end()) {
            map<string,int>::const_iterator it_3 = it_2 -> second.aerolineas.find(aerolinea);
            if (it_3 != it_2 -> second.aerolineas.end())
            {
                return it_3 -> second;
            }
        }
    }
}
bool ArcoDatos::existeAerolinea(int origen, int destino, string aerolinea) const
{
    map<int, map<int, datos> >::const_iterator it = arco.find(origen);
    if (it != arco.end())
    {
        map<int, datos>::const_iterator it_2 = it->second.find(destino);

        if (it_2 != it->second.end()) {
            map<string,int>::const_iterator it_3 = it_2 -> second.aerolineas.find(aerolinea);
            if (it_3 != it_2 -> second.aerolineas.end())
            {
                return true;
            }
            else return false;
        }
    }
}
#endif // ARCODATOS_H_INCLUDED


