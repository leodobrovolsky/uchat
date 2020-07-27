#include "uchat.h"

void mx_print_error_json(cJSON *root) {
    if(PRINT_JSON_ERROR) {
        if (EXIT_PRINT_ERROR) {
        	mx_printstr("Error json\n");
            print_preallocated(root);
            exit(1);
        }
        else {
        	mx_printstr("Error json\n");
            print_preallocated(root);
        }
    }
}
