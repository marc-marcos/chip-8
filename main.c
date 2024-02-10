#include <stdio.h>

#include "Processor.h"

int main(int argc, char* argv[]) {
    struct Processor p = crearProcessorVacio();

    p.screen[0][1] = 1;

    // imprimir_pantalla(p.screen);
    

    cargar_programa_en_memoria("SpaceInvaders.ch8", &p);
}