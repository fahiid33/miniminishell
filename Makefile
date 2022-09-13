
CPPFLAGS = -I/Users/fstitou/.brew/opt/readline/inlclude
LDFLAGS = -L/Users/fstitou/.brew/opt/readline/lib

NAME = minishell
NAME_BONUS = 

SRC = minishell.c lexer.c signals.c tokenizing.c utils.c utils2.c execute.c parse_utils.c builtins.c split.c\
		export-env.c export-env-utils.c cd.c echo.c env.c execute_utils.c exit.c export.c pwd.c unset.c\
		redirections.c here_doc.c\

		
SRC_BONUS = 


OBJ = minishell.o lexer.o signals.o tokenizing.o utils.o utils2.o execute.o parse_utils.o builtins.o split.o\
		export-env.o export-env-utils.o cd.o echo.o env.o execute_utils.o exit.o export.o pwd.o unset.o\
		redirections.o here_doc.o\

OBJ_BONUS = 


all : $(NAME)

$(NAME):
	
	@gcc  -Wall -Wextra -Werror $(SRC) $(LDFLAGS) $(CPPFLAGS) -lreadline  -o $(NAME)
	@echo "HUMAMA MQWD 👍👍👍"

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