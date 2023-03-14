/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:00:54 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/14 12:05:14 by hboumahd         ###   ########.fr       */
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

int Server::is_chanel(std::string name)
{
    size_t i = 0;
    while (_channels.size() > i)
    {
        if (strcmp(_channels[i].get_chanlName().c_str(), name.c_str()) == 0)
            return (i);
        i++;
    }
    return (0);
}

int ft_isChannelExist(std::string nik, std::vector<Channel> chnl)
{
    for (size_t j = 0; j < chnl.size(); j++)
    {
        if (strcmp(nik.c_str(), chnl[j].get_chanlName().c_str()) == 0)
            return (j);
    }
    return (-1);
};

// January 1, 1970
long get_time(void)
{
    struct timeval tp;

    gettimeofday(&tp, NULL);
    return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

bool ftCheckCRLF(std::string buff)
{
    int len = buff.length();
    if (len >= 2 && buff[len - 2] == '\r' && buff[len - 1] == '\n')
        return true;
    else
        return false;
}

std::vector<std::string> splitString(std::string str, std::string delimiter)
{
    std::vector<std::string> result;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);
    return result;
}
