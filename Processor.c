#include "Processor.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct Processor crearProcessorVacio() {
    struct Processor ret;

    for (int i = 0; i < 4096; ++i) {
        ret.memoria[i] = 0;
    }

    for (int i = 0; i < 16; ++i) {
        ret.registros[i] = 0;
    }

    ret.stackpointer = 0;

    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            ret.screen[i][j] = 0;
        }
    }

    return ret;
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

// Actualizar pantalla
void imprimir_pantalla(char p[SCREEN_HEIGHT][SCREEN_WIDTH]) {
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            printf("%x", p[i][j]);
        }

        printf("\n");
    }
}

void cargar_programa_en_memoria(char *fileName, struct Processor *p) {
    int fd = open(fileName, O_RDONLY, NULL);
    if (fd == -1) perror("open");
    printf("%d\n", fd);

    char c;
    int i;

    while(read(fd, &c, sizeof(char)) > 0) {
        printf("%x: %x\n", i, c);
        i++;
    }

    printf("\n");
}