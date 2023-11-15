CC = gcc
CFLAGS = -Werror -Wall -Wextra
LIBFT = ./libft/libft.a

NAME = minishell
SRC_DIR = source
OBJ_DIR = object
READ = -L/usr/local/lib -lreadline
INC = -Iinclude -I/usr/local/include/readline
SRCS = $(shell find $(SRC_DIR) -name *.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all:  $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INC) $(READ) -o $@ $^

$(LIBFT):
	make -C ./libft

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make fclean -C ./libft
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re