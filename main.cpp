#include "Grafo.h"
#include "iostream"
#include <cassert>
#include "Vertice.h"
#include "ArcoDatos.h"
#include "Reservas.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>

using namespace std;


template <typename C>void cargar_aeropuertos(string path, Vertice & v, Grafo<C> & g, list<int>& l_aeropuertos);

template <typename C>void cargar_rutas(string path,Vertice & v, Grafo<C> & g, ArcoDatos & a);

void cargar_reservas(string path, Reservas & r, Vertice & v);

enum Color{Blanco, Gris, Negro};

template <typename C> void imprimir(int i, vector<int> camino, Grafo<C> & g, set<string> interseccion, Vertice & v,ofstream &archivoSalida);

template <typename C> void DFS(Grafo<C> & g, int origen, int destino, vector<Color>& marca,
                               vector<int>& camino, map<int,list<typename Grafo<int>::Arco>>& adyacentes, ArcoDatos& a,
                               set<string> aerolineas, Reservas& r, Vertice& V, bool& encontreCamino, map<vector<int>,set<string>>& mapa_caminos);

void imprimir_recorrido(vector<int> camino,double totalKm,Vertice &V);


template <typename C>
void recorridoAeropuertos(Grafo<C>& grafo, vector<int>& camino, vector<bool>& visitados, double costo, int pos, int origen, int contador, double& costoMinimo, vector<int>& resultado);

template <typename C>
void cargar_aeropuertos(string path, Vertice & v, Grafo<C> & g, list<string>& l_aeropuertos)
{
    ifstream origen(path.c_str());
    if (!origen.is_open())
        cout << "No se pudo abrir el archivo: " << path << endl;
    else {
        while (!origen.eof()) {
            string linea;
            getline(origen,linea);
            size_t primera_pos = linea.find(',');
            string nombre_aeropuerto = linea.substr(0, primera_pos);
            size_t segunda_pos = linea.find(',', primera_pos + 1);
            string nombre_ciudad = linea.substr(primera_pos + 1, segunda_pos - primera_pos - 1);
            string pais = linea.substr(segunda_pos + 1);

                v.cargarVertice(nombre_aeropuerto, nombre_ciudad, pais);
                g.agregar_vertice(v.getNumeroAsociado(nombre_aeropuerto));


            l_aeropuertos.push_back(nombre_aeropuerto);

        }
    }
}

template <typename C>
void cargar_rutas(string path, Vertice & v, Grafo<C> & g, ArcoDatos & a)
{
    ifstream origen(path.c_str());
    if (!origen.is_open())
        cout << "No se pudo abrir el archivo: " << path << endl;
    else {
        while (!origen.eof()) {
            string linea;
            getline(origen,linea);
            size_t primera_pos = linea.find(',');
            string nombre_aeropuerto_origen = linea.substr(0, primera_pos);

            size_t segunda_pos = linea.find(',', primera_pos + 1);
            string nombre_aeropuerto_destino = linea.substr(primera_pos + 1, segunda_pos - primera_pos - 1);

            size_t tercera_pos = linea.find(',', segunda_pos + 1);
            string distancia_texto = linea.substr(segunda_pos + 1, tercera_pos - segunda_pos - 1);
            double distancia = stod(distancia_texto);


            size_t cuarta_pos = linea.find(',', tercera_pos + 1);
            string cabotaje_texto = linea.substr(tercera_pos + 1, cuarta_pos - tercera_pos - 1);
            int cabotaje = stoi(cabotaje_texto);

            string aerolineas = linea.substr(cuarta_pos + 1);


            //Se elimina la llave inicial
            aerolineas = aerolineas.substr(1);
            size_t inicial = 0;
            size_t pos = 0;
            size_t pos_final = aerolineas.find('}');
            map<string,int> Aerolineas;
            while ((pos != std::string::npos) && (pos + 1 < pos_final))
                {
                    pos = aerolineas.find(',', inicial);
                    string dato_aerolinea = aerolineas.substr(inicial, pos - inicial);
                    size_t pos_separador = dato_aerolinea.find('-');
                    string aerolinea = dato_aerolinea.substr(0, pos_separador);
                    string asientos_texto = dato_aerolinea.substr(pos_separador + 1);
                    int asientos = atoi(asientos_texto.c_str());
                    Aerolineas[aerolinea] = asientos;
                    inicial = pos + 1;
                }
            a.cargarArco(v.getNumeroAsociado(nombre_aeropuerto_origen),v.getNumeroAsociado(nombre_aeropuerto_destino), Aerolineas,cabotaje);
            g.agregar_arco(v.getNumeroAsociado(nombre_aeropuerto_origen),v.getNumeroAsociado(nombre_aeropuerto_destino), distancia);
            g.agregar_arco(v.getNumeroAsociado(nombre_aeropuerto_destino),v.getNumeroAsociado(nombre_aeropuerto_origen), distancia);
        }
    }
}

