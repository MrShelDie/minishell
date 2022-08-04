SRC = 															\
	source/main/main.c											\
	source/main/init_shell_data.c								\
	source/main/destroy_shell_data.c							\
	source/main/parse_env.c										\
																\
	source/map/map.c											\
	source/map/map_private.c									\
																\
	source/vector/vector.c										\
	source/vector/vector_create_from.c							\
	source/vector/vector_private.c								\
																\
	source/lexer/lexer.c										\
	source/lexer/lexer_utils.c									\
																\
	source/parser/parser.c										\
	source/parser/logic_group.c									\
	source/parser/operator.c									\
	source/parser/cmd/cmd.c										\
	source/parser/cmd/fill_argv.c								\
	source/parser/cmd/fill_redir.c								\
	source/parser/cmd/fill_subshell.c							\
	source/parser/cmd/fill_subshell_utils.c						\
	source/parser/error.c										\
																\
	source/builtin/cd_utils.c									\
	source/builtin/cd.c											\
	source/builtin/echo.c										\
	source/builtin/ft_env.c										\
	source/builtin/ft_export.c									\
	source/builtin/ft_export_ut.c								\
	source/builtin/ft_unset.c									\
	source/builtin/pwd.c										\
	source/builtin/get_builtin_nb.c								\
																\
	source/executer/get_cmd_path.c								\
	source/executer/dup_pipe.c									\
	source/executer/dup_redir.c									\
	source/executer/executer.c									\
	source/executer/expand_heredoc.c							\
	source/executer/expand_heredoc_utils.c						\
	source/executer/expand_heredoc_utils2.c						\
	source/executer/read_heredoc.c								\
	source/executer/read_heredoc_utils.c						\
	source/executer/execute_logic_group.c						\
	source/executer/exec_logic_group_utils.c					\
	source/executer/execute_simple_cmd.c						\
	source/executer/exec_simple_cmd_utils.c						\
	source/executer/init_pipex.c								\
	source/executer/destroy_pipex.c								\
																\
	source/get_next_line/get_next_line.c						\
	source/get_next_line/get_next_line_utils.c					\
																\
	source/expand/asterisk.c									\
	source/expand/expand_logic_group.c							\
	source/expand/expand_quote_var/append_expanded_str.c		\
	source/expand/expand_quote_var/append_expanded_str_utils.c	\
	source/expand/expand_quote_var/append_regular_str.c			\
	source/expand/expand_quote_var/append_substr.c				\
	source/expand/expand_quote_var/check_expansion.c			\
	source/expand/expand_quote_var/replace_with_expanded_str.c	\
	source/expand/expand_wildcard/append_dir_name_to_list.c		\
	source/expand/expand_wildcard/get_matched_dir_name_list.c	\
	source/expand/expand_wildcard/is_matched_utils.c			\
	source/expand/expand_wildcard/is_matched.c					\
	source/expand/expand_wildcard/match_arg.c					\
	source/expand/expand_wildcard/match_redir.c					\
																\
	source/signal/signal.c										\
																\
	source/error/error.c

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
