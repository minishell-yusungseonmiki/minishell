CC = gcc
CFLAGS = -Werror -Wall -Wextra
LIBFT = ./libft/libft.a

NAME = minishell
SRC_DIR = source
READ = -L/usr/local/lib -lreadline
INC = -Iinclude -I/usr/local/include/readline

BUILTIN_SRC = builtin_cd.c builtin_echo.c builtin_env.c builtin_exit.c builtin_export.c\
		builtin_export_print.c builtin_pwd.c builtin_unset.c builtin.c
EXEC_SRC = execute_process.c execute.c
TOKEN_SRC = change_value.c erase_quotes.c pre_check.c tokenize_util.c tokenize.c
PROC_SRC = env.c heredoc.c make_proc_info.c make_proc_list.c make_proc_util.c open_fd.c
SIGNAL_SRC = sigint_handler.c signal_print.c sigquit_handler.c
UTIL_SRC = error.c free.c get_next_line.c util.c
MAIN_SRC = main.c

SRCS = $(addprefix $(SRC_DIR)/builtin/, $(BUILTIN_SRC)) \
		$(addprefix $(SRC_DIR)/execute/, $(EXEC_SRC)) \
		$(addprefix $(SRC_DIR)/make_token/, $(TOKEN_SRC)) \
		$(addprefix $(SRC_DIR)/proc_info/, $(PROC_SRC)) \
		$(addprefix $(SRC_DIR)/signal/, $(SIGNAL_SRC)) \
		$(addprefix $(SRC_DIR)/util/, $(UTIL_SRC)) \
		$(addprefix $(SRC_DIR)/, $(MAIN_SRC))
OBJS = $(SRCS:.c=.o)

all:  $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INC) $(READ) -o $@ $(OBJS) $(LIBFT)

$(LIBFT):
	make -C ./libft

%.o : $(SRC_DIR)/$(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make fclean -C ./libft
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
