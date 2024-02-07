#include "Processor.h"
#include <stdio.h>

struct Processor crearProcessorVacio() {
    struct Processor ret;

    for (int i = 0; i < 4096; ++i) {
        ret.memoria[i] = 0;
    }

    for (int i = 0; i < 16; ++i) {
        ret.registros[i] = 0;
    }

    ret.stackpointer = 0;

    for (int i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; ++i) {
        ret.screen[i] = 0;
    }
}

// Cambiar esto a punteros para que sea más eficiente
void imprimir_memoria(const struct Processor p) {
    for (int i = 0; i < 4096; ++i) {
        if (p.memoria[i] != 0) {
            printf("%x: %x", i, p.memoria[i]);
        }
    }
}

// Cambiar esto a punteros para que sea más eficiente
void imprimir_registros(const struct Processor p) {
    for (int i = 0; i < 16; ++i) {
        if (p.registros[i] != 0) {
            printf("%x: %x", i, p.registros[i]);
        }
    }
}

