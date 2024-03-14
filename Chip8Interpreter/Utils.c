#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short grab_last(char *inst) {
    char lastHexString = inst[3];
    char lastHexChar = strtol(&lastHexString, NULL, 16);

    return lastHexChar;
}

short grab_last_two(char *inst) {
    char last_two_hex_chars[3];

    strncpy(last_two_hex_chars, inst + strlen(inst) - 2, 2);

    return strtol(last_two_hex_chars, NULL, 16);
}

short grab_last_three(char *inst) {
    char last_three_hex_chars[4];

    strncpy(last_three_hex_chars, inst + strlen(inst) - 3, 3);

    return strtol(last_three_hex_chars, NULL, 16);
}

short grab_second(char *inst) {
    char secondHexString = inst[1];
    char secondHexChar = strtol(&secondHexString, NULL, 16);

    return secondHexChar;
}

short grab_third(char *inst) {
    char thirdHexString = inst[2];
    char thirdHexChar = strtol(&thirdHexString, NULL, 16);

    return thirdHexChar;
}