/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:39:02 by lahammam          #+#    #+#             */
/*   Updated: 2023/02/27 18:58:32 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"

User::User(/* args */){};

User::User(std::string _nick, std::string _username)
{
    nick = _nick;
    username = _username;
};

User::~User(){};