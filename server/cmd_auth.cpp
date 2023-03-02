/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:10:25 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/02 10:24:58 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::ft_pass_cmd(int i, std::vector<std::string> cmds, char *buffer)
{
    std::string pass = "";

    if (cmds.size() == 1)
        ft_print_error("PASS", ERR_NEEDMOREPARAMS, users[i]);
    else
    {
        pass = strchr(buffer, ' ');
        pass.erase(0, 1);
        pass.erase(pass.size() - 1, 1);
        if (strcmp(pass.c_str(), password.c_str()))
            ft_print_error("PASS", ERR_PASSWDMISMATCH, users[i]);
        else if (users[i].get_pass())
            ft_print_error("PASS", ERR_ALREADYREGISTRED, users[i]);
        else
            users[i].set_pass(1);
    }
};

void Server::ft_nick_cmd(int i, std::vector<std::string> cmds)
{
    if (cmds.size() == 1)
        ft_print_error(users[i].get_nickname(), ERR_NONICKNAMEGIVEN, users[i]);
    else if (ft_isvalid_nickname(cmds[1]) == 0)
        ft_print_error(cmds[1], ERR_ERRONEUSNICKNAME, users[i]);
    else if (ft_isalreadyused(cmds[1], 1, users) == 1)
        ft_print_error(cmds[1], ERR_NICKNAMEINUSE, users[i]);
    else
    {
        //: nick1!~PPP@d2a6-9017-cfb7-6374-1329.iam.net.ma NICK :nick2
        if (ft_isregister(users[i]))
        {
            std::string msg = "::punch.wa.us.dal.net NICK : " + cmds[1] + "\n";
            send(users[i].get_fdClient(), msg.c_str(), strlen(msg.c_str()), 0);
        }

        users[i].set_nickname(cmds[1]);
    }
};

void Server::ft_user_cmd(int i, std::vector<std::string> cmds)
{

    if (cmds.size() < 5)
        ft_print_error("USER", ERR_NEEDMOREPARAMS, users[i]);
    else
    {
        users[i].set_username(cmds[1]);
        users[i].set_hostname(cmds[2]);
        users[i].set_servername(cmds[3]);
        users[i].set_realname(cmds[4]);
    }
};
