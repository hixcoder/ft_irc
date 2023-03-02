/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:36:25 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/02 10:36:52 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_irc.hpp"

void ft_print_error(std::string cmd, int type, User user)
{
    std::string temp = ":punch.wa.us.dal.net " + std::to_string(type) + " ";
    if (type == ERR_NEEDMOREPARAMS)
    {
        std::string msg = temp + cmd + " :Not enough parameters\n";
        send(user.get_fdClient(), msg.c_str(), strlen(msg.c_str()), 0);
    }
    else if (type == ERR_PASSWDMISMATCH)
    {
        std::string msg = temp + cmd + " :Password incorrect\n";
        send(user.get_fdClient(), msg.c_str(), strlen(msg.c_str()), 0);
    }
    else if (type == ERR_ALREADYREGISTRED)
    {
        std::string msg = temp + ":You may not reregister\n";
        send(user.get_fdClient(), msg.c_str(), strlen(msg.c_str()), 0);
    }

    else if (type == ERR_NONICKNAMEGIVEN)
    {
        std::string msg = temp + cmd + ":No nickname given\n";
        send(user.get_fdClient(), msg.c_str(), strlen(msg.c_str()), 0);
    }
    else if (type == ERR_ERRONEUSNICKNAME)
    {
        std::string msg = temp + cmd + " :Erroneus nickname\n";
        send(user.get_fdClient(), msg.c_str(), strlen(msg.c_str()), 0);
    }
    else if (type == ERR_NICKNAMEINUSE)
    {
        std::string msg = temp + cmd + " :Nickname is already in use\n";
        send(user.get_fdClient(), msg.c_str(), strlen(msg.c_str()), 0);
    }
}