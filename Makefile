NAME		= minishell
CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g3
SRCS_LIST	= main.c parser.c execute_cmd.c syntax_handler.c spec_sym_handler.c split_command.c parser_utils.c \
			env_handler.c redirect_handler.c split_line.c split_line_utils.c split_command_utils.c \
			echo.c cd.c pwd.c export.c unset.c env.c \
			strings_counter.c execute_bin.c find_env_var.c arrjoin.c \
			redirect_handler_utils.c redirect_handler_utls_2.c
SRCS		= $(addprefix $(SRCS_DIR)/, $(SRCS_LIST))
LIB_FT		= -Llibft -lft
RL_LIB		= -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
OBJ_LIST 	= $(patsubst %.c, %.o, $(SRCS_LIST))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(OBJ_LIST))
INC_DIR		= inc
RL_INC_DIR	= /Users/$(USER)/.brew/opt/readline/include
SRCS_DIR	= srcs
OBJ_DIR		= obj
all:		$(NAME)
$(NAME):	$(OBJ)
#			cd libft && make bonus
			$(CC) $(CFLAGS) $(OBJ) $(LIB_FT) $(RL_LIB) -o $(NAME)
$(OBJ_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -I$(INC_DIR) -I$(RL_INC_DIR) -c $< -o $@
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