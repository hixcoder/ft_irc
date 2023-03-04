/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:51:49 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/03 11:53:41 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP
#include "client.hpp"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
// class Client;
class Server
{
	std::vector<pollfd> _fds;
	std::vector<Client> client;
	std::string _password;
	int _serverSock;
	int _conectSock;
	int _port;
	struct  sockaddr_in serverAddr;
	int _end;
public:
	Server(int port, std::string pass);
	~Server();
	void createSocket();
	void bindSocket();
	void listenSocket();
	void pollSocket();
	void acceptSocket();
	void recvMessage(Client user);
	void closeSocket();
	int connectionRegistration(char *message, Client user);
	void passCmd(std::vector<std::string> cmd, Client user, char *message);
	void nickCmd(std::vector<std::string> cmd, Client user, char *message);
	void userMsg(std::vector<std::string> cmd, Client user, char *message);
};

void exitPerror( const char *message);
#endif