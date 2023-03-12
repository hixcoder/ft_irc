/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:17:54 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/12 09:18:02 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

Server::Server(char *port, char *passwd)
{
    _passwd = passwd;
    _port = atoi(port);
    _timeout = 0;
    _endServer = 0;
    _closeCon = 0;
    _serverName = "irc_killers";
  
  
    createSocket();
    bindSocket();
    listeningToClients(4);

    pollfd servSocket = {_serverSocket, POLLIN, 0};
    _pollfds.push_back(servSocket);
}

Server::~Server()
{
}

void Server::createSocket()
{
    //  create server socket and initialize it
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket < 0)
        error("Error building socket", 1, _serverSocket);

    bzero((char *)&_server_addr, sizeof(_server_addr));

    _server_addr.sin_addr.s_addr = inet_addr(LOCAL_IP);
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(_port);
}

void Server::bindSocket()
{
    // here we allow the server socket fd to be reusable
    int optval = 1;
    if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
        error("Error on setsockopt.", 1, _serverSocket);

    // here we set the server socket to be nonbloking
    if (fcntl(_serverSocket, F_SETFL, O_NONBLOCK) == -1)
        error("Error on fcntl", 1, _serverSocket);

    // bind the server host address
    if (bind(_serverSocket, (struct sockaddr *)&_server_addr, sizeof(_server_addr)) < 0)
        error("Error on binding host adress.", 1, _serverSocket);
}

void Server::listeningToClients(int backlog)
{
    // listening for the clients (wait for incoming connection from the client)
    if (listen(_serverSocket, backlog) < 0)
        error("Error on binding host adress.", 1, _serverSocket);
}

// establish connections and start communication
void Server::runServer()
{
    do
    {
        if (poll(&_pollfds[0], _pollfds.size(), 0) < 0)
        {
            std::cout << "poll() call failed!\n";
            break;
        }

        // determine the readable fds
        for (size_t i = 0; i < _pollfds.size(); i++)
        {
            if (_pollfds[i].revents == 0)
                continue;
            if (_pollfds[i].revents != POLLIN)
            {
                std::cout << "client " << _pollfds[i].fd << " disconnected\n";
                std::cout << "client send " << _pollfds[i].revents << " revent\n";
                close(_pollfds[i].fd);
                _pollfds.erase(_pollfds.begin() + i);
                _clients.erase(_clients.begin() + i - 1);
                break;
            }

            if (_pollfds[i].fd == _serverSocket)
                addClient();
            else
                recvClientMsg(_clients[i - 1]);

            if (_closeCon)
            {
                close(_pollfds[i].fd);
                _pollfds.erase(_pollfds.begin() + i);
                _clients.erase(_clients.begin() + i - 1);
                _closeCon = 0;
            }
        }
    } while (_endServer == 0);
    clean();
}

void Server::addClient()
{
    // here we loop and accept incoming connections
    while (true)
    {
        _newSocket = accept(_serverSocket, NULL, NULL);
        if (_newSocket < 0)
        {
            if (errno != EWOULDBLOCK)
            {
                std::cout << "accept() failed\n";
                _endServer = 1;
            }
            break;
        }
        // add the new incoming connection to _pollfds
        std::cout << "New incoming connection: " << _newSocket << "\n";
        pollfd cliSocket = {_newSocket, POLLIN, 0};
        _pollfds.push_back(cliSocket);
        // add client
        Client newclient(cliSocket.fd);
        _clients.push_back(newclient);
    }
}

void Server::recvClientMsg(Client &client)
{
    // if recv function fails with EWOULDBLOCK
    char buffer[1024];
    bzero(&buffer, sizeof(buffer));
    _rc = recv(client.getFd(), buffer, sizeof(buffer), 0);
    if (_rc < 0)
    {
        if (errno != EWOULDBLOCK)
        {
            std::cout << "recv() failed\n";
            _closeCon = 1;
        }
    }
    else if (_rc == 0)
    {
        // if connection closed by client
        std::cout << "Connection closed\n";
        _closeCon = 1;
    }
    else
        ft_hundle_cmd(client, buffer);
}

// this function for handle sockets errors
void Server::error(std::string errorMsg, int exitStatus, int fd)
{
    std::cout << errorMsg << "\n";
    if (fd != -2)
        close(fd);
    exit(exitStatus);
}

// clean up all the sockets that are open
void Server::clean()
{
    for (size_t i = 0; i < _pollfds.size(); i++)
    {
        if (_pollfds[i].fd > 0)
            close(_pollfds[i].fd);
    }
}
