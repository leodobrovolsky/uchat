#include "uchat.h"

char **mx_user_create_to_arr(t_user_create *user) {
	char **arr = mx_create_char_arr(TABLE_USERS_COLUMNS);

	arr[0] = mx_strdup(user->id);
	arr[1] = mx_strdup(user->login);
	arr[2] = mx_strdup(user-password);
	arr[3] = mx_strdup(user->name);
	arr[4] = mx_strdup(user->surname);
	arr[5] = mx_strdup(user->email);
	arr[6] = mx_strdup(user->rules);
	arr[7] = mx_strdup(user->status);
	return arr;
}
