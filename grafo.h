#ifndef GRAFO_H_
#define GRAFO_H_
#include <list>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include "iostream"
#include <cassert>
using namespace std;

template <typename C> class Grafo
{
public:
	class Arco
	{
	public:
		Arco();
		Arco(int adyacente, const C & costo);
		int devolver_adyacente() const;
		const C & devolver_costo() const;
	private:
		int vertice;
		C costo;
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo();
	Grafo(const Grafo & otroGrafo);

	~Grafo();

	Grafo & operator = (const Grafo & otroGrafo);

	// Devuelve true si la cantidad de vértices es cero
	bool esta_vacio() const;

	// Indica la cantidad de vértices del grafo
	int devolver_longitud() const;

	bool existe_vertice(int vertice) const;

	bool existe_arco(int origen, int destino) const;

	// PRE CONDICION: existe_arco(origen, destino)
	const C & costo_arco(int origen, int destino) const;

	void devolver_vertices(list<int> & vertices) const;

	void devolver_adyacentes(int origen, list<Arco> & adyacentes) const;

	void agregar_vertice(int vertice);

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminar_vertice(int vertice);

	// PRE CONDICION: existeArco(origen, destino)
	void modificar_costo_arco(int origen, int destino, const C & costo);

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void agregar_arco(int origen, int destino, const C & costo);


	// POST CONDICION: !existeArco(origen, destino)
	void eliminar_arco(int origen, int destino);

	bool tieneCiclo();

	void vaciar();

private:
    map <int, map <int, C > > grafo;
}; // class Grafo


/*
 * Arco
 */

template <typename C> Grafo<C>::Arco::Arco()
{

}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{
    vertice = adyacente;
    this -> costo = costo;
}

template <typename C> int Grafo<C>::Arco::devolver_adyacente() const
{
    return vertice;
}

template <typename C> const C & Grafo<C>::Arco::devolver_costo() const
{
    return costo;
}


/*
 * Grafo
 */

template <typename C> Grafo<C>::Grafo()
{
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{

}

template <typename C> Grafo<C>::~Grafo()
{
    grafo.clear();
}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{

    return *this;
}

template <typename C> bool Grafo<C>::esta_vacio() const
{
    return grafo.empty();
}

template <typename C> int Grafo<C>::devolver_longitud() const
{
    return grafo.size();
}

template <typename C> bool Grafo<C>::existe_vertice(int vertice) const
{
    return (grafo.find(vertice) != grafo.end());
}

template <typename C> bool Grafo<C>::existe_arco(int origen, int destino) const
{
    typename map <int, map <int, C > >::const_iterator it = grafo.find(origen);
    return ((it != grafo.end()) && (it -> second.find(destino)) != (it -> second.end()));
}

template <typename C> const C & Grafo<C>::costo_arco(int origen, int destino) const
{
    if(!existe_arco(origen, destino))
     {
       return -1;
     }
    else{
        typename map <int, map <int, C > >::const_iterator it = grafo.find(origen);
        if(it != grafo.end())
        {
           typename map <int, C > :: const_iterator it_2 = it -> second.find(destino);
           if (it_2 != it -> second.end())
           {
               return it_2 -> second;
           }
        }
    }
}

template <typename C> void Grafo<C>::devolver_vertices(list<int> & vertices) const
{
    typename map <int, map <int, C > >::const_iterator it = grafo.begin();
    while (it != grafo.end())
    {
        vertices.push_back(it -> first);
        it++;
    }
}

template <typename C> void Grafo<C>::devolver_adyacentes(int origen, list<Arco> & adyacentes) const
{
    typename map <int, map <int, C > >::const_iterator it = grafo.find(origen);
    if (it != grafo.end())
    {
      typename map <int, C >::const_iterator it2 = it -> second.begin();
      while (it2 != it -> second.end())
      {
        Arco arco = Arco(it2 -> first, it2 -> second);
        adyacentes.push_back(arco);
        it2++;
      }
    }
}

template <typename C> void Grafo<C>::agregar_vertice(int vertice)
{
    if (grafo.find(vertice) == grafo.end())
    {
        grafo[vertice] = {};
    }
}

template <typename C> void Grafo<C>::eliminar_vertice(int vertice)
{
    if (existe_vertice(vertice))
    {
        grafo.erase(vertice);
    }
}

template <typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C & costo)
{
    typename map <int, map <int, C > >::iterator it = grafo.find(origen);
    if ((it != grafo.end()) && (it -> second.find(destino)) != (it -> second.end()))
    {
        it -> second[destino] = costo;
    }

}

template <typename C> void Grafo<C>::agregar_arco(int origen, int destino, const C & costo)
{
    if ((existe_vertice(origen)) && (existe_vertice(destino)))
    {
        typename map <int, map <int, C > >::iterator it = grafo.find(origen);
        it -> second[destino] = costo;
    }
}

template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino)
{
    typename map <int, map <int, C > >::iterator it = grafo.find(origen);
    if ((it != grafo.end()) && (it -> second.find(destino)) != (it -> second.end()))
    {
        it -> second.erase(destino);
    }
}

template <typename C> void Grafo<C>::vaciar()
{
    typename map <int, map <int, C > >::iterator it = grafo.begin();
    while (it != grafo.end())
    {
        grafo.erase(it);
        it++;
    }
}
template class Grafo<int>;
template class Grafo<float>;
template class Grafo<double>;
#endif /* GRAFO_H_ */
