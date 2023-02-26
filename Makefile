# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 08:45:10 by lahammam          #+#    #+#              #
#    Updated: 2023/02/26 10:41:17 by lahammam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = server

# CFLAGS = -Wall -Wextra -Werror -std=c++98

# SRCS =	main.cpp\
# 		client.cpp
# Include	=  

# OBJSRC = ${SRCS:.cpp=.o}

# CC = c++

# %.o:%.cpp ${Include}
# 		${CC} ${CFLAGS} -c $< -o $@

# $(NAME): ${OBJSRC}  
# 	${CC} ${CFLAGS} ${OBJSRC} -o ${NAME} 

# all: ${NAME}
all:
	g++ client.cpp -o client
	g++ server.cpp -o server

clean:
	# rm -f ${OBJSRC}
	rm -f *.o
	rm -rf client server

fclean: clean
	rm -f ${NAME}

re: fclean all
