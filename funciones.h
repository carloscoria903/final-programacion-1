#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "archivo.h"


void menuPrincipal(struct Grupo grupos[]) {
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
                crearFixture(grupos);
                break;
            case 2:
                system("cls");
                menuFixture(grupos);
                break;
            case 3:
                exit(0);
            default:
                system("cls");
                printf("ingrese una opcion valida.\n");
                break;
        }
    } while (opcion != 3);
}

void limpiarBuffer() {
    while (getchar() != '\n');
}

void crearFixture(struct Grupo grupos[]) {

    FILE *archivoPrueba = fopen("fixture.txt", "r");
    if (archivoPrueba) {
        fclose(archivoPrueba);//cerrar el archivo si existe
        char respuesta;
        printf("el archivo 'fixture.txt' ya existe. esta seguro que quiere continuar (s/n): ");
        scanf(" %c", &respuesta);
        limpiarBuffer(); //limpiar el buffer

        if (respuesta == 's' || respuesta == 'S') {
            //eliminar el archivo
            eliminarArchivoFixture("fixture.txt");
        } else {
            printf("regresando al menu principal \n");
            return; 
        }
    }
    printf("Ingrese el nombre de la competencia: ");
    fgets(nombreCompetencia, sizeof(nombreCompetencia), stdin);
    strtok(nombreCompetencia, "\n"); //para quitar el salto de línea

    for (int grupoI = 0; grupoI < 4; grupoI++) {
        printf("crear grupo %c:\n", letraGrupo[grupoI]);

        for (int i = 0; i < 4; i++) {
            printf("ingresa el nombre del equipo %d: ", i + 1);
            fgets(grupos[grupoI].equipos[i].nombreEquipo, sizeof(grupos[grupoI].equipos[i].nombreEquipo), stdin);
            strtok(grupos[grupoI].equipos[i].nombreEquipo, "\n");

            //inicializar estadisticas
            grupos[grupoI].equipos[i].estadistica.PJ = 0;
            grupos[grupoI].equipos[i].estadistica.PG = 0;
            grupos[grupoI].equipos[i].estadistica.PE = 0;
            grupos[grupoI].equipos[i].estadistica.PP = 0;
            grupos[grupoI].equipos[i].estadistica.GF = 0;
            grupos[grupoI].equipos[i].estadistica.GC = 0;
            grupos[grupoI].equipos[i].estadistica.DFG = 0;
            grupos[grupoI].equipos[i].estadistica.PTS = 0;
        }
    }

    //guardar grupos en archivo
    agregarEquipoAlFixture(grupos, nombreCompetencia);
    
    printf("fixture creado y guardado.\n");
}

void menuFixture(struct Grupo grupos[]) {
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
        printf("|                                  4- MODIFICAR DATOS (NOMBRES)                                   |\n");
        printf("|                                                                                                 |\n");
        printf("|                                  5- MENU PRINCIPAL                                              |\n");
        printf("|                                                                                                 |\n");
        printf("===================================================================================================\n");

        printf("\ningrese una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 1:
                system("cls");
                verFixture(grupos);
                break;
            case 2:
                system("cls");
                verGrupo(grupos);
                break;
            case 3:
                system("cls");
                actualizarEstadisticas(grupos);
                break;
            case 4:
                system("cls");
                modificarNombresEquipos(grupos);
                break;
            case 5:
                system("cls");
                return;
            default:
                system("cls");
                printf("ingrese una opcion valida.\n");
                break;
        }
    } while (opcion != 6);
}

