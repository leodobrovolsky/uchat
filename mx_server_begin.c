#include "uchat.h"

void mx_server_begin(t_server *s) {
    int size = 0;

    mx_printstr("Введите /help для справки\n");
    while(1) {
        mx_printstr("server-> ");
        s->input_str = mx_strnew(SERVER_INPUT_SIZE);
        size = mx_getch(s->input_str);
        if (size <= 0) {
            mx_strdel(&s->input_str);
            continue;
        }
        //mx_printstr(s->input_str);
        mx_parse_com(s->input_str);
        mx_strdel(&s->input_str);
    }
}