void cargar_reservas(string path, Reservas & r, Vertice & v)
{
    ifstream origen(path.c_str());
    if (!origen.is_open())
        cout << "No se pudo abrir el archivo: " << path << endl;
    else {
        while (!origen.eof()) {
            string linea;
            getline(origen,linea);
            size_t primera_pos = linea.find(',');
            string nombre_aeropuerto_origen = linea.substr(0, primera_pos);

            size_t segunda_pos = linea.find(',', primera_pos + 1);
            string nombre_aeropuerto_destino = linea.substr(primera_pos + 1, segunda_pos - primera_pos - 1);

            size_t tercera_pos = linea.find(',', segunda_pos + 1);
            string aerolinea = linea.substr(segunda_pos + 1, tercera_pos - segunda_pos - 1);

            string asientos_reservados_texto = linea.substr(tercera_pos + 1);
            int asientos_reservados = atoi(asientos_reservados_texto.c_str());

             r.cargarReservas(v.getNumeroAsociado(nombre_aeropuerto_origen), v.getNumeroAsociado(nombre_aeropuerto_destino), aerolinea, asientos_reservados);
            }

    }
}


template <typename C>
ostream & operator << (ostream & salida, const Grafo<C> & grafo)
{
	// Recorremos todos los vertices
	list<int> vertices;
	grafo.devolver_vertices(vertices);
	list<int>::iterator v = vertices.begin();
	while (v != vertices.end()) {
		salida << "    " << *v << "\n";
		// Recorremos todos los adyacentes de cada vertice
		list<typename Grafo<C>::Arco> adyacentes;
		grafo.devolver_adyacentes(*v, adyacentes);
		typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
		while (ady != adyacentes.end()) {
			salida << "    " << *v << "-> " << ady->devolver_adyacente() << " (" << ady->devolver_costo() << ")\n";
			ady++;
		}
		v++;
	}
	return salida;
}

template <typename C>
void DFS(Grafo<C> & g, int origen, int destino, vector<Color>& marca, vector<int>& camino,
         map<int, list<typename Grafo<int>::Arco>>& adyacentes, ArcoDatos& a, set<string> aerolineas,
         Reservas& r, Vertice& V, bool& encontreCamino,  map<vector<int>,set<string>>& mapa_caminos)
{
    marca[origen] = Gris;
    camino.push_back(origen);

    if (origen == destino) {
        mapa_caminos[camino]= aerolineas;

    } else {
        list<typename Grafo<int>::Arco> l;
        g.devolver_adyacentes(origen, l);
        adyacentes[origen] = l;
        set<string> aerolineas_1;
        typename list<typename Grafo<int>::Arco>::iterator it;

        for (it = adyacentes[origen].begin(); it != adyacentes[origen].end(); ++it) {
            int v = it->devolver_adyacente();

            if (marca[v] == Blanco) {
                set<string> interseccion;
                aerolineas_1 = a.conjuntoAerolineas(origen, v);

                if (!aerolineas.empty()) {
                    set_intersection(aerolineas.begin(), aerolineas.end(), aerolineas_1.begin(), aerolineas_1.end(), inserter(interseccion, interseccion.begin()));
                } else {
                    interseccion = aerolineas_1;
                }

                set<string>::iterator it_1;
                int suma;
                for (it_1 = interseccion.begin(); it_1 != interseccion.end(); it_1++) {
                    suma = a.asientosTotales(origen, v, *it_1) - r.getAsientosReservados(origen, v, *it_1);
                    if (suma == 0) {
                        interseccion.erase(*it_1);
                    }
                }

                if (!interseccion.empty()) {
                    DFS(g, v, destino, marca, camino, adyacentes, a, interseccion, r, V, encontreCamino, mapa_caminos);
                }
            }
        }
    }
    marca[origen] = Blanco;
    camino.pop_back();
}

