#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "funciones.h"
#include "archivo.h"

int main()
{
    setlocale(LC_ALL, "");
    struct Grupo grupos[4];
    menuPrincipal(grupos);
    getchar();
    return 0;
}