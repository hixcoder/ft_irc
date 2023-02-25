/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:45:47 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/25 15:02:34 by alouzizi         ###   ########.fr       */
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

	//create a socket
	if((severSock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Server socket failed");
		exit(1);
	}

	//Bind the socket to an ip adress and port


	//listen for incoming connections


	//Accept incoming connections from clients

	//while(1)
	//{
		//Receive data from the client

		//Send data to the client
	//}
	
	//close the connected socket


	//close the listening socket

	return 0;
}