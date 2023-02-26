/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:34:17 by lahammam          #+#    #+#             */
/*   Updated: 2023/02/26 14:28:26 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

int main()
{
    // int opt = 1;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // setsockopt(sock, SOL_SOCKET,
    //            SO_REUSEADDR | SO_REUSEPORT, &opt,
    //            sizeof(opt));

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sock, (struct sockaddr *)&server_address, sizeof(server_address));

    listen(sock, 5);

    // struct sockaddr_in client_addr;
    // memset(&client_addr, 0, sizeof(client_addr));
    // socklen_t client_addrlen = sizeof(client_addr);
    // int clientfd = accept(sock, (struct sockaddr *)&client_addr, &client_addrlen);
    // if (clientfd < 0)
    // {
    //     printf("Error accepting connection: %s\n", strerror(errno));
    //     close(sock);
    //     return -1;
    // }

    // char buffer[5] = {0};

    // char *hello = (char *)"Hello from server\n";
    // int valread;

    // while (true)
    // {
    //     valread = recv(clientfd, buffer, sizeof(buffer), MSG_WAITALL);
    //     if (valread < 0)
    //     {
    //         perror("Failed to receive data");
    //         exit(1);
    //     }
    //     if (valread == 0)
    //     {
    //         printf("Client disconnected\n");
    //         break;
    //     }
    //     printf("%s\n", buffer);
    //     send(clientfd, hello, strlen(hello), 0);
    //     printf("Response sent\n");
    // }

    int new_socket, valread, opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    struct pollfd pollfds[10];
    pollfds[0].fd = sock;
    pollfds[0].events = POLLIN;

    // Initialize the other sockets
    for (int i = 1; i < 10; i++)
    {
        pollfds[i].fd = -1;
    }

    while (1)
    {
        // Wait for any activity on any of the sockets
        int ready_sockets = poll(pollfds, 10, -1);
        printf("------\n");
        if (ready_sockets < 0)
        {
            perror("poll failed");
            exit(EXIT_FAILURE);
        }

        // Check each socket for activity
        for (int i = 0; i < 10; i++)
        {
            // Check if the socket has activity
            if (pollfds[i].revents != 0)
            {
                // If it's the server socket, accept a new connection

                if (pollfds[i].fd == sock)
                {
                    if ((new_socket = accept(sock, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
                    {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }

                    // Add the new socket to the pollfd structure
                    for (int j = 1; j < 10; j++)
                    {
                        if (pollfds[j].fd == -1)
                        {
                            pollfds[j].fd = new_socket;
                            pollfds[j].events = POLLIN;
                            break;
                        }
                    }
                }
                // If it's not the server socket, receive the data and echo it back
                else
                {
                    if ((valread = read(pollfds[i].fd, buffer, 1024)) == 0)
                    {
                        // Connection closed
                        close(pollfds[i].fd);
                        pollfds[i].fd = -1;
                    }
                    else
                    {
                        std::cout << "Received: " << buffer << std::endl;
                        send(pollfds[i].fd, buffer, strlen(buffer), 0);
                    }
                }
            }
        }
        printf("Polling...\n");
    }

    // close(clientfd);
    close(sock);
}