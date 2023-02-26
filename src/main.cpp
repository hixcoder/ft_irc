/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:46:07 by hboumahd          #+#    #+#             */
/*   Updated: 2023/02/26 19:51:18 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

void doProcessing(int clientSockFd)
{
    int n;
    char buffer[1024];

    // receives client message 
    bzero(&buffer, sizeof(buffer));
    n = recv(clientSockFd, buffer, sizeof(buffer), 0);
    if (n < 0)
        fun_error("Error receiving from client socket", 1);

    std::cout << "client: " << buffer;
    
    // send message to client
    // char msg[] = "hello client!\n";
    // n = send(clientSockFd, msg, sizeof(msg), 0);
    // if (n < 0)
    //     fun_error("Error sending to client socket", 1);
}

int main(int ac, char **av)
{
    if (ac == 3)
    {
        int serverSockFd, clientSockFd, portno;
        struct sockaddr_in server_addr, client_addr;
        int pid;
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
        if (listen(serverSockFd, 2) < 0)
            fun_error("Error on binding host adress.", 1);
        
        while (1)
        {
            // accept actual connection from the client
            clientlen = sizeof(client_addr);
            clientSockFd = accept(serverSockFd, (struct sockaddr *) &client_addr, &clientlen);
            if (clientSockFd < 0)
                fun_error("Error accepting connection with the client.", 1);
            
            // create child process for each connection
            pid = fork();
            if (pid < 0)
                fun_error("Error: fork faild to create a child process", 1);
            if (pid == 0)
            {
                close(serverSockFd);
                while (1)
                {
                    doProcessing(clientSockFd);
                }
                exit(0);
            }
            else
                close(clientSockFd);
        }
    }
    else
        std::cout << "=> please enter: ./ircserv: <port> <password>\n";
    return 0;
}