NAME = libft.a

CC = cc
C_FLAGS = -Wall -Wextra -Werror

SRC_DIR = source
OBJ_DIR = object
INC_DIR = include
C_FILE = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c\
		ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
		ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
		ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c  \
		ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstmap_bonus.c ft_lstadd_front_bonus.c \
		ft_lstiter_bonus.c ft_lstnew_bonus.c ft_lstclear_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c

SRCS = $(addprefix $(SRC_DIR)/, $(C_FILE))
OBJS = $(addprefix $(OBJ_DIR)/, $(C_FILE:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS) $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(C_FLAGS) -I $(INC_DIR)/ -c $^ -o $@
	ar -rcs $(NAME) $@

clean :
	rm -f $(LIBFT_OBJ)
	rm -rf $(OBJ_DIR)
 
fclean : clean
	rm -f $(NAME)

re : 
	make fclean
	make all

PHONY	: all clean fclean re