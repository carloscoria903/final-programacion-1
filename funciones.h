#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estructuras.h"

void menuPrincipal() {
    int opcion;
    do {
        printf("\n======================================== MENU PRINCIPAL ========================================");
        printf("\n|                                                                                             |");
        printf("\n|                                  1- CREAR FIXTURE                                           |");
        printf("\n|                                                                                             |");
        printf("\n|                                  2- VER FIXTURE                                             |");
        printf("\n|                                                                                             |");
        printf("\n|                                  3- SALIR                                                   |");
        printf("\n|                                                                                             |\n");
        printf("================================================================================================\n");

        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion) {
            case 1:
                system("cls");
                crearFixture();
                break;
            case 2:
                system("cls");
                verFixture();
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

/*void crearFixture() {
    struct competencia torneo;
    int grupoIndex;

    printf("Ingresa el nombre de la competencia: ");
    fgets(torneo.nombre, sizeof(torneo.nombre), stdin);
    strtok(torneo.nombre, "\n"); //consumir el salto de línea

    //abrir archivos para guardar datos
    archivoGrupo = fopen("Grupo.txt", "w");
    archivoEquipo = fopen("Equipos.txt", "w");
    
    if (archivoGrupo == NULL || archivoEquipo == NULL) {
        printf("Error al abrir los archivos.\n");
        return;
    }

    for (int grupoI = 0; grupoI < 4; grupoI++) {
        printf("Crear grupo %d:\n", grupoI + 1);

        //leer nombres de equipos
        for (int i = 0; i < 4; i++) {
            printf("Ingresa el nombre del equipo %d: ", i + 1);
            fgets(torneo.gruposEquipos[grupoI].nombreEquipos[i].nombre, sizeof(torneo.gruposEquipos[grupoI].nombreEquipos[i].nombre), stdin);
            strtok(torneo.gruposEquipos[grupoI].nombreEquipos[i].nombre, "\n"); // Consumir el salto de línea
            fprintf(archivoEquipo, "Equipo %d: %s\n",i + 1 ,torneo.gruposEquipos[grupoI].nombreEquipos[i].nombre); // Guardar en el archivo de equipos
        }

        //inicializar estadísticas del grupo
        torneo.gruposEquipos[grupoI].PJ = 0;
        torneo.gruposEquipos[grupoI].PG = 0;
        torneo.gruposEquipos[grupoI].PE = 0;
        torneo.gruposEquipos[grupoI].PP = 0;
        torneo.gruposEquipos[grupoI].GC = 0;
        torneo.gruposEquipos[grupoI].GF = 0;
        torneo.gruposEquipos[grupoI].DFG = 0;
        torneo.gruposEquipos[grupoI].PTS = 0;

        //guardar los grupo en el archivo de grupos
        fprintf(archivoGrupo, "\n================================= GRUPO %c ===================================\n", 'A' + grupoI);
        fprintf(archivoGrupo, "| Equipo             | PJ   | PG   | PE   | PP   | Pts  | GF   | GC   | DG   |\n");
        fprintf(archivoGrupo, "|--------------------|------|------|------|------|------|------|------|------|\n");
        for (int i = 0; i < 4; i++) {
            fprintf(archivoGrupo, "| %-18s | %4d | %4d | %4d | %4d | %4d | %4d | %4d | %4d |\n",
                torneo.gruposEquipos[grupoI].nombreEquipos[i].nombre,
                torneo.gruposEquipos[grupoI].PJ,
                torneo.gruposEquipos[grupoI].PG,
                torneo.gruposEquipos[grupoI].PE,
                torneo.gruposEquipos[grupoI].PP,
                torneo.gruposEquipos[grupoI].PTS,
                torneo.gruposEquipos[grupoI].GF,
                torneo.gruposEquipos[grupoI].GC,
                torneo.gruposEquipos[grupoI].DFG);
        }
    }

    //cerrar los archivos
    fclose(archivoGrupo);
    fclose(archivoEquipo);
    printf("Grupos creados y guardados correctamente.\n");
}*/

// Función para limpiar el buffer después de usar scanf
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void crearFixture() {
    struct competencia torneo;
    int grupoIndex;

    printf("Ingresa el nombre de la competencia: ");
    fgets(torneo.nombre, sizeof(torneo.nombre), stdin);
    strtok(torneo.nombre, "\n"); // Consumir el salto de línea

    // Abrir archivos para guardar datos
    archivoGrupo = fopen("Grupo.txt", "w");
    archivoEquipo = fopen("Equipos.txt", "w");
    
    if (archivoGrupo == NULL || archivoEquipo == NULL) {
        printf("Error al abrir los archivos.\n");
        return;
    }

    for (int grupoI = 0; grupoI < 4; grupoI++) {
        printf("Crear grupo %d:\n", grupoI + 1);

        // Leer nombres de equipos y estadísticas
        for (int i = 0; i < 4; i++) {
            printf("Ingresa el nombre del equipo %d: ", i + 1);
            fgets(torneo.gruposEquipos[grupoI].nombreEquipos[i].nombre, sizeof(torneo.gruposEquipos[grupoI].nombreEquipos[i].nombre), stdin);
            strtok(torneo.gruposEquipos[grupoI].nombreEquipos[i].nombre, "\n"); // Consumir el salto de línea

            // Pedir estadísticas del equipo
            printf("Estadísticas para %s:\n", torneo.gruposEquipos[grupoI].nombreEquipos[i].nombre);
            printf("Partidos Jugados: ");
            scanf("%d", &torneo.gruposEquipos[grupoI].PJ);
            printf("Partidos Ganados: ");
            scanf("%d", &torneo.gruposEquipos[grupoI].PG);
            printf("Partidos Empatados: ");
            scanf("%d", &torneo.gruposEquipos[grupoI].PE);
            printf("Partidos Perdidos: ");
            scanf("%d", &torneo.gruposEquipos[grupoI].PP);
            printf("Goles a Favor: ");
            scanf("%d", &torneo.gruposEquipos[grupoI].GF);
            printf("Goles en Contra: ");
            scanf("%d", &torneo.gruposEquipos[grupoI].GC);

            limpiarBuffer();

            // Calcular diferencia de goles y puntos
            torneo.gruposEquipos[grupoI].DFG = torneo.gruposEquipos[grupoI].GF - torneo.gruposEquipos[grupoI].GC;
            torneo.gruposEquipos[grupoI].PTS = (torneo.gruposEquipos[grupoI].PG * 3) + (torneo.gruposEquipos[grupoI].PE);

            // Guardar en el archivo de equipos
            fprintf(archivoEquipo, "Equipo %d: %s\n", i + 1, torneo.gruposEquipos[grupoI].nombreEquipos[i].nombre);
        }

        // Guardar el grupo y las estadísticas en el archivo de grupos
        fprintf(archivoGrupo, "\n================================= GRUPO %c ===================================\n", 'A' + grupoI);
        fprintf(archivoGrupo, "| Equipo             | PJ   | PG   | PE   | PP   | Pts  | GF   | GC   | DG   |\n");
        fprintf(archivoGrupo, "|--------------------|------|------|------|------|------|------|------|------|\n");
        for (int i = 0; i < 4; i++) {
            fprintf(archivoGrupo, "| %-18s | %4d | %4d | %4d | %4d | %4d | %4d | %4d | %4d |\n",
                torneo.gruposEquipos[grupoI].nombreEquipos[i].nombre,
                torneo.gruposEquipos[grupoI].PJ,
                torneo.gruposEquipos[grupoI].PG,
                torneo.gruposEquipos[grupoI].PE,
                torneo.gruposEquipos[grupoI].PP,
                torneo.gruposEquipos[grupoI].PTS,
                torneo.gruposEquipos[grupoI].GF,
                torneo.gruposEquipos[grupoI].GC,
                torneo.gruposEquipos[grupoI].DFG);
        }
    }

    // Cerrar los archivos
    fclose(archivoGrupo);
    fclose(archivoEquipo);
    printf("Grupos creados, estadísticas cargadas y guardadas correctamente.\n");
}


void verFixture() {
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
                //cargarResultadosPorEquipo();
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
    archivoEquipo = fopen("Equipos.txt", "r");
    
    if (archivoEquipo == NULL) {
        printf("No se pudo abrir el archivo 'Equipos.txt'. Asegúrate de que el fixture haya sido creado.\n");
        return;
    }
    
    char linea[256];
    printf("\n========================== FIXTURE COMPLETO ==========================\n\n");
    
    while (fgets(linea, sizeof(linea), archivoEquipo) != NULL) {
        printf("%s", linea);  //muestra cada linea del archivo
    }
    
    fclose(archivoEquipo);
    printf("\n======================================================================\n");
}


void mostrarUnGrupo() {
   archivoGrupo = fopen("Grupo.txt", "r");
    if (archivoGrupo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char nombreGrupo;
    printf("Ingrese el grupo que desea ver (A, B, C, D): ");
    scanf(" %c", &nombreGrupo);

    char linea[256];
    int mostrar = 0; //indica si se deben mostrar las lineas del grupo
    int grupoEncontrado = 0; //indica si se ha encontrado el grupo

    while (fgets(linea, sizeof(linea), archivoGrupo)) {
        //verificamos si la linea contiene el nombre del grupo
        if ((strstr(linea, "GRUPO A") != NULL && (nombreGrupo == 'A' || nombreGrupo == 'a')) ||
            (strstr(linea, "GRUPO B") != NULL && (nombreGrupo == 'B' || nombreGrupo == 'b')) ||
            (strstr(linea, "GRUPO C") != NULL && (nombreGrupo == 'C' || nombreGrupo == 'c')) ||
            (strstr(linea, "GRUPO D") != NULL && (nombreGrupo == 'D' || nombreGrupo == 'd'))) {
            mostrar = 1; //comenzar a mostrar lineas
            grupoEncontrado = 1; //se encontro el grupo
        } 
        //cuando encontramos otro grupo, dejamos de mostrar
        else if (strstr(linea, "GRUPO") != NULL && grupoEncontrado) {
            break; //salir del bucle si ya mostramo el grupo
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


















//struct competencia torneo;

// Función para cargar los resultados de un partido
/*void cargarResultados() {
    struct competencia torneo;
    struct grupos grupoActual;
    int equipo1, equipo2, goles1, goles2;

    // Mostrar los equipos del grupo
    printf("Seleccione el equipo 1:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, grupoActual.nombreEquipos[i].nombre);
    }
    scanf("%d", &equipo1);

    printf("Seleccione el equipo 2:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, grupoActual.nombreEquipos[i].nombre);
    }
    scanf("%d", &equipo2);

    // Pedir los goles de ambos equipos
    printf("Ingrese los goles de %s: ", grupoActual.nombreEquipos[equipo1 - 1].nombre);
    scanf("%d", &goles1);
    printf("Ingrese los goles de %s: ", grupoActual.nombreEquipos[equipo2 - 1].nombre);
    scanf("%d", &goles2);

    // Actualizar estadísticas
    // Partidos jugados
    grupoActual.PJ += 1; // Para ambos equipos, ya que ambos juegan un partido

    // Goles a favor y en contra
    grupoActual.GF += goles1;
    grupoActual.GC += goles2;
    grupoActual.GF += goles2;
    grupoActual.GC += goles1;

    // Diferencia de goles
    grupoActual.DFG += (goles1 - goles2);
    grupoActual.DFG += (goles2 - goles1);

    // Actualización de puntos y resultados
    if (goles1 > goles2) {
        // Equipo 1 gana
        grupoActual.PG += 1;
        grupoActual.PP += 1;
        grupoActual.PTS += 3;
    } else if (goles2 > goles1) {
        // Equipo 2 gana
        grupoActual.PP += 1;
        grupoActual.PG += 1;
        grupoActual.PTS += 3;
    } else {
        // Empate
        grupoActual.PE += 1;
        grupoActual.PTS += 1;
    }

    // Guardar los datos actualizados en el archivo
    archivoGrupo = fopen("grupos.dat", "r+b");
    if (archivoGrupo == NULL) {
        printf("Error al abrir el archivo de grupos.\n");
        return;
    }

    // Buscar el grupo y actualizarlo
    fseek(archivoGrupo, sizeof(struct grupos) * (equipo1 - 1), SEEK_SET);
    fwrite(grupoActual, sizeof(struct grupos), 1, archivoGrupo);

    fclose(archivoGrupo);
}*/



