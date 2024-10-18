#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *archivoEquipo;
FILE *archivoGrupo;
FILE *archivoEstadisticas;

// Estructura para almacenar las estadísticas de los equipos
struct estadisticasEquipo {
    int PJ; // Partidos jugados
    int PG; // Partidos ganados
    int PE; // Partidos empatados
    int PP; // Partidos perdidos
    int GC; // Goles en contra
    int GF; // Goles a favor
    int DFG; // Diferencia de goles
    int PTS; // Puntos
};

// Estructura para representar un equipo
struct equipo {
    char nombre[50]; // Nombre del equipo
    struct estadisticasEquipo estadisticas; // Estadísticas del equipo
};

// Estructura para representar un grupo, que contiene 4 equipos
struct grupos {
    struct equipo equipos[4]; // Lista de equipos en el grupo
};

// Estructura para representar la competencia, que contiene 4 grupos
struct competencia {
    char nombre[50]; // Nombre de la competencia
    struct grupos gruposEquipos[4]; // Grupos de equipos dentro de la competencia
};


void menuPrincipal() {
    struct competencia torneo;
    int opcion;
    do {
        printf("\n======================================== MENU PRINCIPAL ========================================\n");
        printf("|                                                                                                 |\n");
        printf("|                                  1- CREAR FIXTURE                                               |\n");
        printf("|                                                                                                 |\n");
        printf("|                                  2- MENU FIXTURE                                                |\n");
        printf("|                                                                                                 |\n");
        printf("|                                  3- SALIR                                                       |\n");
        printf("|                                                                                                 |\n");
        printf("================================================================================================\n");

        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 1:
                system("cls");
                crearFixture();
                break;
            case 2:
                system("cls");
                menuFixture();
                break;
            case 3:
                exit(0);
            default:
                system("cls");
                printf("Opcion no valida. Por favor, ingrese una opcion valida.\n");
                break;
        }
    } while (opcion != 3);
}

void crearFixture() {
    struct competencia torneo;
    
    printf("Ingresa el nombre de la competencia: ");
    fgets(torneo.nombre, sizeof(torneo.nombre), stdin);
    strtok(torneo.nombre, "\n"); // Eliminar el salto de línea

    // Leer los nombres de los equipos para cada grupo
    for (int grupoI = 0; grupoI < 4; grupoI++) {
        printf("Crear grupo %c:\n", 'A' + grupoI);

        // Leer nombres de equipos
        for (int i = 0; i < 4; i++) {
            printf("Ingresa el nombre del equipo %d: ", i + 1);
            fgets(torneo.gruposEquipos[grupoI].equipos[i].nombre, sizeof(torneo.gruposEquipos[grupoI].equipos[i].nombre), stdin);
            strtok(torneo.gruposEquipos[grupoI].equipos[i].nombre, "\n"); // Eliminar el salto de línea
            
            // Inicializar estadísticas del equipo
            torneo.gruposEquipos[grupoI].equipos[i].estadisticas.PJ = 0;
            torneo.gruposEquipos[grupoI].equipos[i].estadisticas.PG = 0;
            torneo.gruposEquipos[grupoI].equipos[i].estadisticas.PE = 0;
            torneo.gruposEquipos[grupoI].equipos[i].estadisticas.PP = 0;
            torneo.gruposEquipos[grupoI].equipos[i].estadisticas.GF = 0;
            torneo.gruposEquipos[grupoI].equipos[i].estadisticas.GC = 0;
            torneo.gruposEquipos[grupoI].equipos[i].estadisticas.DFG = 0;
            torneo.gruposEquipos[grupoI].equipos[i].estadisticas.PTS = 0;
        }
    }

    // Guardar los equipos, los grupos y las estadísticas en archivos
    guardarEquipos(&torneo);
    guardarGrupos(&torneo);
    guardarEstadisticas(&torneo);

    printf("Fixture creado y guardado exitosamente.\n");
}

