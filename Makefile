SRC = 															\
	source/main/main.c											\
	source/main/init_shell_data.c								\
	source/main/destroy_shell_data.c							\
	source/main/parse_env.c										\
	source/main/increase_shlvl.c								\
	source/main/increase_shlvl_utils.c							\
	source/signal/signal.c										\
	source/signal/signal_handler.c								\
	source/error/error.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

NAME 		= minishell

LIBFT		= source/libft/libft.a
LIBFTDIR	= source/libft

BUILTIN		= source/builtin/builtin_private.a
BUILTINDIR	= source/builtin

EXECUTER	= source/executer/executer_private.a
EXECUTERDIR	= source/executer

EXPAND		= source/expand/expand_private.a
EXPANDDIR	= source/expand

PARSER		= source/parser/parser_private.a
PARSERDIR	= source/parser

MAP			= source/map/map_private.a
MAPDIR		= source/map

VECTOR		= source/vector/vector_private.a
VECTORDIR	= source/vector

LEXER		= source/lexer/lexer_private.a
LEXERDIR	= source/lexer

GNL			= source/get_next_line/get_next_line_private.a
GNLDIR		= source/get_next_line

CFLAGS 		= -Wall -Werror -Wextra
CPPFLAGS 	= -MMD -I./include


all:		modules Makefile $(NAME)

modules:
	@make -C $(LIBFTDIR) all
	@make -C $(BUILTINDIR) all
	@make -C $(EXECUTERDIR) all
	@make -C $(EXPANDDIR) all
	@make -C $(PARSERDIR) all
	@make -C $(MAPDIR) all
	@make -C $(VECTORDIR) all
	@make -C $(LEXERDIR) all
	@make -C $(GNLDIR) all

$(NAME):	$(OBJ) $(EXECUTER) $(EXPAND) $(PARSER) $(LEXER) $(MAP) $(VECTOR) $(BUILTIN) $(GNL) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(EXECUTER) $(EXPAND) $(PARSER) $(LEXER) $(MAP) $(VECTOR) $(BUILTIN) $(GNL) $(LIBFT) -lreadline -o $@

clean:
	@make -C $(LIBFTDIR) clean
	@make -C $(GNLDIR) clean
	@make -C $(BUILTINDIR) clean
	@make -C $(EXECUTERDIR) clean
	@make -C $(EXPANDDIR) clean
	@make -C $(PARSERDIR) clean
	@make -C $(MAPDIR) clean
	@make -C $(VECTORDIR) clean
	@make -C $(LEXERDIR) clean
	$(RM) $(OBJ) $(DEP)

fclean:		clean
	@make -C $(LIBFTDIR) fclean
	@make -C $(GNLDIR) fclean
	@make -C $(BUILTINDIR) fclean
	@make -C $(EXECUTERDIR) fclean
	@make -C $(EXPANDDIR) fclean
	@make -C $(PARSERDIR) fclean
	@make -C $(MAPDIR) fclean
	@make -C $(VECTORDIR) fclean
	@make -C $(LEXERDIR) fclean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all modules clean fclean re

-include $(DEP)
