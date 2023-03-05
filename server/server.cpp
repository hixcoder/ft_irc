/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:02:51 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/05 09:14:30 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server()
{
    int opt = 1;
    _password = "1111";

    _mainsocked = socket(AF_INET, SOCK_STREAM, 0);
    if (_mainsocked < 0)
        error("Error building socket", 1, _mainsocked);

    if (setsockopt(_mainsocked, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        error("Error on setsockopt.", 1, _mainsocked);

    if (fcntl(_mainsocked, F_SETFL, O_NONBLOCK) == -1)
        error("Error on fcntl", 1, _mainsocked);

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(_mainsocked, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        error("Error on binding host adress.", 1, _mainsocked);

    if (listen(_mainsocked, 5) < 0)
        error("Error on binding host adress.", 1, _mainsocked);

    pollfd mainPollfd = {_mainsocked, POLLIN, 0};
    _pollfds.push_back(mainPollfd);

    User tmp;
    tmp.set_fdClient(0);
    _users.push_back(tmp);
};

void Server::addGuest()
{
    int new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    if ((new_socket = accept(_mainsocked, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    pollfd addSocket = {new_socket, POLLIN, 0};
    _pollfds.push_back(addSocket);

    User new_gst;
    new_gst.set_fdClient(new_socket);
    _users.push_back(new_gst);
};

void Server::ft_hundleCmd(int i, char *buffer)
{
    std::vector<std::string> spl = ft_split(buffer, ' ');
    if (strcmp("PASS", spl[0].c_str()) == 0)
        Server::ft_passCmd(i, spl, buffer);
    else if (strcmp("USER", spl[0].c_str()) == 0)
        Server::ft_userCmd(i, spl, buffer);
    else if (strcmp("NICK", spl[0].c_str()) == 0)
        Server::ft_nickCmd(i, spl);
    else if (strcmp("PRIVMSG", spl[0].c_str()) == 0)
        Server::ft_privmsgCmd(i, spl, buffer);
    else if (strcmp("JOIN", spl[0].c_str()) == 0)
        Server::ft_joinCmd(i, spl, buffer);
};
void Server::recv_msg(int i)
{
    char buffer[1024] = {0};
    int valread;
    if ((valread = recv(_pollfds[i].fd, buffer, 1024, 0)) == 0)
    {
        close(_pollfds[i].fd);
        _pollfds.erase(_pollfds.begin() + i);
    }
    else
        ft_hundleCmd(i, buffer);
};

void Server::startServer()
{
    while (1)
    {
        int ready_sockets = poll(_pollfds.data(), _pollfds.size(), 100000);
        if (ready_sockets < 0)
        {
            perror("poll failed");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < _pollfds.size(); i++)
        {
            if (_pollfds[i].revents != 0)
            {
                if (_pollfds[i].fd == _mainsocked)
                    Server::addGuest();
                else
                    Server::recv_msg(i);
            }
        }
    }
};

Server::~Server()
{
    close(_mainsocked);
};
