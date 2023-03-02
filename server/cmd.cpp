/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:40:39 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/02 15:45:49 by lahammam         ###   ########.fr       */
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

int ft_is_userexist(std::string nik, std::vector<User> urs)
{
    for (size_t j = 0; j < urs.size(); j++)
    {
        if (strcmp(nik.c_str(), urs[j].get_nickname().c_str()) == 0)
            return (j);
    }
    return (0);
};
void Server::ft_privmsg_cmd(int i, std::vector<std::string> cmds, char *buffer)
{
    if (cmds.size() == 1)
        ft_print_error(cmds[0], ERR_NORECIPIENT, users[i]);
    else if (cmds.size() == 2)
        ft_print_error("", ERR_NOTEXTTOSEND, users[i]);
    else
    {
        std::vector<std::string> clts = ft_split(cmds[1], ',');
        for (size_t k = 0; k < clts.size(); k++)
        {
            int fd = ft_is_userexist(clts[k], users);
            if (fd) // ft_isregister(users[i])
            {
                std::string msg;
                if (cmds[2][0] != ':')
                    msg = ":" + users[i].get_nickname() + " PRIVMSG " + users[fd].get_nickname() + " :" + cmds[2] + "\n";
                else
                    msg = ":" + users[i].get_nickname() + " PRIVMSG " + users[fd].get_nickname() + " " + strchr(buffer, ':');
                send(users[fd].get_fdClient(), msg.c_str(), strlen(msg.c_str()), 0);
            }
            else
                ft_print_error(cmds[k], ERR_NOSUCHNICK, users[i]);
        }
    }
};
