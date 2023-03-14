/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileTransfer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:49:46 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/13 16:29:56 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

#include <fstream>

void Server::sendFile(Client &client, std::vector<std::string> cmds)
{
	std::string msg;
	std::ifstream file(cmds[1], std::fstream::in);
	int bytesSent = 0;
	if (file.fail())
	{
		//ft_print_error("Error: file not found",
		msg = "Error: file not found";
		send(client.getFd(), msg.c_str(), msg.size(), 0);
		//client.sendReply(ERR_FILENOTFOUND, "File not found");
		return;
	}
	// file.seekg(0, ios::end);
	int fileSize = file.tellg();
	// file.seekg(0, ios::beg);

	int iResult = send(client.getFd(), (char*)&fileSize, sizeof(fileSize), 0);
	while (bytesSent < fileSize)
	{
		// int bytesToRead = min(fileSize - bytesSent, sizeof(buffer));
    //    int bytesToRead = min(fileSize - bytesSent, sizeof(buffer));
//        file.read(buffer, bytesToRead);
      //  iResult = send(client.getFd(), buffer, bytesToRead, 0);
        // if (iResult == SOCKET_ERROR) {
        //     cout << "send failed: " << WSAGetLastError() << endl;
        //     closesocket(client.getFd());
        //     WSACleanup();
        //     //return 1;
        // }
        bytesSent += iResult;
    }
	
}

// void Server::recvFile(Client &client, std::vector<std::string> cmds)
// {
	
// }