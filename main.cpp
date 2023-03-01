/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:20:38 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/01 19:46:59 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

// int main()
// {
// 	int severSock;
// 	int opt = 1;
// 	int conectSock;
// 	char recvBuff[1024];
// 	struct sockaddr_in serverAddr;
// 	int check;
// 	int pollCheck;

// 	// create a socket
// 	if ((severSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0)
// 	{
// 		perror("Server socket failed");
// 		exit(1);
// 	}

// 	// Bind the socket to an ip adress and port
// 	if (setsockopt(severSock, SOL_SOCKET, SO_REUSEADDR,
// 				   &opt, sizeof(opt)))
// 	{
// 		perror("error in setsockopt");
// 		exit(EXIT_FAILURE);
// 	}
// 	int end = 0;
// 	memset(&serverAddr, 0, sizeof(serverAddr));
// 	int adrlen = sizeof(serverAddr);
// 	serverAddr.sin_family = AF_INET;
// 	// htons() converts the unsigned short integer hostshort from host byte order to network byte order.
// 	serverAddr.sin_port = htons(1111);
// 	// inet_addr() converts the Internet host address cp from IPv4 numbers-and-dots notation into binary data in network byte order.
// 	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
// 	if (bind(severSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
// 	{
// 		perror("bind failed");
// 		exit(1);
// 	}

// 	// listen for incoming connections
// 	if (listen(severSock, 3) < 0)
// 	{
// 		perror("listen failed");
// 		exit(1);
// 	}
// 	// Accept incoming connections from clients
// 	std::cout << "Connection accepted" << std::endl;
// 	int numfds = 4;
// 	struct pollfd fds[numfds];
// 	memset(fds, 0, sizeof(fds));
// 	fds[0].fd = severSock;
// 	fds[0].events = POLLIN;
// 	int nfds = 1;

// 	while(1)
// 	{
// 		std::cout << "Waiting for data" << std::endl;
// 		pollCheck = poll(fds, nfds, 0);
// 		if (pollCheck < 0)
// 		{
// 			perror("poll failed");
// 			break;
// 		}
// 		// if (pollCheck == 0)
// 		// {
// 		// 	perror("poll timeout");
// 		// 	break;
// 		// }
// 		int currentSize = nfds;
// 		for (int i = 0; i < currentSize; i++)
// 		{
// 			if (fds[i].revents == 0)
// 				continue;
// 			if (fds[i].revents != POLLIN)
// 			{
// 				perror("poll failed || client desconected");
// 				exit(1);
// 			}
// 			if (fds[i].fd == severSock)
// 			{
// 				while(1)
// 				{

// 					conectSock = accept(severSock, (struct sockaddr *)&serverAddr, (socklen_t *)&adrlen);
					
// 					if (conectSock < 0)
// 					{
// 						perror("accept failed");
// 						end = 1;
// 						exit(1);
// 					}
// 					fds[nfds].fd = conectSock;
// 					fds[nfds].events = POLLIN;
// 					fds[nfds].revents = 0;
// 					nfds++;
// 				}
// 			}
// 			else
// 			{
// 				// Receive data from the client
// 				do
// 				{

// 					memset(recvBuff, 0, sizeof(recvBuff));
// 					check = recv(fds[i].fd, recvBuff, sizeof(recvBuff), 0);
// 					if (check < 0)
// 					{
// 						perror("recv failed");
// 						exit(1);
// 					}
// 					if (check == 0)
// 					{
// 						std::cout << "Client disconnected" << std::endl;
// 						break;
// 						//	cozznectSock = accept(severSock, (struct sockaddr*) &serverAddr, (socklen_t*) &adrlen);
// 					}
// 					else if (check > 0)
// 						std::cout << recvBuff;
// 				}
// 				while (1);
// 			}
// 		}
// 	}
// 		// Send data to the client

// 	// close the connected socket
// 	close(conectSock);

// 	// close the listening socket
// 	close(severSock);
// 	return 0;
// }


int main()
{
	Server Server(1111);
	Server.createSocket();
	Server.bindSocket();
	Server.listenSocket();
	Server.pollSocket();
}