#include "uchat.h"

bool mx_valid(const char *s, int n) {
/*    char f[0] = '.';
    char f[1] = '-';
    char f[2] = '_';//для логина max = 3 n = 1
    char p[0] = '.';
    char p[1] = '@'; //для емейла max = 2 n = 3*/

    int m[3] = {4, 21, 4};
    char w[21] = {'.','_','-','@','!','#','$','^','&','+','=',':',';','.','?','~','<','>','|','`','\''}; //для пароля max  = 20 n = 2
    int a = 0;
    int b = 0;

    if(!s ? 1 : mx_strlen(s) == 0)
        return false;
    if (!mx_isdigit(s[0]) && !mx_isalpha(s[0]) && n != 2)
        return false;
    if (mx_strlen(s) < 4)
        return false;
    for (a = 0; a < mx_strlen(s); a++) {
        if (mx_isdigit(s[a]) || mx_isalpha(s[a]))
            continue;
        for (b = 0; b < m[n]; b++){
            if(s[a] == w[b]){
                b = -5;
                break;
            }
        }
        if (b == -5)
            continue;
        return false;
    }
    return true;
}