/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:00:54 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/09 13:46:03 by ahammam          ###   ########.fr       */
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

bool validMode(std::string mode)
{
    if (mode.length() != 2 && (mode[0] != '+' && mode[0] != '-'))
        return (false);
    if (mode[1] == 'i' || mode[1] == 'w' || mode[1] == 's' || mode[1] == 'o' || mode[1] == 'O' || mode[1] == 'r' || mode[1] == 'a')
        return (true);
    return (false);
}

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

int ft_isUserExist(std::string nik, std::vector<Client> urs)
{
    for (size_t j = 0; j < urs.size(); j++)
    {
        if (strcmp(nik.c_str(), urs[j].getNickName().c_str()) == 0)
            return (j);
    }
    return (-1);
};

int ft_isChannelExist(std::string nik, std::vector<Channel> chnl)
{
    for (size_t j = 0; j < chnl.size(); j++)
    {
        if (strcmp(nik.c_str(), chnl[j].get_chanlName().c_str()) == 0)
            return (j);
    }
    return (-1);
};