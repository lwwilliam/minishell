NAME = minishell.a

SRC = main.c hell_env.c directory.c hell_lexer.c str_ll.c free.c

CC = gcc

# CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRC)
	make libft
	$(CC) $(CFLAGS) $(SRC) -lreadline $(NAME) -o Minishell #-fsanitize=address

libft:
	make -C libft
	cp libft/libft.a .
	mv libft.a $(NAME)

clean :
	rm -f *.o
	make clean -C libft

fclean : clean
	rm -f $(NAME) Minishell
	make fclean -C libft

re : fclean all
	make re -C libft

.PHONY :libft $(NAME)