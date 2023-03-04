/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:23:00 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/03 12:10:28 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.hpp"

void Server::passCmd(std::vector<std::string> cmd, Client user, char *message)
{
	std::string pass;

	if (cmd.size() < 2)
		std::cerr <<"ERR_NEEDMOREPARAMS\n";
	else
	{
		pass = message;
		pass.erase(0, 5);
		pass.erase(pass.size() -1, 1);
		if (strcmp(pass.c_str(), _password.c_str()))
			std::cerr <<"ERR_PASSWDMISMATCH\n";
		else if (user.passStatus())
			std::cerr <<"ERR_ALREADYREGISTRED,\n";
		else
			user.setPassStatus(true);
	}
}

void Server::nickCmd(std::vector<std::string> cmd, Client user, char *message)
{
	std::string nick;
	int i = 0;

	if (cmd.size() < 2)
		std::cerr <<"ERR_NONICKNAMEGIVEN\n";
	while(i < client.size())
	{
		if (strcmp (client[i].getNick().c_str() , nick.c_str()) == 0)
		std::cerr <<"ERR_NICKNAMEINUSE\n";
		
	}
}

void Server::userMsg(std::vector<std::string> cmd, Client user, char *message)
{

}