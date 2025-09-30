#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <string>
#include <iostream>
using namespace std;
class Vertice
{
   public:
      Vertice();
      ~Vertice();
      string getCiudad(string aeropuerto) const;
      string getPais(string aeropuerto) const;
      int getNumeroAsociado(string aeropuerto) const;
      string getAeropuertoAsociado(int numero) const;
      void cargarVertice(string aeropuerto, string ciudad, string pais);

   private:
    struct dato{
    string ciudad;
    string pais;
    };
    int numero;
    map<string,dato> vertice;
    map<string,int> aeropuertos;
    map<int,string> NumeroDeAeropuerto;
};

Vertice::Vertice()
{
    numero = 1;
}

Vertice::~Vertice()
{
    vertice.clear();
    aeropuertos.clear();
}

void Vertice::cargarVertice(string aeropuerto, string ciudad, string pais)
{
    aeropuertos[aeropuerto] = numero;
    NumeroDeAeropuerto[numero] = aeropuerto;
    dato d;
    d.ciudad = ciudad;
    d.pais = pais;
    vertice[aeropuerto] = d;
    numero++;
}

 int Vertice::getNumeroAsociado(string aeropuerto) const
{
     map<string,int>::const_iterator it = aeropuertos.find(aeropuerto);
    if (it != aeropuertos.end())
    {
        return it -> second;
    }
    else return -1;
}
 string Vertice::getAeropuertoAsociado(int numero) const
{
    map<int, string>::const_iterator it = NumeroDeAeropuerto.find(numero);
    if (it != NumeroDeAeropuerto.end())
    {
        return it -> second;
    }
    else return "-1";
}
 string Vertice::getCiudad(string aeropuerto) const
{
    map<string,dato>::const_iterator it = vertice.find(aeropuerto);
    if (it != vertice.end())
    {
        return it -> second.ciudad;
    }
    else return "-1";
}

 string Vertice::getPais(string aeropuerto) const
{
    map<string,dato>::const_iterator it = vertice.find(aeropuerto);
    if (it != vertice.end())
    {
        return it -> second.pais;
    }
    else
        return "-1";

}

#endif // VERTICE_H_INCLUDED
