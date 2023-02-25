/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:34:17 by lahammam          #+#    #+#             */
/*   Updated: 2023/02/25 14:37:27 by lahammam         ###   ########.fr       */
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


int main()
{
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cout << "Failed to create socket\n";
        return 1;
    }
    // char *
    struct sockaddr_in server_address;
    // memset(&server_address, 0, sizeof(server_address)); // zero out the address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(1234); // set the port number
    server_address.sin_addr.s_addr = inet_addr("1.0.0.1");


    bind(sock, (struct sockaddr*)&server_address, sizeof(server_address)); 
    std::cout << "Server socket bound to address " << 
    inet_ntoa(server_address.sin_addr) << " on port " << ntohs(server_address.sin_port) << std::endl;

    listen(sock, 5);

    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    int newsockfd = accept(sock, (struct sockaddr *) &cli_addr, &clilen);

    char buffer[1024] = { 0 };
    char* hello = "Hello from server";

    int valread;
   valread = read(newsockfd, buffer, 1024);

    printf("%s\n", buffer);
    send(newsockfd, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    close(sock);
}