#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "Processor.h"

int main() {
    unsigned char a = 0x12;
    unsigned char b = 0x34;

    printf("%x\n", (a<<8)+b);
}