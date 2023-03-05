/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_auth.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:10:25 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/05 08:39:41 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::ft_passCmd(int i, std::vector<std::string> cmds, char *buffer)
{
    std::string pass = "";

    if (cmds.size() == 1)
        ft_printError("PASS", ERR_NEEDMOREPARAMS, _users[i]);
    else
    {
        pass = strchr(buffer, ' ');
        pass.erase(0, 1);
        pass.erase(pass.size() - 1, 1);
        if (strcmp(pass.c_str(), _password.c_str()))
            ft_printError("PASS", ERR_PASSWDMISMATCH, _users[i]);
        else if (_users[i].get_pass())
            ft_printError("PASS", ERR_ALREADYREGISTRED, _users[i]);
        else
            _users[i].set_pass(1);
    }
};

void Server::ft_nickCmd(int i, std::vector<std::string> cmds)
{
    if (cmds.size() == 1)
        ft_printError("", ERR_NONICKNAMEGIVEN, _users[i]);
    else if (ft_isNicknameValide(cmds[1]) == 0)
        ft_printError(cmds[1], ERR_ERRONEUSNICKNAME, _users[i]);
    else if (!ft_isRegister(_users[i]) && ft_isAlreadyUsed(cmds[1], i, _users) == 1)
        ft_printError(cmds[1], ERR_NICKNAMEINUSE, _users[i]);
    else if (ft_isAlreadyUsed(cmds[1], i, _users) == 1)
        ft_printError(cmds[1], ERR_NICKCOLLISION, _users[i]);
    else
    {
        //: nick1!~PPP@d2a6-9017-cfb7-6374-1329.iam.net.ma NICK :nick2
        if (ft_isRegister(_users[i]))
        {
            std::string msg = "::punch.wa.us.dal.net NICK :" + cmds[1] + "\n";
            send(_users[i].get_fdClient(), msg.c_str(), strlen(msg.c_str()), 0);
        }

        _users[i].set_nickname(cmds[1]);
    }
};

void Server::ft_userCmd(int i, std::vector<std::string> cmds)
{

    if (cmds.size() < 5)
        ft_printError("USER", ERR_NEEDMOREPARAMS, _users[i]);
    else if (!_users[i].get_username().empty())
        ft_printError("USER", ERR_ALREADYREGISTRED, _users[i]);
    else
    {
        _users[i].set_username(cmds[1]);
        _users[i].set_hostname(cmds[2]);
        _users[i].set_servername(cmds[3]);
        _users[i].set_realname(cmds[4]);
    }
};
