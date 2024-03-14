#include <stdio.h>
#include <assert.h>
#include "Utils.h"


int main() {
    // Testing UTILS
    short a = grab_last("bbbb");
    assert(a == 0xb);

    a = grab_last_two("bbbb");
    assert(a == 0xbb);

    a = grab_last_three("bbbb");
    assert(a == 0xbbb);

    a = grab_third("abcd");
    assert(a == 0xc);

    a = grab_second("abcd");
    assert(a == 0xb);

    printf("\033[0;32m");
    printf("Tested all functions successfully!\n");
    printf("\033[0m");
}