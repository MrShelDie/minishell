SRC = 								\
	source/main/main.c				\
	source/main/shell_data.c		\
	source/map/map.c				\
	source/map/map_private.c		\
	source/vector/vector.c			\
	source/executer/executer.c		\
	source/builtin/echo.c			\
	source/vector/vector_private.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

NAME 		= minishell
LIBFT		= source/libft/libft.a
LIBFTDIR	= source/libft
CFLAGS 		= -Wall -Werror -Wextra -g
CPPFLAGS 	= -MMD -I./include

all:		$(LIBFT) $(NAME) Makefile

$(LIBFT):
	@make -C $(LIBFTDIR) all

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@

clean:
	@make -C $(LIBFTDIR) clean
	$(RM) $(OBJ) $(DEP)

fclean:		clean
	@make -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEP)
