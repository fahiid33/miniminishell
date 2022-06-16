
# LDFLAGS = -L/home/fahd/.brew/Cellar/readline/8.1.2/lib
# CPPFLAGS = -I/home/fahd/.brew/Cellar/readline/8.1.2/include

NAME = minishell
NAME_BONUS = 

SRC = minishell.c lexer.c signals.c tokenizing.c utils.c execute.c parse_utils.c builtins.c split.c export-env.c export-env-utils.c 42-GNL/get_next_line.c 42-GNL/get_next_line_utils.c\

		
SRC_BONUS = 


OBJ =  minishell.o lexer.o signals.o tokenizing.o utils.o execute.o parse_utils.o builtins.o split.o export-env.o export-env-utils.o 42-GNL/get_next_line.o 42-GNL/get_next_line_utils.o\

OBJ_BONUS = 


all : $(NAME)

$(NAME):
	
	@gcc  $(SRC) -lreadline  -o $(NAME)
	@gcc  -g $(SRC) -lreadline -o $(NAME)
	@echo "👍👍👍"

$(NAME_BONUS) : 
	@gcc -Wall -Wextra -Werror -g $(SRC_BONUS) -o $(NAME_BONUS)
	@echo "🎁🎁🎁"

bonus: $(NAME_BONUS)

clean :
 
	@rm -f $(OBJ) $(OBJ_BONUS)
	@echo "🚮🚮🚮"

fclean : clean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "🗑️ 🗑️ 🗑️"

re : fclean all