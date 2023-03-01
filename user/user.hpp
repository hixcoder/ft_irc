/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:38:58 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/01 13:20:03 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include "../ft_irc.hpp"

class User
{
private:
    bool setPass;
    std::string nick;
    std::string username;
    std::string hostname;
    std::string servername;
    std::string realname;
    bool auth;

    int fdClient;

public:
    User();
    void set_nickname(std::string _nick);

    void set_username(std::string _username);
    void set_hostname(std::string _hostname);
    void set_servername(std::string _servername);
    void set_realname(std::string _realname);

    void set_auth(bool _auth);
    void set_pass(bool _pass);
    void set_fdClient(int fd);

    std::string get_nickname();
    std::string get_username();
    std::string get_hostname();
    std::string get_servername();
    std::string get_realname();
    bool get_auth();
    bool get_pass();
    int get_fdClient();
    ~User();
};

#endif