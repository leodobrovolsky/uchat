#include "libmx.h"
#include "sqlite3.h"
#include "cJSON.h"

#define DATABASE_NAME "database.db"
#define TABLE_NAME_USERS "users"
#define TABLE_NAME_ROOMS "rooms"
#define TABLE_NAME_USERS_ROOMS "users_rooms"
#define TABLE_NAME_MESSAGES "messages"
#define TABLE_NAME_ACTIVE_USERS "active_users"
#define TABLE_USERS_COLUMNS 8
#define TABLE_ROOMS_COLUMNS 2
#define TABLE_USERS_ROOMS_COLUMNS 2
#define TABLE_MESSAGES_COLUMNS 5
#define TABLE_ACTIVE_USERS 3
#define BUFFER_SIZE 1025
#define WINDOW_MAIN_WEIGHT 1000
#define WINDOW_MAIN_HEIGHT 700
#define SERVER_INPUT_SIZE 20
#define SERVER_COM_HELP "/help"
#define SERVER_COM_CREATE_MANAGER "/create_manager"
#define SERVER_COM_DELETE_MANAGER "/delete_manager"
#define SERVER_COM_EDIT_MANAGER "/edit_manager"
#define SERVER_COM_MANAGERS "/managers"
#define SERVER_COM_EXIT "/exit"
#define SERVER_COM_ABORT "/abort"
#define SERVER_HELP "/help - справка\n/exit - выход\n/unset - отмена операции\n/create_manager - создать менеджера\n/delete_manager - удалить менеджера\n/edit_manager - изменить данные о менеджере\n/managers - вывести список менеджеров\n"
#define USER_TYPE_USUAL "usual"
#define USER_TYPE_MANAGER "manager"
#define USER_TYPE_ADMIN "admin"

//database
typedef struct s_table {
    char *name;
    char *params;
    char *type;
    char *data;
    struct s_table *next;
} t_table;

typedef struct s_database {
    char *name_db;
    char *name_table;
    t_table *table;
} t_database;

//database
void mx_create_db(char const *name_db);
void mx_create_table(const t_database t_db);
t_table *mx_create_t_table(char *name, char *params, char *type);
void mx_push_t_table(t_table **table, char *name, char *params, char *type);
void mx_push_data_table(t_table **table, char **datas);
void mx_free_t_table(t_table **table);
void mx_insert_data(const t_database t_db);
t_list_arr *mx_select_table(const t_database t_db, char *cond, int columns);
void mx_update_data(t_database t_db, char *condition);
t_table *mx_copy_struct_t_table(t_table *table);
void mx_delete_data(t_database t_db, char *condition);

