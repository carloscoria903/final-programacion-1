#include <stdio.h>
#include <stdlib.h>
FILE *archivoEquipo;
FILE *archivoGrupo;

//estructura tipo equipo para almacenar los nombres de los equipos
struct equipos{
    char nombre[50];
};


//estructura tipo grupo para almacenar los grupos y las estadísticas del grupo
struct grupos {
 int PJ;//partidos jugados
 int PG;//partidos ganados
 int PE;//partidos empatados
 int PP;//partidos perdidos   
 int GC;//goles encontra
 int GF;//goles a favor
 int DFG;//diferencia de goles
 int PTS;//puntos
 struct equipos nombreEquipos[4];
};

//estructura tipo competencia para almacenar el nombre de la competencia
struct competencia {
    char nombre[50];
    struct grupos gruposEquipos[4];
};

