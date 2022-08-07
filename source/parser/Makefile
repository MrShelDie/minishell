SRC	= \
	parser.c					\
	logic_group.c				\
	operator.c					\
	unlink_heredoc.c			\
	cmd/cmd.c					\
	cmd/fill_arg_list.c			\
	cmd/fill_redir.c			\
	cmd/fill_subshell.c			\
	cmd/fill_subshell_utils.c	\
	error.c							

OBJ			= ${SRC:.c=.o}
DEP			= ${SRC:.c=.d}

NAME		= parser_private.a
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