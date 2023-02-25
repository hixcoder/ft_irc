# ft_irc
### Create your own IRC server in C++, fully compatible with an official client.  
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bind.txt                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 11:18:21 by lahammam          #+#    #+#              #
#    Updated: 2023/02/25 12:31:06 by lahammam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

tcp et udp : des protocoles de transmission des données

tcp : transmission control protocol 
    - three-way handshake, guarntee that the data is received correctly.
udp : user datagram protocol
    - fire and forget protocol, faster than TCP, 


### bind

- the Socket need to bind with specific IP address amd port number, for linsting to incoming commections.
- The syntax : 
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    . sockfd : file descriptor returned by the socket.
    . addr : is a pointer to a sockaddr structure that 
        contains the IP address and port number to bind the socket to.
        struct sockaddr {
            unsigned short sa_family;    // Address family    // 2 bytes
            char sa_data[14];            // Up to 14 bytes of direct address
        };
        struct sockaddr_in {
            short int sin_family;           // Address family, AF_INET  // 2 bytes
            unsigned short int sin_port;    // Port number  // 2 bytes
            struct in_addr sin_addr;        // Internet address  // 4 bytes
            unsigned char sin_zero[8];      // Same size as struct sockaddr // 8 bytes
        };
        - The inet_addr() function is used to convert a string representation of an IPv4 address to 
            its binary form.
        - The htons() function is used to convert the port number to network byte order. 
    . addrlen : The size of addr in bytes.
