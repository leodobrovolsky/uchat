#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//#include <conio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define BAD_MESSAGE         -13
#define SUCCESS               0
 
// typedef struct someArgs_tag {
//     int id;
//     const char *msg;
//     int out;
// } someArgs_t;
 
// void* helloWorld(void *args) {
//     someArgs_t *arg = (someArgs_t*) args;
//     int len;
 
//     if (arg->msg == NULL) {
//         return NULL;
//     }
 
//     len = strlen(arg->msg);
//     printf("%s\n", arg->msg);
//     arg->out = len;
 
//     return SUCCESS;
// }
 
// #define NUM_THREADS 4
 
// int main() {
//     pthread_t threads[NUM_THREADS];
//     int status;
//     int i;
//     int status_addr;
//     someArgs_t args[NUM_THREADS];
//     const char *messages[] = {
//         "First",
//         "123",
//         "Third Message",
//         "Fourth Message"
//     };
 
//     for (i = 0; i < NUM_THREADS; i++) {
//         args[i].id = i;
//         args[i].msg = messages[i];
//     }
 
//     for (i = 0; i < NUM_THREADS; i++) {
//         status = pthread_create(&threads[i], NULL, helloWorld, (void*) &args[i]);
//         if (status != 0) {
//             printf("main error: can't create thread, status = %d\n", status);
//             exit(ERROR_CREATE_THREAD);
//         }
//     }
 
//     printf("Main Message\n");
 
//     for (i = 0; i < NUM_THREADS; i++) {
//         status = pthread_join(threads[i], (void**)&status_addr);
//         if (status != SUCCESS) {
//             printf("main error: can't join thread, status = %d\n", status);
//             exit(ERROR_JOIN_THREAD);
//         }
//         printf("joined with address %d\n", status_addr);
//     }
 
//     for (i = 0; i < NUM_THREADS; i++) {
//         printf("thread %d arg.out = %d\n", i, args[i].out);
//     }
 
//     //_getch();
//     return 0;
// }

void *print_hello(void *str) {
    printf("hello\n");
    return SUCCESS;
}

typedef struct s_list {
    char *name;
} t_list;

void *change_name(void *head) {
    pthread_t treat;
    t_list *head1 = (t_list*)head;
    head1->name = strdup("name");
    pthread_create(&treat, NULL, print_hello, &head1->name);
    //head1->name = strdup("name");
    return SUCCESS;
}

void *print_mess(void *str) {
    //sleep(5);
    printf("%s\n", str);
    return SUCCESS;
}

int main() {
    pthread_t treat1;
    pthread_t treat2;
    t_list *head = malloc(sizeof(t_list));
    head->name = strdup("list");
    printf("%s\n", head->name);

    char buf[100];

    pthread_create(&treat1, NULL, change_name, &head);
    sleep(1);
    pthread_create(&treat2, NULL, print_mess, &head->name);
    scanf("%c", buf);
    return 0;
}

