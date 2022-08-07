SRC	= \
	get_next_line.c		\
	get_next_line_utils.c	

OBJ			= ${SRC:.c=.o}
DEP			= ${SRC:.c=.d}

NAME		= get_next_line_private.a
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