/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:06:33 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/05 08:40:06 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
#define FT_IRC_HPP

#define ERR_NEEDMOREPARAMS 461
#define ERR_PASSWDMISMATCH 464
#define ERR_ALREADYREGISTRED 462
#define ERR_NONICKNAMEGIVEN 431
#define ERR_ERRONEUSNICKNAME 432
#define ERR_NICKNAMEINUSE 433
#define ERR_NORECIPIENT 411
#define ERR_NOTEXTTOSEND 412
#define ERR_NOSUCHNICK 401
#define ERR_NICKCOLLISION 436

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
#include <fcntl.h>
#include <cctype>

#include "user/user.hpp"
class User;
#include "channel/channel.hpp"
class Channel;
std::vector<std::string> ft_split(std::string str, char separator);
void ft_printError(std::string cmd, int type, User user);
bool ft_isNicknameValide(std::string nick);
bool ft_isAlreadyUsed(std::string nick, size_t j, std::vector<User> users);
bool ft_isRegister(User user);
bool ft_noSuchNick(std::string nick, std::vector<User> users);
int ft_isUserExist(std::string nik, std::vector<User> urs);
void error(std::string errorMsg, int exitStatus, int fd);
#endif