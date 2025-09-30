## Resumen
Como contexto de aplicación del trabajo práctico especial se utilizará un modelo simplificado de aeropuertos y rutas aéreas. A partir de la narrativa que se presenta a continuación se deberán detectar las entidades necesarias para modelar el problema; para luego implementar los algoritmos que permitan resolver los servicios solicitados.

Se plantean dos escenarios de uso distintos del sistema:  
- **Viajeros:** desean conocer información de los vuelos disponibles.  
- **Organismos de seguridad:** desean verificar el correcto funcionamiento de los aeropuertos.

---

## Introducción
Se busca crear un sistema que permita:
- Registrar aeropuertos habilitados con su nombre, país y ciudad.  
- Registrar rutas aéreas entre aeropuertos (distancia, cabotaje, aerolíneas que la operan, cantidad de pasajes habilitados).  
- Mantener un sistema de reservas por día (origen, destino, aerolínea y asientos reservados).

El sistema será usado también por organismos de seguridad que deben verificar aeropuertos.

---

## Servicios a implementar

### Servicios para viajeros
**Servicio 1:** Verificar si existe un vuelo directo entre un aeropuerto de origen y uno de destino, para una aerolínea particular. Informar:  
- Kilómetros del viaje.  
- Cantidad de asientos disponibles.  

**Servicio 2:** Dado un par de aeropuertos origen y destino, obtener todos los vuelos (directos y con escalas) que se pueden tomar sin cambiar de aerolínea en las escalas intermedias. Indicar:  
- Aerolínea.  
- Número de escalas.  
- Kilómetros totales.  
- Sólo mostrar vuelos con asientos disponibles.  

### Servicios para organismos de seguridad
**Servicio 3:** Encontrar un recorrido que, partiendo de un aeropuerto, visite todos los aeropuertos y regrese al origen.  
- Cada aeropuerto debe visitarse una sola vez.  
- El recorrido debe minimizar los kilómetros.  
- No se consideran restricciones de reservas ni capacidad.  

---

## Descripción de la aplicación
El sistema cargará datos desde archivos de texto (`Aeropuertos.txt`, `Reservas.txt`, `Rutas.txt`) y presentará un menú con opciones:

1. Listar todos los aeropuertos.  
2. Listar todas las reservas realizadas.  
3. Servicio 1: Verificar vuelo directo.  
4. Servicio 2: Obtener vuelos de la misma aerolínea.  
5. Servicio 3: Circuito de aeropuertos.  

Cada opción solicitará los datos necesarios y mostrará resultados por pantalla, además de exportarlos a un archivo de salida.

---
