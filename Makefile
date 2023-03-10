# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 08:41:24 by hboumahd          #+#    #+#              #
#    Updated: 2023/03/10 11:15:26 by alouzizi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CPPFLAGS = -Wall -Wextra -Werror -std=c++98
CPP = c++

SRCS =	src/main.cpp src/server.cpp src/client.cpp src/commands.cpp src/channel.cpp \
		src/utiles/print_error.cpp src/utiles/utiles.cpp src/mode.cpp

SRCOBJ = ${SRCS:.cpp=.o}

OBJS_FILES =	main.o server.o client.o commands.o \
				print_error.o utiles.o mode.o channel.o
OBJS_FOLDER =	./src/output/
SRCOBJ_OUT = $(addprefix $(OBJS_FOLDER), $(OBJS_FILES))

Include = includes/ircserv.hpp includes/server.hpp includes/client.hpp includes/channel.hpp

# -g for the debugger
%.o:%.cpp ${Include} 
		${CPP} ${CPPFLAGS} -g -c $< -o $@
		@mv $@ ./src/output/
		

$(NAME): ${SRCOBJ} 
	$(CPP) ${CPPFLAGS} $(SRCOBJ_OUT) -o $(NAME)
	@echo "|+| make the program [${GREEN}DONE${RESET}]"

s:
	@./ircserv 12345 00
c:
	@nc 127.0.0.1 12345 55

all: ${NAME}

clean:
	@rm -f ${SRCOBJ_OUT}

fclean: clean
	@rm -f ${NAME}
	@echo "|-| remove the programs  [${RED}DONE${RESET}]"

re: fclean all

# colors used
GREEN = \033[0;92m
RED = \033[0;91m
RESET = \033[0m