void actualizarEstadisticas(struct Grupo grupos[]) {
    char grupo;
    int equipo1, equipo2, goles1, goles2;

    verGrupo(grupos);  // Mostrar los grupos para seleccionar

    printf("seleccione el grupo (A, B, C, D): ");
    scanf(" %c", &grupo);
    grupo = toupper(grupo);  // Asegurarse de que sea mayúscula

    if (grupo < 'A' || grupo > 'D') {
        printf("ingrese A, B, C o D.\n");
        return;
    }

    int grupoIndex = grupo - 'A'; 

    printf("seleccione el primer equipo (1-4): ");
    scanf("%d", &equipo1);
    printf("seleccione el segundo equipo (1-4): ");
    scanf("%d", &equipo2);
    printf("ingrese los goles del primer equipo: ");
    scanf("%d", &goles1);
    printf("ingrese los goles del segundo equipo: ");
    scanf("%d", &goles2);

    equipo1--;  //indice para el primer equipo
    equipo2--;  //indice para el segundo equipo

    //actualizar estadisticas del primer equipo
    grupos[grupoIndex].equipos[equipo1].estadistica.PJ++;
    grupos[grupoIndex].equipos[equipo1].estadistica.GF += goles1;
    grupos[grupoIndex].equipos[equipo1].estadistica.GC += goles2;
    grupos[grupoIndex].equipos[equipo1].estadistica.DFG = 
        grupos[grupoIndex].equipos[equipo1].estadistica.GF - grupos[grupoIndex].equipos[equipo1].estadistica.GC;
    
    //actualizar estadisticas del segundo equipo
    grupos[grupoIndex].equipos[equipo2].estadistica.PJ++;
    grupos[grupoIndex].equipos[equipo2].estadistica.GF += goles2;
    grupos[grupoIndex].equipos[equipo2].estadistica.GC += goles1;
    grupos[grupoIndex].equipos[equipo2].estadistica.DFG = 
    grupos[grupoIndex].equipos[equipo2].estadistica.GF - grupos[grupoIndex].equipos[equipo2].estadistica.GC;

    //actualizar puntos
    if (goles1 > goles2) {
        grupos[grupoIndex].equipos[equipo1].estadistica.PG++;
        grupos[grupoIndex].equipos[equipo1].estadistica.PTS += 3;
        grupos[grupoIndex].equipos[equipo2].estadistica.PP++;
    } else if (goles1 < goles2) {
        grupos[grupoIndex].equipos[equipo2].estadistica.PG++;
        grupos[grupoIndex].equipos[equipo2].estadistica.PTS += 3;
        grupos[grupoIndex].equipos[equipo1].estadistica.PP++;
    } else {
        grupos[grupoIndex].equipos[equipo1].estadistica.PE++;
        grupos[grupoIndex].equipos[equipo2].estadistica.PE++;
        grupos[grupoIndex].equipos[equipo1].estadistica.PTS += 1;
        grupos[grupoIndex].equipos[equipo2].estadistica.PTS += 1;
    }

    guardarEstadisticasEnArchivo(grupos);
}

void modificarNombresEquipos(struct Grupo grupos[]) {
    char grupoSeleccionado;
    int equipoSeleccionado;
    char nuevoNombre[50];

    //mostrar los grupos
    printf("elija el grupo del equipo que desea modificar (A, B, C, D): ");
    scanf(" %c", &grupoSeleccionado);
    grupoSeleccionado = toupper(grupoSeleccionado);  //convertir a mayuscula

    if (grupoSeleccionado < 'A' || grupoSeleccionado > 'D') {
        printf("ingrese A, B, C o D.\n");
        return;
    }

    int grupoIndex = grupoSeleccionado - 'A';  //cambiar 'A', 'B', 'C', 'D' a  0, 1, 2, 3

    //mostrar los equipos
    printf("grupo %c:\n", grupoSeleccionado);
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, grupos[grupoIndex].equipos[i].nombreEquipo);
    }

    printf("que equipo que desea modificar (1-4): ");
    scanf("%d", &equipoSeleccionado);

    if (equipoSeleccionado < 1 || equipoSeleccionado > 4) {
        printf("el equipo seleccionado no es valido.\n");
        return;
    }

    //ajustar indice del equipo
    equipoSeleccionado--;

    printf("Ingrese el nuevo nombre del equipo: ");
    limpiarBuffer();
    fgets(nuevoNombre, sizeof(nuevoNombre), stdin);
    strtok(nuevoNombre, "\n");

    //actualizar el nombre en la estructura
    strcpy(grupos[grupoIndex].equipos[equipoSeleccionado].nombreEquipo, nuevoNombre);

    //guardar los cambios
    guardarEstadisticasEnArchivo(grupos);

    printf("El nombre del equipo ha sido actualizado exitosamente.\n");
}


#endif