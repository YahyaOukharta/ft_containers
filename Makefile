NAME = a.out

SRCS = main.cpp

FLAGS =  -std=c++98  -std=c++11 -fsanitize=address -g 	#-Wall -Wextra -Werror

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


stack: fclean
	$(COMP) -o stack.out $(FLAGS) tests/stack_tests.cpp
	clear
	./stack.out
	
map:
	$(COMP) -o map.out $(FLAGS) tests/Map_tests.cpp
	clear
	./map.out