template <typename C>
void imprimir(int i, vector<int> camino, Grafo<C> & g, set<string> interseccion, Vertice & v, ofstream &archivoSalida) {
    int escalas = camino.size() - 2;
    vector<int>::iterator it;
    set<string>::iterator it_1;
    double kmTotales = 0;

    cout <<"---------------------------------------------------"<<endl;
    archivoSalida <<"---------------------------------------------------"<<endl;
    cout <<"------------------CAMINO NUMERO "<<i<<"------------------"<<endl;
    archivoSalida <<"------------------CAMINO NUMERO "<<i<<"------------------"<<endl;
    cout <<"---------------------------------------------------"<<endl;
    archivoSalida <<"---------------------------------------------------"<<endl;

    cout << "--Recorrido entre "<< v.getAeropuertoAsociado(camino[0]) << " y "<< v.getAeropuertoAsociado(camino[camino.size() - 1]) <<"--"<< endl;
    archivoSalida << "--Recorrido entre "<< v.getAeropuertoAsociado(camino[0]) << " y "<< v.getAeropuertoAsociado(camino[camino.size() - 1]) <<"--"<< endl;

    for (it = camino.begin(); it != camino.end() - 1; it++) {
        kmTotales = kmTotales + g.costo_arco(*it, *(it + 1));
        cout << "|" <<v.getAeropuertoAsociado(*it) << "| --> ";
        archivoSalida << "|" <<v.getAeropuertoAsociado(*it) << "| --> ";
    }
    cout << "|" << v.getAeropuertoAsociado(*(camino.end()-1)) << "|" <<endl;
    archivoSalida << "|" << v.getAeropuertoAsociado(*(camino.end()-1)) << "|" <<endl;
    cout<< "--Aerolineas--" << endl;
    archivoSalida << "--Aerolineas--" << endl;

    for (it_1 = interseccion.begin(); it_1 != interseccion.end(); it_1++) {
        cout << *it_1 << endl;
        archivoSalida << *it_1 << endl;
    }

    cout << "--Kilometros totales--" << endl;
    archivoSalida << "--Kilometros totales--" << endl;
    cout<< kmTotales << endl;
    archivoSalida << kmTotales << endl;

    cout << "--Escalas realizadas--" <<endl;
    archivoSalida << "--Escalas realizadas--" <<endl;
    cout<< escalas << endl;
    archivoSalida << escalas << endl;

    cout <<"---------------------------------------------------"<<endl;
    archivoSalida <<"---------------------------------------------------"<<endl;
}

template <typename C>
void recorridoAeropuertos(Grafo<C>& grafo, vector<int>& camino, vector<bool>& visitados,
                double costo, int pos, int origen, int contador, double& costoMinimo, vector<int>& resultado)
{
    if (contador == grafo.devolver_longitud() && grafo.existe_arco(pos, origen)) {
        if (costo + grafo.costo_arco(pos, origen) < costoMinimo) {
            resultado = camino;
            resultado.push_back(origen);
            costoMinimo = costo + grafo.costo_arco(pos, origen);
        }
        return;
    }

    list<typename Grafo<C>::Arco> adyacentes;
    grafo.devolver_adyacentes(pos, adyacentes);
    for (typename list<typename Grafo<C>::Arco>::iterator it = adyacentes.begin(); it != adyacentes.end(); ++it) {
        int i = it->devolver_adyacente();
        if (!visitados[i] && grafo.existe_arco(pos, i)) {
            visitados[i] = true;
            camino.push_back(i);
            recorridoAeropuertos(grafo, camino, visitados, costo + grafo.costo_arco(pos, i), i, origen, contador + 1, costoMinimo, resultado);
            camino.pop_back();
            visitados[i] = false;
        }
    }
}

void imprimir_recorrido(vector<int> camino, double totalKm, Vertice &v)
{
    string nombreArchivoNuevo = "datasets/Servicio 3 - Circuito de " + v.getAeropuertoAsociado(*camino.begin()) + ".txt";
    ofstream archivoSalida(nombreArchivoNuevo);
    if (!archivoSalida.is_open())
        {
            cout << "Error: No se pudo crear el archivo." << endl;
            return;
        }
    vector<int> :: iterator it = camino.begin();
    cout<<"-------RECORRIDO MINIMO--------------"<<endl;
    archivoSalida <<"-------RECORRIDO MINIMO--------------"<<endl;
    while(it != camino.end() - 1)
    {
        cout <<"|"<<v.getAeropuertoAsociado(*it) <<"| --> ";
        archivoSalida <<"|"<<v.getAeropuertoAsociado(*it) <<"| --> ";
        it++;
    }
    cout <<"|"<<v.getAeropuertoAsociado(*it) << "|" <<endl;
    archivoSalida <<"|"<<v.getAeropuertoAsociado(*it) << "|" <<endl;
    cout<<"KM totales del recorrido: " <<totalKm<<endl;
    archivoSalida <<"KM totales del recorrido: " <<totalKm<<endl;
    cout<<"cantidad de aeropuertos visitados " << camino.size()-1<<endl;
    archivoSalida <<"cantidad de aeropuertos visitados " << camino.size()-1<<endl;
    cout<<"--------------------------------------"<<endl;
    archivoSalida <<"--------------------------------------"<<endl;
}
int main() {

    Vertice v;
    ArcoDatos a;
    Grafo<int> g;
    Reservas r;
    list<string> l_aeropuertos;
     list<string>l_reservas;

    string tecla;
    string origen, destino, aerolinea;

    cargar_aeropuertos("datasets/Aeropuertos.txt", v, g,l_aeropuertos) ;
    cargar_rutas("datasets/Rutas.txt", v, g, a);
    cargar_reservas("datasets/Reservas.txt", r, v);
    r.getReservas(l_reservas,v);

  do {
        // Mostrar el menú
        cout << "Menu:" << endl;
        cout << "1. Lista de Aeropuertos" << endl;
        cout << "2. Lista de Reservados" << endl;
        cout << "3. Servicio 1: Verificar vuelo directo" << endl;
        cout << "4. Servicio 2: Obtener vuelos de la misma Aerolinea" << endl;
        cout << "5. Servicio 3: Circuito de Aeropuertos" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: " << endl;
        cout << endl;

        // Leer la opción del usuario
            tecla = _getch();
       int U;
       int V;
        // Procesar la opción seleccionada
        switch (stoi(tecla)) {
            case 1:
                {
                    cout << "AROPUERTOS" << endl;
                    cout << "--------------------------" << endl;
                    list<string>::iterator it = l_aeropuertos.begin();
                    while(it!=l_aeropuertos.end()){
                        cout << *it <<endl;
                    it++;
                }
                    cout << "--------------------------" << endl;
                    break;
                }
            case 2:
                {
                    cout << "RESERVAS" << endl;
                    cout << "--------------------------" << endl;
                    list<string>::iterator it = l_reservas.begin();
                    while(it!=l_reservas.end()){
                        cout << *it;
                        cout << "--------------------------" << endl;
                        it++;
                    }
                    break;
                }
            case 3:
                {
                    cout << "Ha seleccionado la Opcion 'vuelo directo'" << endl;
                    cout << "ingrese el aeropuerto de origen"<<endl;
                    getline(cin,origen);
                    cout << "ingrese el aeropuerto destino"<<endl;
                    getline(cin, destino);
                    cout << "ingrese  la aerolinea "<<endl;
                    getline(cin, aerolinea);
                    cout << "la aerolinea seleccionada es " << aerolinea <<endl;

                    U = v.getNumeroAsociado(origen);
                    V = v.getNumeroAsociado(destino);

                    if (g.existe_arco(U,V) && a.existeAerolinea(U, V, aerolinea))
                    {
                        string nombreArchivoNuevo = "datasets/Servicio 1 - Verificacion de Vuelos Directos Entre " + origen + " y " + destino + ".txt";
                        ofstream archivoSalida(nombreArchivoNuevo);
                        if (!archivoSalida.is_open())
                        {
                            cout << "Error: No se pudo crear el archivo." << endl;
                        }
                        cout << "Kilometros = " << g.costo_arco(U,V) << endl;
                        archivoSalida << "Kilometros = " << g.costo_arco(U,V) << endl;
                        cout << "Asientos disponibles = " << a.asientosTotales(U, V, aerolinea) - r.getAsientosReservados(U , V, aerolinea) << endl;
                        archivoSalida << "Asientos disponibles = " << a.asientosTotales(U, V, aerolinea) - r.getAsientosReservados(U , V, aerolinea) << endl;

                    }
                        else cout << "no existe un vuelo directo entre los aeropuertos seleccionados" << endl;
                    break;
                }
            case 4:
                {
                 map<vector<int>,set<string>> mapa_caminos;
                vector<Color> marca(g.devolver_longitud()+1, Blanco);
                vector<int> camino;
                int i = 0;
                map<int,list<typename Grafo<int>::Arco>> adyacentes;
                set<string> aerolineas;
                bool encontreCamino = false;
                cout << "ingrese el aeropuerto de origen"<<endl;
                getline(cin,origen);
                cout << "ingrese el aeropuerto destino"<<endl;
                getline(cin, destino);
                if(v.getNumeroAsociado(origen)==-1 || v.getNumeroAsociado(destino)==-1){
                    cout << "Aeropuertos inexistentes" <<endl;
                }
                else{
                DFS(g, v.getNumeroAsociado(origen), v.getNumeroAsociado(destino), marca, camino, adyacentes, a, aerolineas, r,
                     v, encontreCamino, mapa_caminos);
                int i=0;
                if (!mapa_caminos.empty())
                {
                    map<vector<int>,set<string>>::iterator it = mapa_caminos.begin();
                        string nombreArchivoNuevo = "datasets/Servicio 2 - Caminos entre " + origen + " y " + destino + ".txt";
                        ofstream archivoSalida(nombreArchivoNuevo);
                        if (!archivoSalida.is_open())
                        {
                            cout << "Error: No se pudo crear el archivo." << endl;
                        }
                    while(it!=mapa_caminos.end()){
                        i++;
                        imprimir(i,it->first,g,it->second,v,archivoSalida);
                        it++;
                    }
                }
                    cout << "caminos totales encontrados: "<< i << endl;
                }

                break;
                }
            case 5:
                {
                    cout << "Ha seleccionado el Servicio 3" << endl;
                    cout << "ingrese el aeropuerto de origen"<<endl;
                    getline(cin,origen);
                    U = v.getNumeroAsociado(origen);
                    if(U==-1){
                        cout << "El aeropuerto ingresado no existe" <<endl;
                    }
                    else{
                    double cotaGlobal = INT_MAX;
                    vector<int> caminos,sol;
                    map<int,list<typename Grafo<int>::Arco>> adyacentes;
                    vector<bool> visitado(g.devolver_longitud(), false);
                    caminos.push_back(U);
                    visitado[U] = true;
                    recorridoAeropuertos( g, caminos, visitado, 0, U,U, 1, cotaGlobal, sol);
                    if (sol.size() == 0)
                    {
                        cout <<"NO EXISTE UN RECORRIDO VALIDO"<<endl;
                    }
                    else imprimir_recorrido(sol, cotaGlobal, v);
                    }
                    break;
                }
            }
        } while (stoi(tecla)!= 6);  // Continuar el bucle hasta que el usuario seleccione la opción de salir (6)

    return 0;
}
