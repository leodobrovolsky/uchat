#include "uchat.h"

int mx_getch(char *input_str) {
    int size = 0;

    size = read(0, input_str, SERVER_INPUT_SIZE);
    input_str[size - 1] = '\0';
    return size;
}
