# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 08:41:24 by hboumahd          #+#    #+#              #
#    Updated: 2023/03/15 11:30:32 by hboumahd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CPPFLAGS = -Wall -Wextra -Werror -std=c++98
CPP = c++

SRCS =	src/main.cpp src/server.cpp src/client.cpp src/commands.cpp src/channel.cpp \
		src/utiles/print_error.cpp src/utiles/utiles.cpp src/mode.cpp

SRCOBJ = ${SRCS:.cpp=.o}

Include = includes/ircserv.hpp includes/server.hpp includes/client.hpp includes/channel.hpp

# -g for the debugger
%.o:%.cpp ${Include}
		${CPP} ${CPPFLAGS} -g -c $< -o $@

$(NAME): ${SRCOBJ} 
	@$(CPP) ${CPPFLAGS} $(SRCOBJ) -o $(NAME)
	@echo "|+| make the program [${GREEN}DONE${RESET}]"
	
all: ${NAME}

s:
	@./ircserv 12345 00
c:
	@nc -c 127.0.0.1 12345

clean:
	@rm -f ${SRCOBJ}

fclean: clean
	@rm -f ${NAME}
	@echo "|-| remove the programs  [${RED}DONE${RESET}]"

re: fclean all

# colors used
GREEN = \033[0;92m
RED = \033[0;91m
RESET = \033[0m