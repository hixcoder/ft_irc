/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:00:54 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/02 19:00:55 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/ircserv.hpp"

std::vector<std::string> ft_split(std::string str, char separator)
{
    std::vector<std::string> result;
    size_t i = 0;
    std::string s;
    while (i < str.size())
    {
        if (str[i] == separator || str[i] == '\n')
        {
            if (!s.empty())
            {
                result.push_back(s);
                s.clear();
            }
            if (str[i] == '\n')
                break;
        }
        else
            s += str[i];
        i++;
    }
    if (!s.empty())
        result.push_back(s);
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

bool ft_isalreadyused(std::string nick, Client &client, std::vector<Client> clients)
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i].getFd() != client.getFd() && strcmp(clients[i].getNickName().c_str(), nick.c_str()) == 0)
            return (1);
    }
    return (0);
}

bool ft_isregister(Client client)
{
    if (client.getPass() && client.getNickName().size() && client.getUserName().size())
        return 1;
    return 0;
}

bool ft_nosuchnick(std::string nick, std::vector<Client> clients)
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (ft_isregister(clients[i]) && strcmp(nick.c_str(), clients[i].getNickName().c_str()) == 0)
            return (1);
    }
    return (0);
}