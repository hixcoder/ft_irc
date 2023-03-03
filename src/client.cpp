/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:57:00 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/03 15:44:36 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

Client::Client(int fd)
{
    _fd = fd;
    _is_auth = 0;
    _pass = 0;

    _nickName = "";
    _userName = "";
    _hostName = "127.0.0.1";
    _serverName = "";
    _realName = ""; 
}

Client::~Client() 
{
    
}

void Client::setAuth(int auth) {_is_auth = auth;}

void Client::setPass(bool pass){_pass = pass;}
void Client::setNickName(std::string nickName){_nickName = nickName;}
void Client::setUserName(std::string userName){_userName = userName;}
void Client::setHostName(std::string hostName){_hostName = hostName;}
void Client::setServerName(std::string serverName){_serverName = serverName;}
void Client::setRealName(std::string realName){_realName = realName;}


int Client::getFd() const {return _fd;}
int Client::getAuth() const {return _is_auth;}

bool Client::getPass()const{return _pass;}
std::string Client::getNickName()const{return _nickName;}
std::string Client::getUserName()const{return _userName;}
std::string Client::getHostName()const{return _hostName;}
std::string Client::getServerName()const{return _serverName;}
std::string Client::getRealName()const{return _realName;}

