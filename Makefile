SRC = 										\
	source/main/main.c						\
	source/main/shell_data.c				\
	source/map/map.c						\
	source/map/map_private.c				\
	source/vector/vector.c					\
	source/vector/vector_private.c			\
	source/lexer/lexer.c					\
	source/lexer/lexer_utils.c				\
	source/parser/parser.c					\
	source/parser/pipe_group.c				\
	source/parser/operator.c				\
	source/parser/cmd/cmd.c					\
	source/parser/cmd/fill_argv.c			\
	source/parser/cmd/fill_redir.c			\
	source/parser/cmd/fill_subshell.c		\
	source/parser/cmd/fill_subshell_utils.c	\
	source/parser/error.c					\
	source/builtin/cd_utils.c				\
	source/builtin/cd.c						\
	source/builtin/echo.c					\
	source/builtin/ft_env.c					\
	source/builtin/ft_export.c				\
	source/builtin/ft_export_ut.c			\
	source/builtin/ft_unset.c				\
	source/builtin/pwd.c					\
	source/executer/ft_heredoc.c			\
	source/executer/ft_heredoc_utils.c		\
	source/executer/pipex_part.c			\
	source/executer/pipex_part_utils1.c		\
	source/executer/pipex_part2.c			\
	source/executer/pipex_part_utils2.c		\
	get_next_line/get_next_line.c			\
	get_next_line/get_next_line_utils.c		\
	source/executer/executer.c						

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
