/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelOpera.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 08:21:29 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/16 09:39:54 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

void Server::ft_partCmd(Client &client, std::vector<std::string> cmds)
{
    if (cmds.size() == 1)
        ft_print_error("PART", ERR_NEEDMOREPARAMS, client);
    else
    {
        std::vector<std::string> chanls;
        chanls = ft_split(cmds[1], ',');
        for (size_t l = 0; l < chanls.size(); l++)
        {
            int indx = is_channel_Exit(_channels, chanls[l]);
            if (indx == -1)
                ft_print_error(chanls[l], ERR_NOSUCHCHANNEL, client);
            else
            {
                int indexUser = _channels[indx].is_userInChannel(client);
                if (indexUser == -1)
                    ft_print_error(chanls[l], ERR_NOTONCHANNEL, client);
                else
                    _channels[indx].eraseUser(indexUser);
            }
        }
    }
};

void Server::ft_inviteCmd(Client &client, std::vector<std::string> cmds)
{
    if (cmds.size() < 4)
        ft_print_error("INVITE", ERR_NEEDMOREPARAMS, client);
    else
    {
        int index = is_channel_Exit(_channels, cmds[2]);
        if (index == -1)
            ft_print_error(cmds[2], ERR_NOSUCHCHANNEL, client);
        // else
        // {
        //     if (_channels[indx].getModes().limit && _channels[indx].getLimit() == (int)_channels[indx].get_chanlUsers().size())
        //         ft_print_error(_channels[indx].get_chanlName(), ERR_CHANNELISFULL, client);
        //     else if (_channels[indx].is_userInChannel(client) == -1)
        //     {
        //         if (_channels[indx].get_chanlPass().empty() || _channels[indx].get_chanlPass() == key)
        //             _channels[indx].add_user(client);
        //         else
        //             ft_print_error(_channels[indx].get_chanlName(), ERR_BADCHANNELKEY, client);
        //     }
        // }
    }
};