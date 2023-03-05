/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:21:53 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/05 19:57:02 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

Channel::Channel(){};
Channel::~Channel(){};

void Channel::set_chanlName(std::string name) { _chanlName = name; };
std::string Channel::get_chanlName() { return _chanlName; };

void Channel::set_chanlPass(std::string pass) { _chanlPass = pass; };
std::string Channel::get_chanlPass() const { return _chanlPass; };

void Channel::add_user(Client user)
{
    _chanlUsers.push_back(user);
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
