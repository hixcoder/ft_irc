/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:00:48 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/15 11:31:45 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ircserv.hpp"

void ft_print_error(std::string cmd, int type, Client client)
{
    std::string temp = ":@localhost  " + std::to_string(type) + " ";
    std::string msg;
    if (type == ERR_NEEDMOREPARAMS)
        msg = temp + client.getNickName() + " " + cmd + " :Not enough parameters\n";
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
    else if (type == ERR_NOSUCHCHANNEL)
        msg = temp + client.getNickName() + " " + cmd + " :No such channel\n";
    else if (type == ERR_BADCHANNELKEY)
        msg = temp + client.getNickName() + " " + cmd + " :Cannot join channel (+k)\n";
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
    else if (type == RPL_LISTSTART)
        msg = temp + client.getNickName() + " Channel :Users  Name\n";
    else if (type == RPL_LISTEND)
        msg = temp + client.getNickName() + " :End of /LIST\n";
    else if (type == ERR_NOTREGISTERED)
        msg = temp + cmd + " :You have not registered\n";
    else if (type == ERR_USERSDONTMATCH)
        msg = temp + cmd + " :Cannot change mode for other users\n";
    else if (type == ERR_UMODEUNKNOWNFLAG)
        msg = temp + cmd + " :Unknown MODE flag\n";
    else if (type == RPL_ENDOFNAMES)
        msg = temp + client.getNickName() + cmd + " :End of /NAMES list\n";
    else if (type == ERR_NOTONCHANNEL)
        msg = temp + cmd + " :You're not on that channel\n";
    else if (type == RPL_NOTOPIC)
        msg = temp + client.getNickName() + " " + cmd + " :No topic is set\n";
    else if (type == ERR_CHANOPRIVSNEEDED)
        msg = temp + client.getNickName() + cmd + " :You're not channel operator\n";
    else if (type == RPL_VERSION)
        msg = temp + client.getNickName() + " VERSION" + " :V1.0.0,release mode," + cmd + ". [this is the first release version of ft_irc]\n";
    else if (type == ERR_NOSUCHSERVER)
        msg = temp + client.getNickName() + " VERSION" + " :No such server\n";
    else if (type == ERR_KEYSET)
        msg = temp + client.getNickName() + " " + cmd + " :Channel key already set\n";
    else if (type == ERR_CHANNELISFULL)
        msg = temp + " " + cmd + " :Cannot join channel (+l)\n";
    send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}