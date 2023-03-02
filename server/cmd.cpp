/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:40:39 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/02 13:48:58 by lahammam         ###   ########.fr       */
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

void Server::ft_privmsg_cmd(int i, std::vector<std::string> cmds)
{
    if (cmds.size() == 1)
        ft_print_error(cmds[0], ERR_NORECIPIENT, users[i]);
    else if (cmds.size() == 2)
        ft_print_error("", ERR_NOTEXTTOSEND, users[i]);
    // else if (ft_isregister(users[i]))
    //     ft_print_error(cmds[1], ERR_NOSUCHNICK, users[i]);
    else
    {
        std::cout << "-----> " << cmds[1] << std::endl;
        std::vector<std::string> clts = ft_split(cmds[1], ',');
        for (size_t k = 0; k < clts.size(); k++)
        {
            std::cout << clts[k] << std::endl;
        }

        size_t j = 0;
        for (; j < users.size(); j++)
        {

            if (strcmp(cmds[1].c_str(), users[j].get_nickname().c_str()) == 0)
            {
                // :LKK!~WERWE@d2a6-9017-cfb7-6374-1329.iam.net.ma PRIVMSG HAMZ :FA:FAS:
                std::string msg = ":" + users[i].get_nickname() + " PRIVMSG " + users[j].get_nickname() + " " + cmds[2];
                send(users[j].get_fdClient(), msg.c_str(), strlen(msg.c_str()), 0);
                break;
            }
        }
        if (j == users.size())
            ft_print_error(cmds[1], ERR_NOSUCHNICK, users[i]);
    }
};
// PRIVMSG USER1,USER2, MESSAGE