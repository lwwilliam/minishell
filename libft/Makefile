NAME		= libft.a

SRCS		= ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_strtrim.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
					ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_striteri.c\
					ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
					ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c  ft_split.c \
					ft_lstadd_back.c ft_lstadd_front.c ft_lstdelone.c ft_lstlast.c \
					ft_lstnew.c ft_lstsize.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUS		= ft_lstadd_back.c ft_lstadd_front.c ft_lstdelone.c ft_lstlast.c \
				ft_lstnew.c ft_lstsize.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS		= $(SRCS:.c=.o)

B_OBJS		= $(BONUS:.c=.o)

FLAGS		= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRCS) $(BONUS)
	gcc $(FLAGS) -c $(SRCS) $(BONUS)
	ar rcs $(NAME) $(OBJS) $(B_OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME)
	# make fclean -C ft_printf

re: fclean all