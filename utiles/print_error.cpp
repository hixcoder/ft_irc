/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:36:25 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/05 08:40:31 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_irc.hpp"

void ft_printError(std::string cmd, int type, User user)
{
    std::string temp = ":punch.wa.us.dal.net " + std::to_string(type) + " ";
    std::string msg;
    if (type == ERR_NEEDMOREPARAMS)
        msg = temp + cmd + " :Not enough parameters\n";
    else if (type == ERR_PASSWDMISMATCH)
        msg = temp + cmd + " :Password incorrect\n";
    else if (type == ERR_ALREADYREGISTRED)
        msg = temp + ":You may not reregister\n";
    else if (type == ERR_NONICKNAMEGIVEN)
        msg = temp + user.get_nickname() + " :No nickname given\n";
    else if (type == ERR_ERRONEUSNICKNAME)
        msg = temp + cmd + " :Erroneus nickname\n";
    else if (type == ERR_NICKNAMEINUSE)
        msg = temp + cmd + " :Nickname is already in use\n";
    else if (type == ERR_NICKCOLLISION)
        msg = temp + cmd + " :Nickname collision KILL\n";
    else if (type == ERR_NORECIPIENT)
        msg = temp + user.get_nickname() + " :No recipient given (" + cmd + ")\n";
    else if (type == ERR_NOTEXTTOSEND)
        msg = temp + user.get_nickname() + " :No text to send\n";
    else if (type == ERR_NOSUCHNICK)
        msg = temp + user.get_nickname() + " " + cmd + " :No such nick/channel\n";
    send(user.get_fdClient(), msg.c_str(), strlen(msg.c_str()), 0);
}