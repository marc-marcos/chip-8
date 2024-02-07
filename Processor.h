#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64

struct Processor {
    char registros[16];
    char memoria[4096];
    char stackpointer;
    char screen[SCREEN_HEIGHT*SCREEN_WIDTH];
};