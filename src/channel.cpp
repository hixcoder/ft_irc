/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:21:53 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/09 16:33:29 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

Channel::Channel()
{
    _chanlTopic = "";
};

Channel::~Channel(){};

// setters and getters
void Channel::set_chanlName(std::string name) { _chanlName = name; };
std::string Channel::get_chanlName() { return _chanlName; };

void Channel::set_chanlPass(std::string pass) { _chanlPass = pass; };
std::string Channel::get_chanlPass() const { return _chanlPass; };

void Channel::setChannelTopic(std::string newTopic) { _chanlTopic = newTopic; }
std::string Channel::getChannelTopic() const { return _chanlTopic; }

// other functions
int Channel::getClientsNbr() { return _chanlUsers.size(); }

std::string Channel::getallUsers(std::string &existedUsers, std::vector<Client> serverClients)
{
    updateChanlUsers(serverClients);
    std::string users = "";
    for (size_t i = 0; i < _chanlUsers.size(); i++)
    {
        size_t pos = existedUsers.find(_chanlUsers[i].getNickName());
        if (pos == std::string::npos)
        {
            if (_chanlUsers[i].getModes('o') || _chanlUsers[i].getModes('O'))
                users += " @" + _chanlUsers[i].getNickName();
            else
                users += " " + _chanlUsers[i].getNickName();
        }
        // else
        // {
        //     if ((_chanlUsers[i].getModes('o') || _chanlUsers[i].getModes('O')) && pos > 0 && existedUsers[pos] != '@')
        //         existedUsers.insert(pos - 1, 1, '@');
        // }
       
    }
    return users;
}

void Channel::add_user(Client &user)
{
    std::string msg;
    //: AHAMMA!~FSD@26d-ac5f-603e-c171-01c.67.196.ip JOIN :#AHAMMAM
    msg = ":" + user.getNickName() + "!~FSD@26d-ac5f.ip JOIN :" + _chanlName + "\n";
    _chanlUsers.push_back(user);
    send(user.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
};

bool Channel::is_userInChannel(Client user)
{
    for (size_t i = 0; i < _chanlUsers.size(); i++)
    {
        if (user == _chanlUsers[i])
            return (1);
    }
    return 0;
};

void Channel::printAllUser()
{
    for (size_t i = 0; i < _chanlUsers.size(); i++)
    {
        std::cout << i << "-----> " << _chanlUsers[i].getNickName() << "\n";
    }
}

void Channel::updateChanlUsers(std::vector<Client> serverClients)
{
    for (size_t i = 0; i < _chanlUsers.size(); i++)
    {
        for (size_t j = 0; j < serverClients.size(); j++)
        {
            if (_chanlUsers[i].getFd() == serverClients[j].getFd())
                _chanlUsers[i] = serverClients[j];
        }
    }
}

