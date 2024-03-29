/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:57:00 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/18 12:38:36 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

Client::Client(int fd)
{
	_fd = fd;
	_is_auth = 0;
	_pass = false;

	_nickName = "";
	_userName = "";
	_hostName = "127.0.0.1";
	_serverName = "";
	_realName = "";

	// user modes:
	_modes.away = false;
	_modes.invisible = false;
	_modes.wallops = false;
	_modes.restricted = false;
	_modes.operator_ = false;
	_modes.localOperator = false;
	_modes.receiveServerNotices = false;
	_startTime = get_time();
	_buff = "";
	_msgTemp = "";
}

Client::~Client()
{
}

// client's functions
bool Client::isRegistered()
{
	if (_pass == true && _nickName != "" && _userName != "")
		return (true);
	return (false);
}

int Client::isUserFinishRegistered()
{
	if (_pass == false)
		return 1;
	if (_nickName == "")
		return 2;
	if (_userName == "")
		return 3;
	return 0;
};
bool Client::operator==(Client &other) const
{
	if (std::strcmp(_nickName.c_str(), other.getNickName().c_str()) == 0)
		return 1;
	return 0;
};

// seters and getters
void Client::loginMessage()
{
	_is_auth++;
	if (_is_auth == 3)
	{
		// 		NICK adaDa
		// user dahsk * * *
		// :IRC-1337 001 adaDa :Welcome to the Internet Relay Network adaDa!dahsk@127.0.0.1
		// :IRC-1337 002 adaDa :Your host is IRC-1337 running on version 1.0
		// :IRC-1337 003 adaDa :This server was created Sat Mar 18 12:31:27 2023
		std::string msg;
		msg = ":IRC-1337 001 " + this->_nickName + " :Welcome to the Internet Relay Network " + this->_nickName + "!" + this->_userName + "@127.0.0.1\n" + ":IRC-1337 002 " + this->_nickName + " :Your host is IRC-1337 running onc version 1.0\n" + ":IRC-1337 003 " + this->_nickName + " :This server was created Sat Mar 18 12:31:27 2023\n";
		send(this->_fd, msg.c_str(), strlen(msg.c_str()), 0);
	}
}
void Client::setPass(bool pass) { _pass = pass; }
void Client::setNickName(std::string nickName) { _nickName = nickName; }
void Client::setUserName(std::string userName) { _userName = userName; }
void Client::setHostName(std::string hostName) { _hostName = hostName; }
void Client::setServerName(std::string serverName) { _serverName = serverName; }
void Client::setRealName(std::string realName) { _realName = realName; }
void Client::setMsgTemp(std::string msg) { _msgTemp = msg; };
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

void Client::setOper(bool status) { _modes.operator_ = status; }
void Client::setBuff(std::string buffer) { _buff = buffer; }
void Client::setClientAddr(struct sockaddr_in client_addr) { _client_addr = client_addr; };
int Client::getFd() const { return _fd; }
long Client::getStartTime() const { return _startTime; }
int Client::getAuth() const { return _is_auth; }
bool Client::getPass() const { return _pass; }
std::string Client::getNickName() const { return _nickName; }
std::string Client::getUserName() const { return _userName; }
std::string Client::getHostName() const { return _hostName; }
std::string Client::getServerName() const { return _serverName; }
std::string Client::getRealName() const { return _realName; }
std::string Client::getMsgTemp() const { return _msgTemp; };

bool Client::getModes(char mode)
{
	bool modes = false;
	if (mode == 'a')
		modes = _modes.away;
	else if (mode == 'i')
		modes = _modes.invisible;
	else if (mode == 'w')
		modes = _modes.wallops;
	else if (mode == 'r')
		modes = _modes.restricted;
	else if (mode == 'o')
		modes = _modes.operator_;
	else if (mode == 'O')
		modes = _modes.localOperator;
	else if (mode == 's')
		modes = _modes.receiveServerNotices;
	return (modes);
}

std::string Client::getBuff() const { return _buff; };
struct sockaddr_in Client::getClientAddr() const { return _client_addr; };
void Client::addBuff(std::string buffer) { _buff += buffer; }
