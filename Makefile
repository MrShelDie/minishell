SRC = 															\
	source/main/main.c											\
	source/main/shell_data.c									\
	source/map/map.c											\
	source/map/map_private.c									\
	source/vector/vector.c										\
	source/vector/vector_create_from.c							\
	source/vector/vector_private.c								\
	source/lexer/lexer.c										\
	source/lexer/lexer_utils.c									\
	source/parser/parser.c										\
	source/parser/pipe_group.c									\
	source/parser/operator.c									\
	source/parser/cmd/cmd.c										\
	source/parser/cmd/fill_argv.c								\
	source/parser/cmd/fill_redir.c								\
	source/parser/cmd/fill_subshell.c							\
	source/parser/cmd/fill_subshell_utils.c						\
	source/parser/error.c										\
	source/builtin/cd_utils.c									\
	source/builtin/cd.c											\
	source/builtin/echo.c										\
	source/builtin/ft_env.c										\
	source/builtin/ft_export.c									\
	source/builtin/ft_export_ut.c								\
	source/builtin/ft_unset.c									\
	source/builtin/pwd.c										\
	source/executer/executer.c									\
	source/executer/ft_heredoc.c								\
	source/executer/ft_heredoc_utils.c							\
	source/executer/pipex_part.c								\
	source/executer/pipex_part_utils1.c							\
	source/executer/pipex_part2.c								\
	source/executer/pipex_part_utils2.c							\
	get_next_line/get_next_line.c								\
	get_next_line/get_next_line_utils.c							\
	source/expand/asterisk.c									\
	source/expand/expand_pipe_group.c							\
	source/expand/expand_quote_var/append_expanded_str.c		\
	source/expand/expand_quote_var/append_regular_str.c			\
	source/expand/expand_quote_var/append_substr.c				\
	source/expand/expand_quote_var/check_expansion.c			\
	source/expand/expand_quote_var/replace_with_expanded_str.c	\
	source/expand/expand_wildcard/append_dir_name_to_list.c		\
	source/expand/expand_wildcard/get_matched_dir_name_list.c	\
	source/expand/expand_wildcard/is_matched_utils.c			\
	source/expand/expand_wildcard/is_matched.c					\
	source/expand/expand_wildcard/match_arg.c					\
	source/expand/expand_wildcard/match_redir.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

NAME 		= minishell
LIBFT		= source/libft/libft.a
LIBFTDIR	= source/libft
CFLAGS 		= -g
CPPFLAGS 	= -MMD -I./include

all:		$(LIBFT) $(NAME) Makefile

$(LIBFT):
	@make -C $(LIBFTDIR) all

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $@

clean:
	@make -C $(LIBFTDIR) clean
	$(RM) $(OBJ) $(DEP)

fclean:		clean
	@make -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEP)
