#include "uchat.h"

char *mx_get_current_time() {
    int times = time(NULL);

    return mx_itoa(times);
}
