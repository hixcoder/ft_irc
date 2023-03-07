/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:00:48 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/07 16:18:53 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/ircserv.hpp"



void ft_print_error(std::string cmd, int type, Client client)
{
    std::string temp = "> " + (std::string)LOCAL_IP + " " + std::to_string(type) + " ";
    std::string msg;
    if (type == ERR_NEEDMOREPARAMS)
        msg = temp + cmd + " :Not enough parameters\n";
    else if (type == ERR_PASSWDMISMATCH)
        msg = temp + cmd + " :Password incorrect\n";
    else if (type == ERR_ALREADYREGISTRED)
        msg = temp + ":You may not reregister\n";
    else if (type == ERR_NONICKNAMEGIVEN)
        msg = temp + client.getNickName() + " :No nickname given\n";
    else if (type == ERR_ERRONEUSNICKNAME)
        msg = temp + cmd + " :Erroneus nickname\n";
    else if (type == ERR_NICKNAMEINUSE)
        msg = temp + cmd + " :Nickname is already in use\n";
    else if (type == ERR_NORECIPIENT)
        msg = temp + client.getNickName() + " :No recipient given (" + cmd + ")\n";
    else if (type == ERR_NOTEXTTOSEND)
        msg = temp + client.getNickName() + " :No text to send\n";
    else if (type == ERR_NOSUCHNICK)
        msg = temp + client.getNickName() + " " + cmd + " :No such nick/channel\n";
    else if (type == ERR_UNKNOWNCOMMAND)
        msg = temp + cmd + " :Unknown command\n";
    else if (type == RPL_YOUREOPER)
        msg = temp + cmd + " :You are now an IRC operator\n";
    else if (type == ERR_NOOPERHOST)
        msg = temp + cmd + " :No O-lines for your host\n";
    else if (type == ERR_NOPRIVILEGES)
        msg = temp + cmd + " :Permission Denied- You're not an IRC operator\n";
    else if (type == ERR_CANTKILLSERVER)
        msg = temp + cmd + " :You cant kill a server!\n";
    else if (type == ERR_NOTREGISTERED)
        msg = temp + cmd + " :You have not registered\n";
    else if (type == ERR_USERSDONTMATCH)
        msg = temp + cmd + " :Cannot change mode for other users\n";
    else if (type == ERR_UMODEUNKNOWNFLAG)
        msg = temp + cmd + " :Unknown MODE flag\n";

    send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}