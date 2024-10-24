#ifndef ARCHIVO_H
#define ARCHIVO_H
#include "funciones.h"
FILE *archivoFixture;
char nombreCompetencia[50];
char letraGrupo[4] = {'A', 'B', 'C', 'D'};

struct Estadisticas{
    int PJ;//PARTIDOS JUGADOS 
    int PG;//PARTIDOS GANADOS
    int PE;//PARTIDOS EMPATADOS
    int PP;//PARTIDOS PERDIDOS
    int GC;//GOL ENCONTRA
    int GF;//GOL A FAVOR
    int DFG;//DIFERENCIA DE GOL
    int PTS;//PUNTOS
};

//ESTRUCTURA PARA GUARDAR LOS NOMBRES DE LOS EQUIPOS
struct Equipo {  
 char nombreEquipo [50];
 struct Estadisticas estadistica;
};

//ESTRUCTURA PARA GUARDAR LOS GRUPOS, CON SUS NOMBRES Y SUS ESTADISTICAS
struct Grupo{
 struct Equipo equipos[4];
};

void agregarEquipoAlFixture(struct Grupo grupos[], const char* nombreCompetencia) {
    archivoFixture = fopen("fixture.txt", "w");
    if (archivoFixture == NULL) {
        perror("error al abrir el archivo para agregar equipos");
        return;
    }

    fprintf(archivoFixture, "============================== %s ==============================\n", nombreCompetencia);
    fprintf(archivoFixture, "\n");

    //guardar cada grupo en el archivo
    for (int grupoI = 0; grupoI < 4; grupoI++) {
        fprintf(archivoFixture, "\n================================= GRUPO %c ===================================\n", 'A' + grupoI);
        fprintf(archivoFixture, "| Equipo             | PJ   | PG   | PE   | PP   | Pts  | GF   | GC   | DG   |\n");
        fprintf(archivoFixture, "|--------------------|------|------|------|------|------|------|------|------|\n");

        for (int i = 0; i < 4; i++) {
            fprintf(archivoFixture, "| %-18s | %4d | %4d | %4d | %4d | %4d | %4d | %4d | %4d |\n",
                grupos[grupoI].equipos[i].nombreEquipo,
                grupos[grupoI].equipos[i].estadistica.PJ,
                grupos[grupoI].equipos[i].estadistica.PG,
                grupos[grupoI].equipos[i].estadistica.PE,
                grupos[grupoI].equipos[i].estadistica.PP,
                grupos[grupoI].equipos[i].estadistica.PTS,
                grupos[grupoI].equipos[i].estadistica.GF,
                grupos[grupoI].equipos[i].estadistica.GC,
                grupos[grupoI].equipos[i].estadistica.DFG);
        }

        fprintf(archivoFixture, "==============================================================================\n");
    }

    fclose(archivoFixture);
    printf("fixture guardado exitosamente en fixture.txt\n");
}

void eliminarArchivoFixture(const char* nombreArchivo) {
    //intentar eliminar el archivo
    if (remove(nombreArchivo) == 0) {
        printf("el archivo %s se elimino.\n", nombreArchivo);
    } else {
        perror("error al eliminar el archivo");
    }
}

void verFixture(struct Grupo grupos[]) {
    //abrir el archivo para lectura
    archivoFixture = fopen("fixture.txt", "r");
    if (archivoFixture == NULL) {
        perror("error al abrir el archivo para lectura");
        return;
    }
    char buffer[256];
    //leer y mostrar cada linea del archivo
    while (fgets(buffer, sizeof(buffer), archivoFixture) != NULL) {
        printf("%s", buffer); //mostrar cada linea
    }
    fclose(archivoFixture);
}

void verGrupo(struct Grupo grupos[]) {
    char grupoSeleccionado;
    printf("seleccione que grupo quiere ver (A, B, C, D): ");
    scanf(" %c", &grupoSeleccionado);
    grupoSeleccionado = toupper(grupoSeleccionado); //convertir a mayuscula por las dudas se ponga una misnuscula

    //validar que el grupo seleccionado este en el rango permitido
    if (grupoSeleccionado < 'A' || grupoSeleccionado > 'D') {
        printf("ingresa A, B, C o D.\n");
        return;
    }

    int grupoIndex = grupoSeleccionado - 'A'; //convertir 'A', 'B', 'C', 'D' a  0, 1, 2, 3

    printf("\n================================= GRUPO %c ===================================\n", grupoSeleccionado);
    printf("| Equipo             | PJ   | PG   | PE   | PP   | Pts  | GF   | GC   | DG   |\n");
    printf("|--------------------|------|------|------|------|------|------|------|------|\n");

    for (int i = 0; i < 4; i++) {
        printf("| %-18s | %4d | %4d | %4d | %4d | %4d | %4d | %4d | %4d |\n",
               grupos[grupoIndex].equipos[i].nombreEquipo,
               grupos[grupoIndex].equipos[i].estadistica.PJ,
               grupos[grupoIndex].equipos[i].estadistica.PG,
               grupos[grupoIndex].equipos[i].estadistica.PE,
               grupos[grupoIndex].equipos[i].estadistica.PP,
               grupos[grupoIndex].equipos[i].estadistica.PTS,
               grupos[grupoIndex].equipos[i].estadistica.GF,
               grupos[grupoIndex].equipos[i].estadistica.GC,
               grupos[grupoIndex].equipos[i].estadistica.DFG);
    }
}

void guardarEstadisticasEnArchivo(struct Grupo grupos[]) {
    FILE *archivoFixture = fopen("fixture.txt", "w");
    if (archivoFixture == NULL) {
        perror("error al abrir el archivo");
        return;
    }

    for (int i = 0; i < 4; i++) {
        
        fprintf(archivoFixture, "\n================================= GRUPO %c ===================================\n", 'A' + i);
        fprintf(archivoFixture, "| Equipo             | PJ   | PG   | PE   | PP   | Pts  | GF   | GC   | DG   |\n");
        fprintf(archivoFixture, "|--------------------|------|------|------|------|------|------|------|------|\n");
        for (int j = 0; j < 4; j++) {
            fprintf(archivoFixture, "| %-18s | %4d | %4d | %4d | %4d | %4d | %4d | %4d | %4d |\n",
                    grupos[i].equipos[j].nombreEquipo,
                    grupos[i].equipos[j].estadistica.PJ,
                    grupos[i].equipos[j].estadistica.PG,
                    grupos[i].equipos[j].estadistica.PE,
                    grupos[i].equipos[j].estadistica.PP,
                    grupos[i].equipos[j].estadistica.PTS,
                    grupos[i].equipos[j].estadistica.GF,
                    grupos[i].equipos[j].estadistica.GC,
                    grupos[i].equipos[j].estadistica.DFG);
        }
    }

    fclose(archivoFixture);
}



#endif