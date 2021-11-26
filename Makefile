NAME = a.out

SRCS = main.cpp

FLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g

COMP=clang++
ifeq ($(shell uname), Linux)
	COMP = g++ -DLINUX
endif

all : $(NAME)

$(NAME) :
	$(COMP) -o $(NAME) $(FLAGS) $(SRCS)

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

vector: fclean
	$(COMP) -o vector.out $(FLAGS) tests/vector_tests.cpp
	clear
	./vector.out

map: