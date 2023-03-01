/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:23:01 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/01 12:03:26 by lahammam         ###   ########.fr       */
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

// It must start with a letter (a-z or A-Z) or a special character ([, \, ], ^, _, or {).
// It must contain only letters, numbers, or special characters.
// It must not contain spaces or other whitespace characters.
// It must not start or end with a special character.
// It must be between 1 and 9 characters long (inclusive).

bool ft_isvalid_nickname(std::string nick)
{
    int i = 0;
    std::string s = "[]\\^_-|~{}";
    if (nick.size() > 9)
        return (0);
    if (std::isalpha(nick[i]) == 0 && s.find(nick[i]) == std::string::npos)
        return (0);
    for (size_t i = 0; i < nick.size(); i++)
    {
        if (std::isalpha(nick[i]) == 0 && s.find(nick[i]) == std::string::npos && std::isdigit(nick[i]) == 0)
            return 0;
    }
    if (i != 0 && s.find(nick[i - 1]) == std::string::npos)
        return (0);
    return (1);
};

bool ft_isalreadyused(std::string nick, size_t j, std::vector<User> users)
{
    for (size_t i = 0; i < users.size(); i++)
    {
        if (i != j && users[i].get_nickname() == nick)
            return (1);
    }
    return (0);
}

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