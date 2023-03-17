/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileTransfer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:49:46 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/17 16:57:58 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

#include "../includes/ircserv.hpp"

void Server::sendFile(Client &client, std::vector<std::string> cmds)
{
	if (!client.isRegistered())
		return (ft_print_error("DOWNLOAD", ERR_NOTREGISTERED, client));
	if (cmds.size() < 2)
		return (ft_print_error("DOWNLOAD", ERR_NEEDMOREPARAMS, client));
	std::string msg;
	char buffer[1024];
	std::string file;
	FILE *fd = fopen(cmds[1].c_str(), "rb");
	while (!feof(fd))
	{
		int size = fread(&buffer, 1, 1024, fd);
		if (size < 0)
			break;
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
			return;
		}
		int opt = 1;
		if (setsockopt(send_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
		{
			std::cout << "Error setting socket options" << std::endl;
			return;
		}
		struct sockaddr_in addr;
		int addrlen = sizeof(addr);
		memset(&addr, 0, addrlen);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(1000);
		addr.sin_addr.s_addr = INADDR_ANY;

		if (bind(send_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		{
			std::cout << "Error binding socket hire" << std::endl;
			return;
		}
		if (listen(send_fd, 1) < 0)
		{
			std::cout << "Error listening on socket" << std::endl;
			return;
		}
		int new_socket = accept(send_fd, (struct sockaddr *)&addr, (socklen_t *)&addrlen);
		if (new_socket < 0)
		{
			std::cout << "Error accepting connection" << std::endl;
			return;
		}
		send(new_socket, file.c_str(), file.size(), 0);
		close(new_socket);
		close(send_fd);
		exit(1);
	}
	msg = "PRIVMSG " + client.getNickName() + " :" + '\x01' + "DCC SEND " + cmds[1] + " 0 1000 " + std::to_string(file.size()) + '\x01';
	msg += "\r\n";
	send(client.getFd(), msg.c_str(), msg.size(), 0);
}