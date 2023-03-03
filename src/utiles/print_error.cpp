/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:00:48 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/03 11:38:58 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/ircserv.hpp"

void ft_print_error(std::string cmd, int type, Client client)
{
    std::string temp = "> " + (std::string)SERVER_IP + " " + std::to_string(type) + " ";
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
    send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}