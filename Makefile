# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 08:45:10 by lahammam          #+#    #+#              #
#    Updated: 2023/03/02 10:42:58 by lahammam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_irc

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS =	main.cpp server/server.cpp server/cmd_auth.cpp server/cmd.cpp utiles/utiles.cpp utiles/print_error.cpp user/user.cpp 

Include	=  ft_irc.hpp server/server.hpp user/user.hpp  

OBJSRC = ${SRCS:.cpp=.o}

CC = c++

%.o:%.cpp ${Include}
		${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJSRC}  
	${CC} ${CFLAGS} ${OBJSRC} -o ${NAME} 

all: ${NAME}


clean:
	rm -f ${OBJSRC}

fclean: clean
	rm -f ${NAME}

re: fclean all
