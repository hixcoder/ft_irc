/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:21:53 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/10 12:28:39 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

Channel::Channel(){

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
int Channel::getClientsNbr(){return _chanlUsers.size();}

std::string Channel::getallUsers()
{
    std::string users = "";
    for (size_t i = 0; i < _chanlUsers.size(); i++)
    {
        if (_chanlUsers[i].getModes('o') || _chanlUsers[i].getModes('O'))
            users += " @" + _chanlUsers[i].getNickName();
        else
            users += " " + _chanlUsers[i].getNickName();
    }
    return users;
}

void Channel::add_user(Client user)
{
    std::string msg;

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

void Channel::setModes(char mode, bool status)
{
    if (mode == 'l')
        _modes.limit = status;
    else if (mode == 'k' && status == true)
        _modes.key = status;
    else if (mode == 't')
        _modes.topic = status;
    else if (mode == 'n')
        _modes.noOutsideMsg = status;
}
void Channel::setLimit(int limit)
{
    _limit = limit; 
}

int Channel::getLimit() const
{
    return _limit;
}

ChanelModes Channel::getModes() const
{
    return _modes;
}