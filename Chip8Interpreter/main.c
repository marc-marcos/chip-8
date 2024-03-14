#include <stdio.h>
#include <stdlib.h>
#include "Processor.h"

void Usage(char *argv0) {
    printf("%s: %s program-name\n", argv0, argv0);
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc != 2) Usage(argv[0]);

    struct Processor p = crearProcessorVacio();
    cargar_programa_en_memoria(argv[1], &p);

    imprimir_memoria(p);
    ejecutarSiguienteInstruccion(&p);
    imprimir_memoria(p);
    ejecutarSiguienteInstruccion(&p);
    imprimir_memoria(p);
    ejecutarSiguienteInstruccion(&p);
}