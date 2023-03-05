/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:21:53 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/05 11:53:42 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_irc.hpp"

Channel::Channel(){};

void Channel::set_chanlName(std::string name) { chanlName = name; };
std::string Channel::get_chanlName() { return chanlName; };

void Channel::get_chanlPass(std::string pass) { chanlPass = pass; };
std::string Channel::set_chanlPass() { return chanlPass; };

void Channel::add_user(User user)
{
    chanlUsers.push_back(user);
};
bool Channel::is_userInChannel(User user)
{
    for (size_t i = 0; i < chanlUsers.size(); i++)
    {
        if (user == chanlUsers[i])
            return (1);
    }
    return 0;
};

void Channel::printAllUser()
{
    for (size_t i = 0; i < chanlUsers.size(); i++)
    {
        std::cout << i << "-----> " << chanlUsers[i].get_nickname() << "\n";
    }
}
Channel::~Channel(){};
