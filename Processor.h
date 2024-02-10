#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64

struct Processor {
    char registros[16];
    char memoria[4096];
    char stackpointer;
    char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
};

void imprimir_memoria(const struct Processor p);
void imprimir_registros(const struct Processor p);
void imprimir_pantalla(char p[SCREEN_HEIGHT][SCREEN_WIDTH]);

struct Processor crearProcessorVacio();

void cargar_programa_en_memoria(char *fileName, struct Processor *p);