/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:15:43 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/12 12:55:45 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ircserv.hpp"
#include "client.hpp"
#include "channel.hpp"
#include <sys/time.h>

#define GREEN "\e[1;32m"
#define RED "\e[1;31m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[1;34m"
#define MAGENTA "\e[1;35m"
#define CYAN "\e[1;36m"
#define RESET "\e[0m"

class Server
{
private:
    int _serverSocket, _newSocket, _port;
    int _rc, _closeCon, _endServer, _timeout;
    const char *_passwd;
    struct sockaddr_in _server_addr;
    std::vector<pollfd> _pollfds;
    std::vector<Client> _clients;
    std::vector<Channel> _channels;
    std::string _serverName;

public:
    Server(char *port, char *passwd);
    ~Server();

    void runServer();

private:
    void createSocket();
    void bindSocket();
    void listeningToClients(int backlog);
    void error(std::string errorMsg, int exitStatus, int fd);
    void clean();

    void addClient();
    void recvClientMsg(Client &client);

    void ft_hundle_cmd(Client &client, char *buffer);
    // auth functions
    void handlePassCmd(Client &client, std::vector<std::string> cmds, char *buffer);
    void handleNickCmd(Client &client, std::vector<std::string> cmds);
    void handleUserCmd(Client &client, std::vector<std::string> cmds, char *buffer);
    // other functions
    void handleQuitCmd(Client &client);
    void handleOperCmd(Client &client, std::vector<std::string> cmds);
    void modeCmd(std::vector<std::string> cmd, Client &user);
    void ft_joinCmd(Client &client, std::vector<std::string> cmds, char *buffer);
    void handlePrivmsgCmd(Client &client, std::vector<std::string> cmds, char *buffer);
    void handleKillCmd(Client &client, std::vector<std::string> cmds);
    void handleListCmd(Client &client, std::vector<std::string> cmds);
    void handleNamesCmd(Client &client, std::vector<std::string> cmds);
    void handleTopicCmd(Client &client, std::vector<std::string> cmds);
    void handleVersionCmd(Client &client, std::vector<std::string> cmds);
    void handleHelpCmd(Client &client);
    void handleTimeCmd(Client &client);
    void handleLusersCmd(Client &client);
    void handlechanlModeCmd(Client &client, std::vector<std::string> cmds, int index);
    int is_chanel(std::string name);

    void handleLogTime(Client &client);
};
