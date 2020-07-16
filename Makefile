CLIENT_NAME=client
SERVER_NAME=server
SERVER_USERS_FILE=Users.bin

CPATH=client/
SPATH=server/
CLIENT=$(CPATH)chat_client.c
SERVER=$(SPATH)chat_server.c
OPENSSL = -I./openssl/include

CC=gcc
CFLAGS_CLIENT=-Wformat -Wall -lpthread -lncurses $(CPATH)client_commands.c $(CPATH)visual.c
CFLAGS_SERVER=-Wformat -Wall -lpthread -L./openssl/lib -lssl -lcrypto $(OPENSSL) $(SPATH)linked_list.c $(SPATH)server_clients.c

all: chat_client chat_server

chat_client: $(CLIENT)
	$(CC) $(CFLAGS_CLIENT) $(CLIENT) -o $(CLIENT_NAME)

chat_server: $(SERVER)
	$(CC) $(CFLAGS_SERVER) $(SERVER) -o $(SERVER_NAME)

clean:
	rm -f $(CLIENT_NAME) $(SERVER_NAME) $(SERVER_USERS_FILE)
