/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:40:39 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/03 11:01:45 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

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

void Server::ft_joinCmd(int i, std::vector<std::string> cmds, char *buffer)
{
    if (cmds.size() == 1)
        ft_printError("JOIN", ERR_NEEDMOREPARAMS, _users[i]);
    else
    {

        std::vector<std::string> chanls;
        std::vector<std::string> chanlsPass;
        chanls = ft_split(cmds[1], ',');
        if (!cmds[2].empty())
            chanlsPass = ft_split(cmds[2], ',');
        for (size_t k = 0; k < chanls.size(); k++)
        {
            std::cout << "------> " << chanls[k] << std::endl;

            if (!chanlsPass.empty() && k < chanlsPass.size())
                std::cout << "-> " << chanlsPass[k] << std::endl;
        }
    }
    buffer++;
};
