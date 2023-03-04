/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:45:47 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/03 11:50:28 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.hpp"

Server::Server(int port, std::string pass)
{
	_port = port;
	_end =  1;
	_password = pass;
}

Server::~Server()
{
	
}

void Server::createSocket()
{
	//create a socket
	_serverSock = socket(AF_INET, SOCK_STREAM , IPPROTO_TCP);
	if(_serverSock  == 0)
		exitPerror("Server socket failed");
}

void Server::bindSocket()
{
	int opt;

	opt = 1;
	//Bind the socket to an ip adress and port
	if  (setsockopt(_serverSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
		exitPerror("Error in setsockopt");
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(_port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(_serverSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
		exitPerror("Bind failed");
}

void Server::listenSocket()
{
	// listen for incoming connections
	if (listen(_serverSock, 3) < 0)
		exitPerror("Listen failed");
}

void Server::pollSocket()
{
	int pollcheck;
	pollfd fds = {_serverSock, POLLIN, 0};
	_fds.push_back(fds);
			int k =0;
	while (_end)
	{
		pollcheck = poll(_fds.data(), _fds.size(), -1);
		if (pollcheck < 0)
		{
			std::cerr << "Poll failed\n";
			break;
		}
		for (int i = 0; i < _fds.size(); i++)
		{
			if (_fds[i].revents == 0)
				continue;
			if (_fds[i].revents != POLLIN)
			{
				std::cout << "\033[1;31;04mClient disconnected\033[0m" << std::endl;
				close(_fds[i].fd);
				_fds.erase(_fds.begin() + i);
				client.erase(client.begin() + i - 1);
				break;
			}
			if (_fds[i].fd == _serverSock)
				acceptSocket();
			else
				recvMessage(client[i - 1]);
		}
	}
}

void Server::acceptSocket()
{
	int addrlen = sizeof(serverAddr);
	int conectSock;

	conectSock = accept(_serverSock, NULL, NULL);
	if (conectSock < 0)
		exitPerror("accept failed");
	std::cout << "\033[1;33;04mNew connection accepted\033[0m" << std::endl;
	pollfd addSocket ={conectSock, POLLIN, 0};
	Client user;
	user.setFd(conectSock);
	_fds.push_back(addSocket);
	client.push_back(user);
}

void Server::recvMessage(Client user)
{
	char recvBuff[1024];
	int check;

	memset(recvBuff, 0, sizeof(recvBuff));
	check = recv(user.getFd(), recvBuff , sizeof(recvBuff), 0);
	if (check == 0)
	{
		std::cout << "Client disconnected" << std::endl;
		return ;
	}
	else if(check > 0)
	{
		connectionRegistration(recvBuff, user);
		// user
		// if (strcmp(recvBuff, "Pass"))
		// {
			
		// 	std::cout << recvBuff;
		// }
	}
}

void Server::closeSocket()
{
	int i = 0;
	while(i < _fds.size())
	{	if (i < client.size() && client[i].getFd() > 0)
			close(client[i].getFd());
		if (_fds[i].fd > 0)
			close(_fds[i].fd);
		i++;
	}
}