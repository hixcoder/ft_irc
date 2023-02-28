/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:38:58 by lahammam          #+#    #+#             */
/*   Updated: 2023/02/28 12:24:42 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include "../ft_irc.hpp"

class User
{
private:
    std::string nick;
    std::string username;
    bool auth;
    bool setPass;
    int fdClient;

public:
    User();
    void set_nickname(std::string _nick);
    void set_username(std::string _username);
    void set_auth(bool _auth);
    void set_pass(bool _pass);
    void set_fdClient(int fd);

    std::string get_nickname();
    std::string get_username();
    bool get_auth();
    bool get_pass();
    int get_fdClient();
    ~User();
};

#endif