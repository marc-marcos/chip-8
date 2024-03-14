#include "Processor.h"
#include "Utils.h"
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

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

    ret.register_i = 0;

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

    printf("Ejecutando (%x): %x\n", p->program_counter, current_instruction);
    p->program_counter = (p->program_counter)+2;

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

    // Jump to address xxx 
    if (instruccion_convertida[0] == '1') {
        short dir = grab_last_three(instruccion_convertida);
        p->program_counter = dir;
    }

    // Jump to subroutine at address xxx
    if (instruccion_convertida[0] == '2') {
        p->stack[p->stackpointer] = p->program_counter;
        (p->stackpointer)++;

        short dir = grab_last_three(instruccion_convertida);
        p->program_counter = dir;
    }

    // UNTESTED FROM HERE ------------------------------------------------------------------------------

    // 3xkk skip next instruction if Vx == kk
    if (instruccion_convertida[0] == '3') {
        if (p->registros[grab_second(instruccion_convertida)] == grab_last_two(instruccion_convertida)) { // Skip
            (p->program_counter)+=2;
        }
    }

    // 4xkk skip next instruction if Vx != kk
    if (instruccion_convertida[0] == '4') {
        if (p->registros[grab_second(instruccion_convertida)] != grab_last_two(instruccion_convertida)) {
            (p->program_counter)+=2;
        }
    }

    // 5xy0 skip if Vx == Vy
    if (instruccion_convertida[0] == '5' && instruccion_convertida[3] == '0') {
        if (p->registros[grab_second(instruccion_convertida)] == p->registros[grab_second(instruccion_convertida)]) {
            (p->program_counter)+=2;
        }
    }

    // 6xkk put value kk in Vx
    if (instruccion_convertida[0] == '6') {
        p->registros[grab_second(instruccion_convertida)] = grab_last_two(instruccion_convertida);
    }

    // 7xkk add the value of Vx and kk and store it in Vx
    if (instruccion_convertida[0] == '7') {
        p->registros[grab_second(instruccion_convertida)] += grab_last_two(instruccion_convertida);
    }

    // 8xy0 Stores the value of register Vy in register Vx
    if (instruccion_convertida[0] == '8' && instruccion_convertida[3] == '0') {
        p->registros[grab_second(instruccion_convertida)] = p->registros[grab_third(instruccion_convertida)];
    }

    // 8xy1 bitwise or on the vlaues of Vx and Vy and store it in Vx.
    if (instruccion_convertida[0] == '8' && instruccion_convertida[3] == '1') {
        p->registros[grab_second(instruccion_convertida)] = p->registros[grab_second(instruccion_convertida)] | p->registros[grab_second(instruccion_convertida)];
    }

    // 8xy2 the same but with an and
    if (instruccion_convertida[0] == '8' && instruccion_convertida[3] == '2') {
        p->registros[grab_second(instruccion_convertida)] = p->registros[grab_second(instruccion_convertida)] & p->registros[grab_second(instruccion_convertida)];
    }

    // 8xy3 the same but with an xor
    if (instruccion_convertida[0] == '8' && instruccion_convertida[3] == '3') {
        p->registros[grab_second(instruccion_convertida)] = p->registros[grab_second(instruccion_convertida)] ^ p->registros[grab_second(instruccion_convertida)];
    }

    // 8xy4 set Vx = Vx + Vy set VF = carry
    if (instruccion_convertida[0] == '8' && instruccion_convertida[3] == '4') {
        p->registros[grab_second(instruccion_convertida)] = p->registros[grab_second(instruccion_convertida)] + p->registros[grab_third(instruccion_convertida)];
        // TODO: añadir lo del carry
    }

    if (instruccion_convertida[0] == '8' && instruccion_convertida[3] == '5') {
        // TODO: añadir lo de VF 
    }

    if (instruccion_convertida[0] == '8' && instruccion_convertida[3] == '6') {
        // TODO: añadir lo de VF
        p->registros[grab_second(instruccion_convertida)] = p->registros[grab_second(instruccion_convertida)] >> 1;
    }

    // TODO: implement this
    if (instruccion_convertida[0] == '8' && instruccion_convertida[3] == '7') {
    }

    if (instruccion_convertida[0] == '8' && instruccion_convertida[3] == 'E') {
        // TODO: añadir lo de VF
        p->registros[grab_second(instruccion_convertida)] = p->registros[grab_second(instruccion_convertida)] << 1;
    }

    if (instruccion_convertida[0] == '9' && instruccion_convertida[3] == '0') {
        if (p->registros[grab_second(instruccion_convertida)] != p->registros[grab_third(instruccion_convertida)]) {
            p->program_counter += 2;
        }
    }

    if (instruccion_convertida[0] == 'a') {
        p->register_i = grab_last_three(instruccion_convertida);
    }

    if (instruccion_convertida[0] == 'b') {
        p->program_counter = (grab_last_three(instruccion_convertida) + p->registros[0]);
    }

    if (instruccion_convertida[0] == 'c') {
        srand(time(NULL));
        short random_number = rand() % 256;

        p->registros[grab_second(instruccion_convertida)] = random_number & grab_last_two(instruccion_convertida);
    }

    if (instruccion_convertida[0] == 'd') {
        // TODO: Implementar lo de los sprites
    }

    if (instruccion_convertida[0] == 'e') {}
}