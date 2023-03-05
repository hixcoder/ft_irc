/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:40:39 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/05 11:42:14 by ahammam          ###   ########.fr       */
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

//               ERR_BANNEDFROMCHAN
// ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
// ERR_CHANNELISFULL               ERR_BADCHANMASK
//                 ERR_TOOMANYCHANNELS
// RPL_TOPIC

bool is_validChannel(std::string name)
{
    if (name.length() < 2 || name.length() > 50)
        return false;
    if (name[0] != '#' && name[0] != '&')
        return false;
    for (size_t i = 1; i < name.length(); i++)
    {
        if (!isalnum(name[i]) && name[i] != '[' && name[i] != ']' && name[i] != '\\' &&
            name[i] != '`' && name[i] != '^' && name[i] != '_' && name[i] != '-')
        {
            return false;
        }
    }
    return true;
}

int is_channel_Exit(std::vector<Channel> chnls, std::string name)
{
    for (size_t i = 0; i < chnls.size(); i++)
    {
        if (std::strcmp(name.c_str(), chnls[i].get_chanlName().c_str()) == 0)
            return (i);
    }
    return (-1);
}

void Server::ft_joinCmd(int i, std::vector<std::string> cmds, char *buffer)
{
    if (cmds.size() == 1)
        ft_printError("JOIN", ERR_NEEDMOREPARAMS, _users[i]);
    else if (!is_validChannel(cmds[1]))
        ft_printError("JOIN", ERR_NOSUCHCHANNEL, _users[i]);
    else
    {
        int indx = is_channel_Exit(_channels, cmds[1]);
        if (indx == -1)
        {
            Channel channel;
            channel.set_chanlName(cmds[1]);
            channel.add_user(_users[i]);
            _channels.push_back(channel);
        }
        else
        {
            if (!_channels[indx].is_userInChannel(_users[i]))
                _channels[indx].add_user(_users[i]);
        }

        // std::vector<std::string> chanls;
        // std::vector<std::string> chanlsPass;
        // chanls = ft_split(cmds[1], ',');
        // if (!cmds[2].empty())
        //     chanlsPass = ft_split(cmds[2], ',');
        // for (size_t k = 0; k < chanls.size(); k++)
        // {
        //     // std::cout << "------> " << chanls[k] << std::endl;
        //     // if (!chanlsPass.empty() && k < chanlsPass.size())
        //     //     std::cout << "-> " << chanlsPass[k] << std::endl;
        // }
        _channels[indx].printAllUser();
    }
    buffer++;
};
