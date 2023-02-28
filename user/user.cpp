/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:39:02 by lahammam          #+#    #+#             */
/*   Updated: 2023/02/28 17:51:42 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"

User::User()
{
    auth = 0;
    setPass = 0;
};

void User::set_nickname(std::string _nick) { nick = _nick; };
void User::set_username(std::string _username) { username = _username; };
void User::set_auth(bool _auth) { auth = _auth; };
void User::set_pass(bool _pass) { setPass = _pass; };
void User::set_fdClient(int fd) { fdClient = fd; };

std::string User::get_nickname() { return (nick); };
std::string User::get_username() { return (username); };
bool User::get_auth() { return (auth); };
bool User::get_pass() { return (setPass); };
int User::get_fdClient() { return (fdClient); };

User::~User(){};