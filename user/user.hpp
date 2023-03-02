/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:38:58 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/02 15:47:30 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include "../ft_irc.hpp"

class User
{
private:
    bool _setPass;
    std::string _nick;
    std::string _username;
    std::string _hostname;
    std::string _servername;
    std::string _realname;

    int _fdClient;

public:
    User();
    void set_nickname(std::string nick);

    void set_username(std::string username);
    void set_hostname(std::string hostname);
    void set_servername(std::string servername);
    void set_realname(std::string realname);

    void set_pass(bool pass);
    void set_fdClient(int fd);

    std::string
    get_nickname();
    std::string get_username();
    std::string get_hostname();
    std::string get_servername();
    std::string get_realname();
    bool get_pass();
    int get_fdClient();
    ~User();
};

#endif