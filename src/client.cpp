/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:31:18 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/05 11:34:43 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.hpp"

void Client::setNick(std::string value)
{
	_nick = value;
	_pass = false;
}

void Client::setFd(int value)
{
	_fd = value;
}

std::string Client::getNick()
{
	return (_nick);
}

int Client::getFd()
{
	return (_fd);
}
void Client::setPassStatus(bool status)
{
		_pass = status;
}
bool Client::passStatus()
{
	return (_pass);
}
void Client::setModes(char mode, bool status)
{
	if (mode == 'a')
		_modes.away = status;
	else if (mode == 'i')
		_modes.invisible = status;
	else if (mode == 'w')
		_modes.wallops = status;
	else if (mode == 'r' && status == true)
		_modes.restricted = status;
	else if (mode == 'o' && status == false)
		_modes.operator_ = status;
	else if (mode == 'O' && status == false)
		_modes.localOperator = status;
	else if (mode == 's')
		_modes.receiveServerNotices = status;
}
bool Client::isRegistered()
{
	if (_pass == true && _nick != "" && _username != "")
		return (true);
	return (false);
}

std::string Client::getModes(char mode)
{
	std::string modes = "";
	if (mode == 'a')
		modes += _modes.away ? "a" : "";
	else if (mode == 'i')
		modes += _modes.invisible ? "i" : "";
	else if (mode == 'w')
		modes += _modes.wallops ? "w" : "";
	else if (mode == 'r')
		modes += _modes.restricted ? "r" : "";
	else if (mode == 'o')
		modes += _modes.operator_ ? "o" : "";
	else if (mode == 'O')
		modes += _modes.localOperator ? "O" : "";
	else if (mode == 's')
		modes += _modes.receiveServerNotices ? "s" : "";
	return (modes);
}

git commit -m "add mode and fix some bugs"