NAME = server

SRC	 =	src/main.cpp \
		src/server.cpp \
		src/utils.cpp \
		src/client.cpp \
		src/commands.cpp

INC = 	./headers/server.hpp \
		./headers/client.hpp

CC = c++

FLAGS =  -std=c++98
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp $(INC)
		@$(CC) $(FLAGS) -c -o $@ -c $<

$(NAME): $(OBJ) $(INC)
		@$(CC) $(FLAGS) $(OBJ) -o $@
			./server
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all