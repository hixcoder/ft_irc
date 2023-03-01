/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:51:49 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/01 19:42:01 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
class Server
{
	std::vector<pollfd> _fds;
	int _serverSock;
	int _conectSock;
	int _port;
	int _password;
	struct  sockaddr_in serverAddr;
public:
	Server(int port);
	~Server();
	void createSocket();
	void bindSocket();
	void listenSocket();
	void pollSocket();
	void acceptSocket();
	void recvMessage(int fd);
	void closeSocket();
};

void exitPerror(char *message);
#endif