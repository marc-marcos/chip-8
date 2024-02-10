#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64

struct Processor {
    unsigned char registros[16];
    unsigned char memoria[4096];
    unsigned char stackpointer;
    unsigned char program_counter;
    unsigned char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
};

void imprimir_memoria(const struct Processor p);
void imprimir_registros(const struct Processor p);
void imprimir_pantalla(unsigned char p[SCREEN_HEIGHT][SCREEN_WIDTH]);

struct Processor crearProcessorVacio();

void cargar_programa_en_memoria(char *fileName, struct Processor *p);

void ejecutarSiguienteInstruccion(struct Processor *p);