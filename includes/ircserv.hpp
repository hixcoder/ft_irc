/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:46:10 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/06 17:42:39 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <string>
# include <vector>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/poll.h>
# include <errno.h>

# include "server.hpp"
# include "client.hpp"
# include "channel.hpp"


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