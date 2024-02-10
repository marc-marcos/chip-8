#include "Processor.h"
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
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

    ret.program_counter = 0;

    return ret;
}

// Cambiar esto a punteros para que sea más eficiente
void imprimir_memoria(const struct Processor p) {
    for (int i = 0; i < 4096; ++i) {
        if (p.memoria[i] != 0) {
            printf("%x: %x\n", i, p.memoria[i]);
        }
    }

    printf("\n");
}

// Cambiar esto a punteros para que sea más eficiente
void imprimir_registros(const struct Processor p) {
    for (int i = 0; i < 16; ++i) {
        if (p.registros[i] != 0) {
            printf("%x: %x\n", i, p.registros[i]);
        }
    }

    printf("Program counter: %x\n", p.program_counter);
}

// Actualizar pantalla
void imprimir_pantalla(unsigned char p[SCREEN_HEIGHT][SCREEN_WIDTH]) {
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

    unsigned char c;
    int i = 0;

    while(read(fd, &c, sizeof(char)) > 0) {
        p->memoria[i] = c;
        i++;
    }
}

void clear_the_screen(struct Processor *p) {
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            p->screen[i][j] = 0;
        }
    }
}

void ejecutarSiguienteInstruccion(struct Processor *p) {
    unsigned char current_half = p->memoria[p->program_counter];
    unsigned char next_half = p->memoria[(p->program_counter)+1];

    unsigned short current_instruction = (current_half) << 8 | next_half;

    char instruccion_convertida[5];
    sprintf(instruccion_convertida, "%04x", current_instruction);
    printf("%s\n", instruccion_convertida);

    // Detectar que instrucción es y ejecutarla

    // Limpiar la pantalla
    if (strcmp(instruccion_convertida ,"00e0") == 0) {
        printf("DEBUG: cleaning the screen\n");
        clear_the_screen(p);
    }


    // Return from subroutine call
    if (strcmp(instruccion_convertida, "00ee") == 0) {
        printf("DEBUG: Returning from subroutine\n");
    }

    printf("Ejecutando (%x): %x\n", p->program_counter, current_instruction);
    p->program_counter = (p->program_counter)+2;
}