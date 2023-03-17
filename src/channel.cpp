/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:21:53 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/17 12:21:32 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

Channel::Channel()
{
    _chanlTopic = "";
    _modes.invitOnly = false;
    _modes.key = false;
    _modes.limit = false;
    _modes.noOutsideMsg = false;
    _modes.topic = false;
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

void Channel::setCreator(int ctr)
{
    _fdCreator = ctr;
};

int Channel::getCreator() { return _fdCreator; };

std::string Channel::getallUsers(std::string &existedUsers, std::vector<Client> serverClients)
{
    updateChanlUsers(serverClients);
    std::string users = "";
    for (size_t i = 0; i < _chanlUsers.size(); i++)
    {
        size_t pos = existedUsers.find(_chanlUsers[i].getNickName());
        if (pos == std::string::npos)
        {
            if (ft_isOperator(_chanlUsers[i]))
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

    msg = ":" + user.getNickName() + "!~:@localhost  JOIN :" + _chanlName + "\n";
    _chanlUsers.push_back(user);
    send(user.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
};

void Channel::add_Operator(Client clr)
{
    _chanOperator.push_back(clr);
};

void Channel::remove_Operator()
{
    _chanOperator.pop_back();
};

bool Channel::ft_isOperator(Client clt)
{
    for (size_t i = 0; i < _chanOperator.size(); i++)
    {
        if (clt == _chanOperator[i])
            return true;
    }
    return false;
};

std::vector<Client> Channel::getOperChannel()
{
    return _chanOperator;
};
// :punch.wa.us.dal.net NOTICE @#OOOOO :LKOOOLKO invited LKOOO into channel #OOOOO
void Channel::add_userbyInveted(Client &user, Client &geust)
{
    std::string msg;

    msg = ":" + user.getNickName() + "!~:@localhost  NOTICE @" + _chanlName + " :" + user.getNickName() + " invited " + geust.getNickName() + "into channel " + _chanlName + "\n";
    _chanlUsers.push_back(geust);
    send(user.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
};

int Channel::is_userInChannel(Client user)
{
    for (size_t i = 0; i < _chanlUsers.size(); i++)
    {
        if (user == _chanlUsers[i])
            return (i);
    }
    return -1;
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

void Channel::setInvitOnly(bool invt)
{
    _modes.invitOnly = invt;
};

bool Channel::getInvitOnly()
{
    return _modes.invitOnly;
};

std::vector<Client> Channel::get_chanlUsers()
{
    return _chanlUsers;
};

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
    else if (mode == 'i')
        _modes.invitOnly = status;
}

void Channel::setLimit(int limit)
{
    _limit = limit;
}

int Channel::getLimit() const
{
    return _limit;
}

void Channel::eraseUser(int i)
{
    _chanlUsers.erase(_chanlUsers.begin() + i);
};

void Channel::updateNickUser(int i, std::string nk)
{
    _chanlUsers[i].setNickName(nk);
};

ChanelModes Channel::getModes() const
{
    return _modes;
}
