/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:23:01 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/02 12:25:48 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_irc.hpp"

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
        if (i != j && strcmp(users[i].get_nickname().c_str(), nick.c_str()) == 0)
            return (1);
    }
    return (0);
}

bool ft_isregister(User user)
{
    if (user.get_pass() && user.get_nickname().size() && user.get_username().size())
        return 1;
    return 0;
}

bool ft_nosuchnick(std::string nick, std::vector<User> users)
{
    for (size_t i = 0; i < users.size(); i++)
    {
        if (ft_isregister(users[i]) && strcmp(nick.c_str(), users[i].get_nickname().c_str()) == 0)
            return (1);
    }
    return (0);
}