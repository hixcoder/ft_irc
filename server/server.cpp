/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:02:51 by lahammam          #+#    #+#             */
/*   Updated: 2023/02/27 19:41:23 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server()
{
    // int opt = 1;
    mainsocked = socket(AF_INET, SOCK_STREAM, 0);
    password = "1111";
    // setsockopt(sock, SOL_SOCKET,
    //            SO_REUSEADDR | SO_REUSEPORT, &opt,
    //            sizeof(opt));

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(mainsocked, (struct sockaddr *)&server_address, sizeof(server_address));

    listen(mainsocked, 5);

    pollfd mainPollfd = {mainsocked, POLLIN, 0};
    pollfds.push_back(mainPollfd);
    connected.push_back(0);
};

void Server::add_guest()
{
    int new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    if ((new_socket = accept(mainsocked, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    pollfd addSocket = {new_socket, POLLIN, 0};
    pollfds.push_back(addSocket);
    connected.push_back(0);
};

void Server::recv_msg(int i)
{
    char buffer[1024] = {0};
    int valread;
    if ((valread = recv(pollfds[i].fd, buffer, 1024, 0)) == 0)
    {
        close(pollfds[i].fd);
        pollfds.erase(pollfds.begin() + i);
    }
    else
    {
        if (connected[i] == 0)
        {
            // char *ptr;
            std::vector<std::string> spl = ft_split(buffer, ' ');

            if (spl.size() != 2)
                std::cout << "Error command" << std::endl;
            else
            {
                if (strcmp("PASS", spl[0].c_str()) == 0)
                    std::cout << spl[1] << std::endl;
            }
        }
        else
        {
            std::cout << "Received: " << buffer << std::endl;
        }
        // send(pollfds[i].fd, buffer, strlen(buffer), 0);
    }
};

void Server::handle_events()
{
    while (1)
    {
        int ready_sockets = poll(pollfds.data(), pollfds.size(), 100000);
        if (ready_sockets < 0)
        {
            perror("poll failed");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < pollfds.size(); i++)
        {
            if (pollfds[i].revents != 0)
            {
                if (pollfds[i].fd == mainsocked)
                    Server::add_guest();
                else
                    Server::recv_msg(i);
            }
        }
    }
};

Server::~Server()
{
    close(mainsocked);
};
