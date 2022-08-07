SRC	= \
ft_cd_utils.c ft_cd.c ft_echo.c \
ft_env.c ft_exit.c ft_export_utils.c \
ft_export.c ft_pwd.c ft_unset.c \
get_builtin_nb.c 

OBJ			= ${SRC:.c=.o}
DEP			= ${SRC:.c=.d}

NAME		= builtin_private.a
CFLAGS		= -Wall -Werror -Wextra
CPPFLAGS	= -I./../../include -MMD

all:		${NAME}

${NAME}:	${OBJ} Makefile
	ar rcs $@ ${OBJ}

clean:
	${RM} ${OBJ} ${DEP}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean

-include $(DEP)
