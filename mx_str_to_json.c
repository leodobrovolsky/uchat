#include "libmx.h"
#include "cJSON.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define CONNECT "0"
#define CONNECT_REQUEST_FILE "mx_connect_request.json"
#define CONNECT_RESPONSE_FILE "mx_connect_response.json"

static int print_preallocated(cJSON *root)
{
    /* declarations */
    char *out = NULL;
    char *buf = NULL;
    char *buf_fail = NULL;
    size_t len = 0;
    size_t len_fail = 0;

    /* formatted print */
    out = cJSON_Print(root);
    printf("%s\n", out);
    exit(0);
    /* create buffer to succeed */
    /* the extra 5 bytes are because of inaccuracies when reserving memory */
    len = strlen(out) + 5;
    buf = (char*)malloc(len);
    if (buf == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(1);
    }

    /* create buffer to fail */
    len_fail = strlen(out);
    buf_fail = (char*)malloc(len_fail);
    if (buf_fail == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(1);
    }

    /* Print to buffer */
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 1)) {
        printf("cJSON_PrintPreallocated failed!\n");
        if (strcmp(out, buf) != 0) {
            printf("cJSON_PrintPreallocated not the same as cJSON_Print!\n");
            printf("cJSON_Print result:\n%s\n", out);
            printf("cJSON_PrintPreallocated result:\n%s\n", buf);
        }
        free(out);
        free(buf_fail);
        free(buf);
        return -1;
    }

}

void mx_stradd(char **str, char const *s) {
    int len_str = 0;
    int len_s = 0;
    char *result = NULL;

    if (!(*str))
        *str = mx_strdup(s);
    else if (s) {
        len_str = mx_strlen(*str);
        len_s = mx_strlen(s);
        result = mx_strnew(len_str + len_s);
        for (int i = 0; i < len_str; i++)
            result[i] = (*str)[i];
        for (int i = len_str; i < len_str + len_s; i++)
            result[i] = s[i - len_str];
        mx_strdel(str);
        *str = mx_strdup(result);
        mx_strdel(&result);
    }
}


static void mx_replace_str2(char **tmp1, char **tmp2, const char *replace, int k) {
    mx_strdel(tmp2);
    *tmp2 = mx_strndup(*tmp1, k);
    mx_stradd(tmp2, replace);  
}

static void mx_replace_str3(char **tmp1, char **tmp2, char **str) {
    mx_strdel(str);
    *str = mx_strdup(*tmp1);
    mx_strdel(tmp1);
    mx_strdel(tmp2);   
}

void mx_replace_str(char **str, const char *sub, const char *replace) {
    char *tmp1 = NULL;
    char *tmp2 = NULL;
    int k = 0;
    int len_sub = 0;
    
    if (!(*str) || !sub || !replace) 
        return;
    len_sub = mx_strlen(sub);
    tmp1 = mx_strdup(*str);
    while (k >= 0) {
        k = mx_get_substr_index(tmp1, sub);
        if (k == -1)
            break;
        mx_replace_str2(&tmp1, &tmp2, replace, k);
        mx_stradd(&tmp2, &tmp1[len_sub + k]);
        mx_strdel(&tmp1);
        tmp1 = mx_strdup(tmp2); 
    }
    mx_replace_str3(&tmp1, &tmp2, str);
}

char *mx_get_current_time() {
    int times = time(NULL);

    return mx_itoa(times);
}

char *mx_connect_request_to_json() {
    char *tmp = mx_file_to_str(CONNECT_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times); 
    mx_strdel(&times);
    return tmp;
}

char *mx_connect_response_to_json(int status) {
    char *tmp = mx_file_to_str(CONNECT_RESPONSE_FILE);
    char *times = mx_get_current_time();
    char *st = mx_itoa(status);

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st); 
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;   
}

int main(int argc, char *argv[]) {
    //char *res = mx_connect_request_to_json();
    char *res = mx_connect_response_to_json(1);

    cJSON *root = NULL;

    
    mx_printstr(res);
    mx_strdel(&res);
    // root = cJSON_Parse(res);
    // if (print_preallocated(root) != 0) {
    //     cJSON_Delete(root);
    //     exit(EXIT_FAILURE);
    // }
    // cJSON_Delete(root);
    //system("leaks -q a.out");
}
