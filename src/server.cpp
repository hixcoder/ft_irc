/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:17:54 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/18 16:09:48 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

Server::Server(int port, char *passwd)
{
    _passwd = passwd;
    _port = port;
    _timeout = 0;
    _endServer = 0;
    _closeCon = 0;
    _serverName = ":IRC-1337 ";
    createSocket();
    bindSocket();
    listeningToClients(4);

    pollfd servSocket = {_serverSocket, POLLIN, 0};
    _pollfds.push_back(servSocket);

    _listCmds.push_back("pass");
    _listCmds.push_back("user");
    _listCmds.push_back("nick");
    _listCmds.push_back("privmsg");
    _listCmds.push_back("notice");
    _listCmds.push_back("quit");
    _listCmds.push_back("oper");
    _listCmds.push_back("join");
    _listCmds.push_back("part");
    _listCmds.push_back("mode");
    _listCmds.push_back("kill");
    _listCmds.push_back("list");
    _listCmds.push_back("names");
    _listCmds.push_back("invite");
    _listCmds.push_back("kick");
    _listCmds.push_back("topic");
    _listCmds.push_back("version");
    _listCmds.push_back("help");
    _listCmds.push_back("time");
    _listCmds.push_back("luser");
    _listCmds.push_back("download");
    _listCmds.push_back("pong");
    _listCmds.push_back("/logtime");
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

    _server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");;
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
    std::cout << _server_addr.sin_addr.s_addr;
    if (bind(_serverSocket, (struct sockaddr *)&_server_addr, sizeof(_server_addr)) < 0)
        error("Error on binding host adress. .", 1, _serverSocket);
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
        if (poll(&_pollfds[0], _pollfds.size(), -1) < 0)
        {
            std::cout << "poll() call failed!\n";
            break;
        }

        for (size_t i = 0; i < _pollfds.size(); i++)
        {
            if (_pollfds[i].revents == 0)
                continue;
            if (_pollfds[i].revents != POLLIN && i != 0)
            {
                std::cout << "client " << _pollfds[i].fd << " disconnected\n";
                close(_pollfds[i].fd);
                _pollfds.erase(_pollfds.begin() + i);
                eraseUserFromChannels(_clients[i - 1]);
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
                eraseUserFromChannels(_clients[i - 1]);
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
        struct sockaddr_in clt_addr;
        bzero((char *)&clt_addr, sizeof(clt_addr));
        int addrlen = sizeof(clt_addr);
        _newSocket = accept(_serverSocket, (struct sockaddr *)&clt_addr, (socklen_t *)&addrlen);
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
        newclient.setClientAddr(clt_addr);
        _clients.push_back(newclient);
        // :punch.wa.us.dal.net NOTICE AUTH :*** Looking up your hostname...
        std::string welcomeMsg;
        // :IRC-1337 NOTICE AUTH :*** Looking up your hostname...
        // :IRC-1337 NOTICE AUTH :*** Found your hostname
        welcomeMsg = ":" + this->_serverName + " NOTICE AUTH  :*** Looking up your hostname...\n";
        welcomeMsg = welcomeMsg + ":" + this->_serverName + " NOTICE AUTH  :*** Found your hostname\n";
        send(newclient.getFd(), welcomeMsg.c_str(), strlen(welcomeMsg.c_str()), 0);
    }
}

void Server::recvClientMsg(Client &client)
{
    // if recv function fails with EWOULDBLOCK
    char buffer[1024];
    bzero(&buffer, sizeof(buffer));
    _rc = recv(client.getFd(), buffer, sizeof(buffer), 0);
    client.addBuff(buffer);
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
    else if (ftCheckCRLF(client.getBuff()))
    {
        std::string tmp = client.getBuff();
        tmp.erase(tmp.length() - 2, 2);
        std::vector<std::string> spl = splitString(tmp, "\\r\\n");
        for (size_t i = 0; i < spl.size(); i++)
        {
            char *cmds = new char[spl[i].length() + 1];
            std::strcpy(cmds, spl[i].c_str());
            ft_hundle_cmd(client, cmds);
            delete[] cmds;
        }
        client.setBuff("");
    }
}

// this function for handle sockets errors
void Server::error(std::string errorMsg, int exitStatus, int fd)
{
    std::cout << errorMsg << "\n";
    if (fd != -2)
        close(fd);
    exit(exitStatus);
}

bool Server::isCmdExit(std::string cmd)
{
    for (size_t i = 0; i < _listCmds.size(); i++)
    {
        if (strcmp(cmd.c_str(), _listCmds[i].c_str()) == 0)
            return 1;
    }
    return 0;
};

void Server::ft_updateNickInChanls(Client clt)
{
    for (size_t i = 0; i < _channels.size(); i++)
    {
        for (size_t j = 0; j < _channels[i].get_chanlUsers().size(); j++)
        {
            if (clt.getFd() == _channels[i].get_chanlUsers()[j].getFd())
            {
                _channels[i].updateNickUser(i, clt.getNickName());
                if (_channels[i].ft_isOperator(clt))
                {
                    _channels[i].remove_Operator();
                    _channels[i].add_Operator(clt);
                }
            }
        }
    }
};

void Server::eraseUserFromChannels(Client clt)
{
    size_t i = 0;
    while (i < _channels.size())
    {
        for (size_t j = 0; j < _channels[i].get_chanlUsers().size(); j++)
        {
            if (clt.getFd() == _channels[i].get_chanlUsers()[j].getFd())
            {
                _channels[i].eraseUser(j);
                if (_channels[i].get_chanlUsers().size() > 0)
                {
                    if (clt.getFd() == _channels[i].getCreator())
                    {
                        _channels[i].remove_Operator();
                        _channels[i].add_Operator(_channels[i].get_chanlUsers()[0]);
                    }
                }
                else
                {
                    delete_Channel(i);
                    i--;
                    break;
                }
            }
        }
        i++;
    }
};

void Server::delete_Channel(int i)
{
    _channels.erase(_channels.begin() + i);
};
// clean up all the sockets that are open
void Server::clean()
{
    for (size_t i = 0; i < _pollfds.size(); i++)
    {
        if (_pollfds[i].fd > 0)
            close(_pollfds[i].fd);
    }
}

bool Server::isNickUserDuplicate(std::string nickUser)
{
    size_t i = 0;
    while (i < _clients.size())
    {
        if (!_clients[i].getUserName().empty())
        {
            if (strcmp(nickUser.c_str(), _clients[i].getUserName().c_str()) == 0)
                return 1;
        }
        i++;
    }
    return 0;
};