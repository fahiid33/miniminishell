
# CPPFLAGS = -I/Users/fstitou/.brew/opt/readline/inlclude
# LDFLAGS = -L/Users/fstitou/.brew/opt/readline/lib
CPPFLAGS = -I/goinfre/fstitou/homebrew/opt/readline/include
LDFLAGS = -L/goinfre/fstitou/homebrew/opt/readline/lib

NAME = minishell
NAME_BONUS = 

CFLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=address
		
SRC = *.c parse/*.c execution/*.c
SRC_BONUS = 


OBJ = $(SRC:.c=.o)
OBJ_BONUS = 


all : $(NAME)

$(NAME):
	
	@gcc  $(CFLAGS) -g $(SRC) $(LDFLAGS) $(CPPFLAGS) -lreadline  -o $(NAME) $(SANITIZE)
	@echo "Mino 👍👍👍"

$(NAME_BONUS) : 
	@gcc $(CFLAGS) -g $(SRC_BONUS) -o $(NAME_BONUS)
	@echo "🎁🎁🎁"

bonus: $(NAME_BONUS)

clean :
 
	@rm -f $(OBJ) $(OBJ_BONUS)
	@echo "🚮🚮🚮"

fclean : clean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "🗑️ 🗑️ 🗑️"

re : fclean all
	@rm -r *.dSYM