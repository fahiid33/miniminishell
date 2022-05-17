
LDFLAGS = -L/home/fahd/.brew/Cellar/readline/8.1.2/lib
CPPFLAGS = -I/home/fahd/.brew/Cellar/readline/8.1.2/include

NAME = minishell
NAME_BONUS = 

SRC = minishell.c lexer.c tokenizing.c\
		
SRC_BONUS = 


OBJ =  minishell.o lexer.o tokenizing.o\

OBJ_BONUS = 


all : $(NAME)

$(NAME):
	
<<<<<<< HEAD
	@gcc  -lreadline -g $(SRC) $(LDFLAGS) $(CPPFLAGS) -o $(NAME)
=======
	@gcc  -g $(SRC) -lreadline -o $(NAME)
>>>>>>> af159d0a932ab54ffaa1d74fa74fa0ae1b011ec3
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