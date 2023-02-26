/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:58:52 by lahammam          #+#    #+#             */
/*   Updated: 2023/02/26 14:45:30 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#define PORT 8080

int main()
{
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		perror(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}
	if ((status = connect(client_fd, (struct sockaddr *)&serv_addr,
						  sizeof(serv_addr))) < 0)
	{
		perror("\nConnection Failed: ");
		return -1;
	}

	std::string input;
	while (std::getline(std::cin, input))
	{
		if (send(client_fd, input.c_str(), input.length(), 0) < 0)
		{
			std::cerr << "Error sending message\n";
			break;
		};
		// valread = read(client_fd, buffer, 1024);
		// printf("%s\n", buffer);
	}
	close(client_fd);
	return 0;
}
