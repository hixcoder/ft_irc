/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:45:47 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/26 14:07:21 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	int severSock;
	int opt = 1;
	int conectSock;
	char recvBuff[1024];
	struct sockaddr_in serverAddr;
	int check;
	
	//create a socket
	if((severSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0)
	{
		perror("Server socket failed");
		exit(1);
	}

	//Bind the socket to an ip adress and port
	if (setsockopt(severSock, SOL_SOCKET, SO_REUSEADDR,
			&opt, sizeof(opt))) {
        perror("error in setsockopt");
        exit(EXIT_FAILURE);
    }
	memset(&serverAddr, 0, sizeof(serverAddr));
	int adrlen = sizeof(serverAddr);
	serverAddr.sin_family = AF_INET;
	//htons() converts the unsigned short integer hostshort from host byte order to network byte order.
	serverAddr.sin_port = htons(1111);
	//inet_addr() converts the Internet host address cp from IPv4 numbers-and-dots notation into binary data in network byte order.
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(severSock,(struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("bind failed");
		exit(1);
	}

	//listen for incoming connections
	if (listen(severSock, 3) < 0)
	{
		perror("listen failed");
		exit(1);
	}

	//Accept incoming connections from clients
	conectSock = accept(severSock, (struct sockaddr*) &serverAddr, (socklen_t*) &adrlen);
	if (conectSock < 0)
	{
		perror("accept failed");
		exit(1);
	}
	std::cout << "Connection accepted" << std::endl;
	while(1)
	{
		//Receive data from the client
		memset(recvBuff, 0, sizeof(recvBuff));
		check = recv(conectSock, recvBuff, sizeof(recvBuff), NULL);
		if (check < 0)
		{
			perror("recv failed");
			exit(1);
		}
		if (check == 0)
		{
			std::cout << "Client disconnected" << std::endl;
			conectSock = accept(severSock, (struct sockaddr*) &serverAddr, (socklen_t*) &adrlen);
		}
		else if (check > 0)
			std::cout << recvBuff;
		//Send data to the client
		
	}

	//close the connected socket
	close(conectSock);

	//close the listening socket
	close(severSock);
	return 0;
