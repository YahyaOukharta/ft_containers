NAME = a.out

SRCS = main.cpp

FLAGS = -Wall -Wextra -Werror -std=c++98

all : $(NAME)

$(NAME) :
	g++ -o $(NAME) $(FLAGS) $(SRCS) 

clean :
	rm -f *.hpp.gch

fclean : clean
	rm -f $(NAME)

re : fclean all

c : fclean all
	clear
	./$(NAME)