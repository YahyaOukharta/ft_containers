NAME = a.out

SRCS = main.cpp

FLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g

all : $(NAME)

$(NAME) :
	clang++ -o $(NAME) $(FLAGS) $(SRCS) 

clean :
	rm -f *.hpp.gch
	rm -rf *.dSYM

fclean : clean
	rm -f $(NAME)
	rm -f *.out

re : fclean all

c : re
	clear
	./$(NAME)

vector: re
	clang++ -o vector.out $(FLAGS) tests/vector_tests.cpp
	clear
	./vector.out

map: