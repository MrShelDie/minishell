SRC	= \
	vector.c											\
	vector_private.c									\
	vector_create_from.c

OBJ			= ${SRC:.c=.o}
DEP			= ${SRC:.c=.d}

NAME		= vector_private.a
CFLAGS		= -Wall -Werror -Wextra -g
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