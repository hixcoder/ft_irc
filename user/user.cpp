/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:39:02 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/01 13:46:31 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"

User::User()
{
    setPass = 0;
};

void User::set_nickname(std::string _nick) { nick = _nick; };
void User::set_username(std::string _username) { username = _username; };
void User::set_hostname(std::string _hostname) { hostname = _hostname; };
void User::set_servername(std::string _servername) { servername = _servername; };
void User::set_realname(std::string _realname) { realname = _realname; };
void User::set_pass(bool _pass) { setPass = _pass; };
void User::set_fdClient(int fd) { fdClient = fd; };

std::string User::get_nickname() { return (nick); };
std::string User::get_username() { return (username); };
std::string User::get_hostname() { return (hostname); };
std::string User::get_servername() { return servername; };
std::string User::get_realname() { return realname; };
bool User::get_pass() { return (setPass); };
int User::get_fdClient() { return (fdClient); };

User::~User(){};