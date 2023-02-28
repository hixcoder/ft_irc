/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:15:43 by hboumahd          #+#    #+#             */
/*   Updated: 2023/02/28 12:31:30 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "ircserv.hpp"

class server
{
private:
    int _serverSocket, _newSocket, _port;
    int _rc, _closeCon, _endServer, _timeout;
    char *_passwd;
    struct sockaddr_in _server_addr;
    std::vector<pollfd> _pollfds;
    
public:
    server(char *port, char *passwd);
    ~server();

    void createSocket();
    void bindSocket();
    void listeningToClients(int backlog);
    void error(std::string errorMsg, int exitStatus, int fd);
    
    void runServer();
    void addClient();
    void recvClientMsg(pollfd arPollfd);
};

