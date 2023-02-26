/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:46:07 by hboumahd          #+#    #+#             */
/*   Updated: 2023/02/26 19:14:22 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"


int main(int ac, char **av)
{
    if (ac == 3)
    {
        int serverSockFd, clientSockFd, portno;
        char buffer[1024];
        struct sockaddr_in server_addr, client_addr;
        int n;
        socklen_t clientlen;
        

        //  create server socket and initialize it
        serverSockFd = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSockFd < 0)
            fun_error("Error building socket", 1);
        
        bzero((char *) &server_addr, sizeof(server_addr));
        portno = atoi(av[1]);
        
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(portno);


        // bind the server host address
        if (bind(serverSockFd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
            fun_error("Error on binding host adress.", 1);
        

        // listening for the clients (wait for incoming connection from the client)
        if (listen(serverSockFd, 5) < 0)
            fun_error("Error on binding host adress.", 1);
        

        // accept actual connection from the client
        clientlen = sizeof(client_addr);
        clientSockFd = accept(serverSockFd, (struct sockaddr *) &client_addr, &clientlen);
        if (clientSockFd < 0)
            fun_error("Error accepting connection with the client.", 1);
        
        // start communicating if the connection is established
        // receives client message 
        bzero(&buffer, sizeof(buffer));
        n = recv(clientSockFd, buffer, sizeof(buffer), 0);
        if (n < 0)
            fun_error("Error reading from client socket", 1);

        std::cout << "client message: " << buffer << "\n";
        
        // send message to client
        char msg[] = "hello client!\n";
        n = send(clientSockFd, msg, sizeof(msg), 0);
        if (n < 0)
            fun_error("Error writting to client socket", 1);

        close(clientSockFd);
        close(serverSockFd);
        
        
    }
    else
        std::cout << "=> please enter: ./ircserv: <port> <password>\n";
    return 0;
}