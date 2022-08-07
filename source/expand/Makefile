SRC	= \
	asterisk.c										\
	expand_logic_group.c							\
	expand_quote_var/append_expanded_str.c			\
	expand_quote_var/append_expanded_str_utils.c	\
	expand_quote_var/append_regular_str.c			\
	expand_quote_var/append_substr.c				\
	expand_quote_var/check_expansion.c				\
	expand_quote_var/replace_with_expanded_str.c	\
	expand_wildcard/append_dir_name_to_list.c		\
	expand_wildcard/get_matched_dir_name_list.c		\
	expand_wildcard/is_matched_utils.c				\
	expand_wildcard/is_matched.c					\
	expand_wildcard/match_arg.c						\
	expand_wildcard/match_redir.c

OBJ			= ${SRC:.c=.o}
DEP			= ${SRC:.c=.d}

NAME		= expand_private.a
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