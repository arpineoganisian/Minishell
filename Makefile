NAME		= minishell
CC			= gcc
RM			= rm -rf
<<<<<<< HEAD
CFLAGS		= -Wall -Wextra -Werror -g
SRCS_LIST	= main.c reading_parsing.c execute_cmd.c echo.c
=======
CFLAGS		= -Wall -Wextra -Werror -g3
SRCS_LIST	= main.c parser.c execute_cmd.c syntax_handler.c spec_sym_handler.c split_command.c parser_utils.c \
			env_handler.c redir_handler.c
>>>>>>> Misha
SRCS		= $(addprefix $(SRCS_DIR)/, $(SRCS_LIST))
LIB_FT		= -Llibft -lft
OBJ_LIST 	= $(patsubst %.c, %.o, $(SRCS_LIST))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(OBJ_LIST))
INC_DIR		= inc
SRCS_DIR	= srcs
OBJ_DIR		= obj
all:		$(NAME)
$(NAME):	$(OBJ)
#			cd libft && make bonus
			$(CC) $(CFLAGS) $(OBJ) $(LIB_FT) $(LIB_MLX) -o $(NAME)
$(OBJ_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
$(OBJ_DIR):
			mkdir -p $@
clean:
#			cd libft && make clean
			$(RM) $(OBJ_DIR)
fclean:		clean
#			cd libft && make fclean
			$(RM) $(NAME)
re:			fclean all
.PHONY:		all clean fclean re