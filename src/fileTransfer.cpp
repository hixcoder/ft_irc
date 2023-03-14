/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileTransfer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:49:46 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/14 12:09:17 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"
# include <thread>
#include <fstream>

void Server::sendFile(Client &client, std::vector<std::string> cmds)
{
	std::string msg;
	char buffer[1024];
	std::string file;
	std::cout <<  cmds[1] <<"]\n" << std::endl;
	FILE *fd = fopen(cmds[1].c_str(), "rb");
	while(!feof(fd))
	{
		int size = fread(&buffer, 1, 1024, fd);
		if (size < 0)
			break ;
		//send(client.getFd(), buffer, size, 0);
		file.append(buffer, size);
	}
	fclose(fd);
	int i = fork();
	if (!i)
	{
		int send_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (send_fd < 0)
		{
			std::cout << "Error creating socket" << std::endl;
			return ;
		}
		int opt = 1;
		if (setsockopt(send_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
		{
			std::cout << "Error setting socket options" << std::endl;
			return ;
		}
		struct sockaddr_in addr;
		int addrlen = sizeof(addr);
		memset(&addr, 0, addrlen);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(7777);
		addr.sin_addr.s_addr = INADDR_ANY;
		
		if(bind(send_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		{
			std::cout << "Error binding socket" << std::endl;
			return ;
		}
		if (listen(send_fd, 1) < 0)
		{
			std::cout << "Error listening on socket" << std::endl;
			return ;
		}
		// std::cout << client.getNickName() << std::endl;
		int new_socket = accept(send_fd, (struct sockaddr *)&addr, (socklen_t*)&addrlen);
		if (new_socket < 0)
		{
			std::cout << "Error accepting connection" << std::endl;
			return ;
		}
		std::cout << "Sending file\n" << std::endl;
		send(new_socket, file.c_str(), file.size(), 0);
		close(new_socket);
		close(send_fd);
		exit(0);
	}
	std::cout << "check \n" << std::endl;
	// std::cout << "Sending file\n" << std::endl;
	msg = "PRIVMSG " + client.getNickName() +  " :" + '\x01' + "DCC SEND " + cmds[1] + " 0 7777 " + std::to_string(file.size()) + '\x01';
	msg += "\r\n";
	send(client.getFd(), msg.c_str(), msg.size(), 0);
}

// void Server::recvFile(Client &client, std::vector<std::string> cmds)
// {
	
// }