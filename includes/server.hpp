/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:15:43 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/17 11:40:51 by hboumahd         ###   ########.fr       */
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
    std::vector<std::string> _listCmds;
    std::string _serverName;

public:
    Server(int port, char *passwd);
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
    void handlePrivmsgCmd(Client &client, std::vector<std::string> cmds, char *buffer);
    void handleNoticeCmd(Client &client, std::vector<std::string> cmds, char *buffer);
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

    int is_userExist(std::string nk);
    // channel operator
    void ft_joinCmd(Client &client, std::vector<std::string> cmds);
    void ft_partCmd(Client &client, std::vector<std::string> cmds);
    void ft_inviteCmd(Client &client, std::vector<std::string> cmds);
    void ft_kickCmd(Client &client, std::vector<std::string> cmds, char *buffer);

    // bonus part
    void handleLogTime(Client &client);
    void sendFile(Client &client, std::vector<std::string> cmds);
    void recvFile(Client &client, std::vector<std::string> cmds);
    bool isCmdExit(std::string cmd);
    bool isNickUserDuplicate(std::string nickUser);
    void ft_updateNickInChanls(Client clt);
    void eraseUserFromChannels(Client clt);
};
