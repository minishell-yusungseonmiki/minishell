.SUFFIXES : .c .o

NAME=minishell
CC=gcc
PRINTF = printf
CFLAGS= -Werror -Wall -Wextra -I/opt/homebrew/opt/readline/include
LIBFT=./libft/libft.a
LLDB= -g
DEBUG= -g3 -fsanitize=address

SRCS= main.c test_parse.c
OBJS=$(SRCS:.c=.o)

all:  $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L/opt/homebrew/opt/readline/lib -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) fclean -C ./libft
	rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

debug:
	$(MAKE) debug -C ./libft
	$(MAKE) fclean
	$(MAKE) all CFLAGS="$(CFLAGS) $(DEBUG)"

lldb:
	$(MAKE) lldb -C ./libft
	$(MAKE) fclean
	$(MAKE) all CFLAGS="$(CFLAGS) $(LLDB)"

test:
	$(MAKE) 'OBJS=$(TEST_OBJS)' all

.PHONY: all clean fclean re debug lldb test