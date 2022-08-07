SRC	= \
	get_cmd_path.c								\
	dup_pipe.c									\
	dup_redir.c									\
	executer.c									\
	expand_heredoc.c							\
	expand_heredoc_utils.c						\
	expand_heredoc_utils2.c						\
	read_heredoc.c								\
	read_heredoc_utils.c						\
	execute_logic_group.c						\
	exec_logic_group_utils.c					\
	execute_simple_cmd.c						\
	exec_simple_cmd_utils.c						\
	init_pipex.c								\
	destroy_pipex.c								\

OBJ			= ${SRC:.c=.o}
DEP			= ${SRC:.c=.d}

NAME		= executer_private.a
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
