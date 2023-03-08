/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:15:43 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/08 16:09:49 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "ircserv.hpp"
# include "client.hpp"
# include "channel.hpp"

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
    
};

