/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:39:02 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/05 11:40:42 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"

User::User()
{
    _setPass = 0;
};

void User::set_nickname(std::string nick) { _nick = nick; };
void User::set_username(std::string username) { _username = username; };
void User::set_hostname(std::string hostname) { _hostname = hostname; };
void User::set_servername(std::string servername) { _servername = servername; };
void User::set_realname(std::string realname) { _realname = realname; };
void User::set_pass(bool pass) { _setPass = pass; };
void User::set_fdClient(int fd) { _fdClient = fd; };

std::string User::get_nickname() { return (_nick); };
std::string User::get_username() { return (_username); };
std::string User::get_hostname() { return (_hostname); };
std::string User::get_servername() { return (_servername); };
std::string User::get_realname() { return (_realname); };
bool User::get_pass() { return (_setPass); };
int User::get_fdClient() { return (_fdClient); };

bool User::operator==(User &other) const
{
    if (std::strcmp(_nick.c_str(), other.get_nickname().c_str()) == 0)
        return 1;
    return 0;
};

User::~User(){};