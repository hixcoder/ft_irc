/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:31:18 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/03 10:09:50 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.hpp"

void Client::setNick(std::string value)
{
	nick = value;
	_pass = false;
	
}

void Client::setFd(int value)
{
	fd = value;
}

std::string Client::getNick()
{
	return (nick);
}

int Client::getFd()
{
	return (fd);
}
void Client::setPassStatus(bool status)
{
		_pass = status;
}
bool Client::passStatus()
{
	return (_pass);
}