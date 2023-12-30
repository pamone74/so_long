# Main makefile

CLIENT = client
SERVER = server
CC_FLAGS = -Wall -Wextra -Werror
CC = cc

SRC_CLIENT = client.c
SRC_SERVER = server.c

LIBFT_DIR = libft

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

all: $(CLIENT) $(SERVER)

$(CLIENT): $(OBJ_CLIENT)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CC_FLAGS) $(OBJ_CLIENT) -o $(CLIENT) -L$(LIBFT_DIR) -lft

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CC_FLAGS) $(OBJ_SERVER) -o $(SERVER) -L$(LIBFT_DIR) -lft

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -r $(CLIENT) $(SERVER) $(OBJ_CLIENT) $(OBJ_SERVER)
	make -C $(LIBFT_DIR) clean
fclean: clean
	rm -rf $(CLIENT) $(SERVER) $(OBJ_CLIENT) $(OBJ_SERVER)
	make -C $(LIBFT_DIR) fclean
re: clean all
	make -C $(LIBFT_DIR) re
