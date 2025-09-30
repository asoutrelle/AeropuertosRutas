# Análisis y Diseño de Algoritmos II
## Trabajo Práctico Especial - Cursada 2023

Consultas y sugerencias: laboratorio.ayda@alumnos.exa.unicen.edu.ar

Licencia Creative Commons Atribución-Compartir Obras Derivadas Igual 2.5 Argentina  
http://creativecommons.org/licenses/by-sa/2.5/ar/

---

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

## Requisitos de entrega

Se debe entregar un proyecto que compile correctamente e incluya:  
- Código fuente.  
- Informe digital que contenga:  
  - Identificación del grupo.  
  - Introducción al problema.  
  - Modelado del problema (tipos de datos, estructuras elegidas, análisis de complejidad).  
  - Implementación de los servicios 1 y 2.  
  - Resolución del servicio 3 (análisis de alternativas, justificación de la elegida).  
  - Explicación del funcionamiento de la aplicación.  
  - Conclusiones.  

**Fecha de entrega:** Jueves 2 de Noviembre.  
**Envío por email:** laboratorio.ayda@alumnos.exa.unicen.edu.ar  

Formato de entrega:  
- Asunto: `<NroGrupo>-<Apellido integrantes>` (ej: `Grupo1-Garcia_Pérez`).  
- Adjuntar un `.zip` con:  
  - Informe editable (`.doc`, `.docx`, `.odt`).  
  - Archivos fuentes del proyecto.  
- Nombre del archivo: `<NroGrupo>-<Apellido integrantes>.zip`.  

---
