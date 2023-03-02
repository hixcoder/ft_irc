/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:40:39 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/02 16:01:19 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
// :punch.wa.us.dal.net 411 ALLL :No recipient given (PRIVMSG)
// :punch.wa.us.dal.net 412 ALLL :No text to send
// :punch.wa.us.dal.net 401 ALLL N/C :No such nick/channel

//     ERR_CANNOTSENDTOCHAN ERR_NOTOPLEVEL
//         ERR_WILDTOPLEVEL ERR_TOOMANYTARGETS
//
//                 RPL_AWAY

int ft_isUserExist(std::string nik, std::vector<User> urs)
{
    for (size_t j = 0; j < urs.size(); j++)
    {
        if (strcmp(nik.c_str(), urs[j].get_nickname().c_str()) == 0)
            return (j);
    }
    return (0);
};
void Server::ft_privmsgCmd(int i, std::vector<std::string> cmds, char *buffer)
{
    if (cmds.size() == 1)
        ft_printError(cmds[0], ERR_NORECIPIENT, _users[i]);
    else if (cmds.size() == 2)
        ft_printError("", ERR_NOTEXTTOSEND, _users[i]);
    else
    {
        std::vector<std::string> clts = ft_split(cmds[1], ',');
        for (size_t k = 0; k < clts.size(); k++)
        {
            int fd = ft_isUserExist(clts[k], _users);
            if (fd) // ft_isRegister(users[i])
            {
                std::string msg;
                if (cmds[2][0] != ':')
                    msg = ":" + _users[i].get_nickname() + " PRIVMSG " + _users[fd].get_nickname() + " :" + cmds[2] + "\n";
                else
                    msg = ":" + _users[i].get_nickname() + " PRIVMSG " + _users[fd].get_nickname() + " " + strchr(buffer, ':');
                send(_users[fd].get_fdClient(), msg.c_str(), strlen(msg.c_str()), 0);
            }
            else
                ft_printError(cmds[k], ERR_NOSUCHNICK, _users[i]);
        }
    }
};
