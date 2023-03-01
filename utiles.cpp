/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:23:01 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/01 09:31:17 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::vector<std::string> ft_split(std::string str, char separator)
{
    std::vector<std::string> result;
    int i = 0;
    std::string s;
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            if (str[i - 1] != separator)
                result.push_back(s);
            return (result);
        }
        if (str[i] != separator)
            s += str[i];
        else
        {
            result.push_back(s);
            s.clear();
        }
        i++;
    }
    return (result);
}

void ft_print_error(std::string cmd, int type, User user)
{
    // :punch.wa.us.dal.net 461  USER :Not enough parameters
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
}