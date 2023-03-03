NAME = minishell.a

SRC = main.c hell_env.c directory.c hell_lexer.c hell_lexer2.c \
		str_ll.c free.c export_unset.c echo.c execve.c hell_expand.c \
		built_in.c heredoc.c

CC = gcc

INC :=  -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

# CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRC)
	make libft
	$(CC) $(CFLAGS) $(SRC) $(INC) $(NAME) -o Minishell #-fsanitize=address -g

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

f:
	rm -r Minishell.dSYM

.PHONY :libft $(NAME)