# FIXTURE

**Contenidos**

[TOC]

#Descripción
Este programa permite la creación y manejo de un fixture para torneos de fútbol. Los usuarios pueden crear grupos, agregar equipos, registrar resultados y mantener estadísticas actualizadas de los equipos como partidos jugados, ganados, empatados, perdidos, goles a favor, goles en contra, y puntos.
#Características
Crear un fixture para una competición con grupos de equipos.
Cargar resultados de los partidos.
Ver las estadísticas completas de los equipos en cada grupo.
Modificar los nombres de los equipos.
Guardar y leer los datos desde archivos de texto.
#Uso
####Menú Principal
Al ejecutar el programa, se presenta un menú con tres opciones principales:

Crear Fixture: Crea un nuevo fixture eliminando el anterior si ya existe.
Menú Fixture: Permite ver el fixture, ver grupos, cargar resultados, y modificar nombres de equipos.
Salir: Cierra el programa.
####Crear Fixture
El programa te pedirá que ingreses el nombre de la competencia, y luego podrás ingresar los nombres de los equipos en cada grupo (A, B, C, D). Todos los datos serán guardados en un archivo.

####Cargar Resultados
En el menú de fixture, puedes seleccionar dos equipos de un grupo, ingresar los goles y actualizar automáticamente las estadísticas.

####Modificar Nombres
Puedes cambiar los nombres de los equipos en el menú de fixture. Los nuevos nombres se guardarán en el archivo.
#Estructuras
El proyecto usa las siguientes estructuras:
####Equipo: 
Representa a cada equipo con su nombre y estadísticas.

> struct Equipo {
    char nombreEquipo[50];
    struct Estadisticas estadistica;
>};

####Estadisticas:
Contiene las estadísticas de un equipo (partidos jugados, ganados, goles a favor, etc.).
> struct Estadisticas {
    int PJ, PG, PE, PP, GF, GC, DFG, PTS;
>};

####Grupo:
Un grupo contiene 4 equipos.

> struct Grupo {
    struct Equipo equipos[4];
> };

###fin