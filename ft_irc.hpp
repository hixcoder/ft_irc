/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:06:33 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/01 10:03:59 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
#define FT_IRC_HPP

#define ERR_NEEDMOREPARAMS 461
#define ERR_PASSWDMISMATCH 464
#define ERR_ALREADYREGISTRED 462

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

#include "user/user.hpp"
class User;
std::vector<std::string> ft_split(std::string str, char separator);
void ft_print_error(std::string cmd, int type, User user);

#endif