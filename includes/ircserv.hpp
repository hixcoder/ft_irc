/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:46:10 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/16 10:23:10 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <errno.h>

#include "server.hpp"
#include "client.hpp"
#include "channel.hpp"

#define LOCAL_IP "127.0.0.1" // server ip

// irc error numbers:
#define ERR_NEEDMOREPARAMS 461
#define ERR_PASSWDMISMATCH 464
#define ERR_ALREADYREGISTRED 462
#define ERR_NONICKNAMEGIVEN 431
#define ERR_ERRONEUSNICKNAME 432
#define ERR_NICKNAMEINUSE 433
#define ERR_NORECIPIENT 411
#define ERR_NOTEXTTOSEND 412
#define ERR_NOSUCHNICK 401
#define ERR_UNKNOWNCOMMAND 421
#define RPL_YOUREOPER 381
#define ERR_NOOPERHOST 491
#define ERR_NOSUCHCHANNEL 403
#define ERR_NOPRIVILEGES 481
#define ERR_CANTKILLSERVER 483
#define RPL_LISTSTART 321
#define RPL_LIST 322
#define RPL_LISTEND 323
#define ERR_NOSUCHSERVER 402
#define ERR_NOTREGISTERED 451
#define ERR_USERSDONTMATCH 502
#define ERR_UMODEUNKNOWNFLAG 501
#define RPL_UMODEIS 221
#define ERR_BADCHANNELKEY 475
#define ERR_NOTONCHANNEL 442
#define RPL_NAMREPLY 353
#define RPL_ENDOFNAMES 366
#define ERR_KEYSET 467
#define ERR_CHANNELISFULL 471

#define ERR_NOTONCHANNEL 442     // "<channel> :You're not on that channel"
#define RPL_NOTOPIC 331          // "<channel> :No topic is set"
#define ERR_CHANOPRIVSNEEDED 482 // "<channel> :You're not channel operator"
#define RPL_TOPIC 332            // "<channel> :<topic>"

#define RPL_VERSION 351
#define RPL_TIME 391

// OUR
#define JOIN_CHANNEL 55

// used functions:

std::vector<std::string> ft_split(std::string str, char separator);
void ft_print_error(std::string cmd, int type, Client client);
bool ft_isvalid_nickname(std::string nick);
bool ft_isalreadyused(std::string nick, Client &client, std::vector<Client> clients);
bool ft_isregister(Client client);
bool ft_nosuchnick(std::string nick, std::vector<Client> clients);
bool validMode(std::string mode);
bool is_validChannel(std::string name);
int is_channel_Exit(std::vector<Channel> chnls, std::string name);
int ft_isUserExist(std::string nik, std::vector<Client> urs);
int ft_isChannelExist(std::string nik, std::vector<Channel> chnl);
long get_time(void);
bool ftCheckCRLF(std::string buff);
std::vector<std::string> splitString(std::string str, std::string delimiter);