void guardarEquipos(struct competencia *torneo) {
    archivoEquipo = fopen("Equipos.txt", "w");
    if (archivoEquipo == NULL) {
        printf("Error al abrir el archivo de equipos.\n");
        return;
    }

    for (int grupoI = 0; grupoI < 4; grupoI++) {
        fprintf(archivoEquipo, "=================== GRUPO %c ===================\n", 'A' + grupoI);
        for (int i = 0; i < 4; i++) {
            fprintf(archivoEquipo, "Equipo %d: %s\n", i + 1, torneo->gruposEquipos[grupoI].equipos[i].nombre);
        }
        fprintf(archivoEquipo, "\n");
    }

    fclose(archivoEquipo);
}

void guardarGrupos(struct competencia *torneo) {
    archivoGrupo = fopen("Grupos.txt", "w");
    if (archivoGrupo == NULL) {
        printf("Error al abrir el archivo de grupos.\n");
        return;
    }

    for (int grupoI = 0; grupoI < 4; grupoI++) {
        fprintf(archivoGrupo, "\n================================= GRUPO %c ===================================\n", 'A' + grupoI);
        fprintf(archivoGrupo, "| Equipo             | PJ   | PG   | PE   | PP   | Pts  | GF   | GC   | DG   |\n");
        fprintf(archivoGrupo, "|--------------------|------|------|------|------|------|------|------|------|\n");
        for (int i = 0; i < 4; i++) {
            fprintf(archivoGrupo, "| %-18s | %4d | %4d | %4d | %4d | %4d | %4d | %4d | %4d |\n",
                torneo->gruposEquipos[grupoI].equipos[i].nombre,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PJ,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PG,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PE,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PP,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PTS,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.GF,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.GC,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.DFG);
        }
    }

    fclose(archivoGrupo);
}

void guardarEstadisticas(struct competencia *torneo) {
    archivoEstadisticas = fopen("Estadisticas.txt", "w");
    if (archivoEstadisticas == NULL) {
        printf("Error al abrir el archivo de estadísticas.\n");
        return;
    }

    for (int grupoI = 0; grupoI < 4; grupoI++) {
        fprintf(archivoEstadisticas, "\n================================= GRUPO %c ===================================\n", 'A' + grupoI);
        fprintf(archivoEstadisticas, "| Equipo             | PJ   | PG   | PE   | PP   | Pts  | GF   | GC   | DG   |\n");
        fprintf(archivoEstadisticas, "|--------------------|------|------|------|------|------|------|------|------|\n");
        for (int i = 0; i < 4; i++) {
            fprintf(archivoEstadisticas, "| %-18s | %4d | %4d | %4d | %4d | %4d | %4d | %4d | %4d |\n",
                torneo->gruposEquipos[grupoI].equipos[i].nombre,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PJ,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PG,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PE,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PP,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PTS,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.GF,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.GC,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.DFG);
        }
    }

    fclose(archivoEstadisticas);
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void menuFixture() {
    struct competencia torneo;
    int opcion;
    do {
        printf("\n======================================== MENU FIXTURE ==========================================\n");
        printf("|                                                                                                 |\n");
        printf("|                                  1- VER FIXTURE COMPLETO                                        |\n");
        printf("|                                                                                                 |\n");
        printf("|                                  2- VER UN GRUPO                                                |\n");
        printf("|                                                                                                 |\n");
        printf("|                                  3- CARGAR RESULTADOS                                           |\n");
        printf("|                                                                                                 |\n");
        printf("|                                  4- MODIFICAR DATOS                                             |\n");
        printf("|                                                                                                 |\n");
        printf("|                                  5- VOLVER AL MENU PRINCIPAL                                    |\n");
        printf("|                                                                                                 |\n");
        printf("===================================================================================================\n");

        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion) {
            case 1:
                system("cls");
                verFixtureCompleto();
                break;
            case 2:
                system("cls");
                mostrarUnGrupo();
                break;
            case 3:
                system("cls");
                menuParaCargarResultados();
                break;
            case 4:
                system("cls");
                break;
            case 5:
                system("cls");
                return;
            default:
                system("cls");
                printf("Opcion no valida. Por favor, ingrese una opcion valida.\n");
                break;
        }
    } while (opcion != 5);
}


