/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:57:00 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/06 16:04:23 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

Client::Client(int fd)
{
    _fd = fd;
    _is_auth = 0;
    _pass = false;
    _isOper = false;

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

bool Client::operator==(Client &other) const
{
    if (std::strcmp(_nickName.c_str(), other.getNickName().c_str()) == 0)
        return 1;
    return 0;
};


// seters and getters
void Client::setAuth(int auth) {_is_auth = auth;}
void Client::setPass(bool pass){_pass = pass;}
void Client::setNickName(std::string nickName){_nickName = nickName;}
void Client::setUserName(std::string userName){_userName = userName;}
void Client::setHostName(std::string hostName){_hostName = hostName;}
void Client::setServerName(std::string serverName){_serverName = serverName;}
void Client::setRealName(std::string realName){_realName = realName;}
void Client::setModes(char mode, bool status)
{
	if (mode == 'a')
		_modes.away = status;
	else if (mode == 'i')
		_modes.invisible = status;
	else if (mode == 'w')
		_modes.wallops = status;
	else if (mode == 'r')
		_modes.restricted = status;
	else if (mode == 'o')
		_modes.operator_ = status;
	else if (mode == 'O')
		_modes.localOperator = status;
	else if (mode == 's')
		_modes.receiveServerNotices = status;
}

int Client::getFd() const {return _fd;}
int Client::getAuth() const {return _is_auth;}
bool Client::getPass()const{return _pass;}
std::string Client::getNickName()const{return _nickName;}
std::string Client::getUserName()const{return _userName;}
std::string Client::getHostName()const{return _hostName;}
std::string Client::getServerName()const{return _serverName;}
std::string Client::getRealName()const{return _realName;}
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
