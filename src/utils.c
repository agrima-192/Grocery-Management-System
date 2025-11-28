#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void pauseProgram() {
    printf("\nPress Enter to continue...");
    getchar();
}

void clearScreen() {
    system("clear || cls");
}