void verFixtureCompleto() {
    struct competencia torneo;
    archivoEquipo = fopen("Equipos.txt", "r");
    
    if (archivoEquipo == NULL) {
        printf("No se pudo abrir el archivo 'Equipos.txt'. Asegúrate de que el fixture haya sido creado.\n");
        return;
    }
    
    char linea[256];
    printf("\n========================== FIXTURE COMPLETO ==========================\n\n");
    
    while (fgets(linea, sizeof(linea), archivoEquipo) != NULL) {
        printf("%s", linea);  // Muestra cada línea del archivo
    }
    
    fclose(archivoEquipo);
    printf("\n======================================================================\n");
}

void mostrarUnGrupo() {
    struct competencia torneo;
    archivoGrupo = fopen("Grupos.txt", "r");
    if (archivoGrupo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char nombreGrupo;
    printf("Ingrese el grupo que desea ver (A, B, C, D): ");
    scanf(" %c", &nombreGrupo);

    char linea[256];
    int mostrar = 0;
    int grupoEncontrado = 0;

    while (fgets(linea, sizeof(linea), archivoGrupo)) {
        if ((strstr(linea, "GRUPO A") != NULL && (nombreGrupo == 'A' || nombreGrupo == 'a')) ||
            (strstr(linea, "GRUPO B") != NULL && (nombreGrupo == 'B' || nombreGrupo == 'b')) ||
            (strstr(linea, "GRUPO C") != NULL && (nombreGrupo == 'C' || nombreGrupo == 'c')) ||
            (strstr(linea, "GRUPO D") != NULL && (nombreGrupo == 'D' || nombreGrupo == 'd'))) {
            mostrar = 1;
            grupoEncontrado = 1;
        } 
        else if (strstr(linea, "GRUPO") != NULL && grupoEncontrado) {
            break;
        }

        if (mostrar) {
            printf("%s", linea);
        }
    }

    if (!grupoEncontrado) {
        printf("Grupo no encontrado.\n");
    }

    fclose(archivoGrupo);
}

void menuParaCargarResultados() {
    char grupo;
    printf("Seleccione el grupo (A, B, C, D): ");
    scanf(" %c", &grupo);
    grupo = toupper(grupo); 

    if (grupo < 'A' || grupo > 'D') {
        printf("Grupo no válido. Intente de nuevo.\n");
        return;
    }
    archivoGrupo = fopen("Grupos.txt", "r");
    if (archivoGrupo == NULL) {
        printf("Error al abrir el archivo de grupos.\n");
        return;
    }
    cargarResultadosPartido(grupo);

    fclose(archivoGrupo);
}

void cargarResultadosPartido(char grupo) {
    int equipo1, equipo2, goles1, goles2;
    printf("Seleccione el equipo 1 (1-4): ");
    scanf("%d", &equipo1);
    printf("Seleccione el equipo 2 (1-4): ");
    scanf("%d", &equipo2);

    if (equipo1 < 1 || equipo1 > 4 || equipo2 < 1 || equipo2 > 4 || equipo1 == equipo2) {
        printf("Selección de equipos no válida. Intente de nuevo.\n");
        return;
    }
    printf("Ingrese los goles del equipo %d: ", equipo1);
    scanf("%d", &goles1);
    printf("Ingrese los goles del equipo %d: ", equipo2);
    scanf("%d", &goles2);

    actualizarEstadisticas(grupo, equipo1, equipo2, goles1, goles2);
}

void actualizarEstadisticas(char grupo, int equipo1, int equipo2, int goles1, int goles2) {
    struct competencia torneo;
    cargarGrupos(&torneo);

    int grupoIndex = grupo - 'A';
    equipo1--;
    equipo2--;

    torneo.gruposEquipos[grupoIndex].equipos[equipo1].estadisticas.PJ++;
    torneo.gruposEquipos[grupoIndex].equipos[equipo1].estadisticas.GF += goles1;
    torneo.gruposEquipos[grupoIndex].equipos[equipo1].estadisticas.GC += goles2;
    torneo.gruposEquipos[grupoIndex].equipos[equipo1].estadisticas.DFG = 
        torneo.gruposEquipos[grupoIndex].equipos[equipo1].estadisticas.GF - torneo.gruposEquipos[grupoIndex].equipos[equipo1].estadisticas.GC;
    
    torneo.gruposEquipos[grupoIndex].equipos[equipo2].estadisticas.PJ++;
    torneo.gruposEquipos[grupoIndex].equipos[equipo2].estadisticas.GF += goles2;
    torneo.gruposEquipos[grupoIndex].equipos[equipo2].estadisticas.GC += goles1;
    torneo.gruposEquipos[grupoIndex].equipos[equipo2].estadisticas.DFG = 
        torneo.gruposEquipos[grupoIndex].equipos[equipo2].estadisticas.GF - torneo.gruposEquipos[grupoIndex].equipos[equipo2].estadisticas.GC;

    if (goles1 > goles2) {
        torneo.gruposEquipos[grupoIndex].equipos[equipo1].estadisticas.PG++;
        torneo.gruposEquipos[grupoIndex].equipos[equipo1].estadisticas.PTS += 3;
        torneo.gruposEquipos[grupoIndex].equipos[equipo2].estadisticas.PP++;
    } else if (goles1 < goles2) {
        torneo.gruposEquipos[grupoIndex].equipos[equipo2].estadisticas.PG++;
        torneo.gruposEquipos[grupoIndex].equipos[equipo2].estadisticas.PTS += 3;
        torneo.gruposEquipos[grupoIndex].equipos[equipo1].estadisticas.PP++;
    } else {
        torneo.gruposEquipos[grupoIndex].equipos[equipo1].estadisticas.PE++;
        torneo.gruposEquipos[grupoIndex].equipos[equipo2].estadisticas.PE++;
        torneo.gruposEquipos[grupoIndex].equipos[equipo1].estadisticas.PTS += 1;
        torneo.gruposEquipos[grupoIndex].equipos[equipo2].estadisticas.PTS += 1;
    }

    guardarGrupos(&torneo);
    guardarEstadisticas(&torneo);

    printf("Estadísticas actualizadas correctamente.\n");
}

void cargarGrupos(struct competencia *torneo) {
    archivoGrupo = fopen("Grupos.txt", "a");
    if (archivoGrupo == NULL) {
        printf("Error al abrir el archivo de grupos.\n");
        return;
    }

    for (int grupoI = 0; grupoI < 4; grupoI++) {
        fprintf(archivoGrupo, "\n================================= GRUPO %c ===================================\n", 'A' + grupoI);
        fprintf(archivoGrupo, "| Equipo             | PJ   | PG   | PE   | PP   | Pts  | GF   | GC   | DG   |\n");
        fprintf(archivoGrupo, "|--------------------|------|------|------|------|------|------|------|------|\n");
        for (int i = 0; i < 4; i++) {
            fprintf(archivoGrupo, "| %-18s | %4d | %4d | %4d | %4d | %4d | %4d | %4d | %4d |\n",
                torneo->gruposEquipos[grupoI].equipos[i].nombre,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PJ,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PG,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PE,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PP,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.PTS,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.GF,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.GC,
                torneo->gruposEquipos[grupoI].equipos[i].estadisticas.DFG);
        }
    }

    fclose(archivoGrupo);
}

#endif