/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:03:06 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/05 09:14:43 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../ft_irc.hpp"

class Server
{
private:
    int _mainsocked;
    std::vector<pollfd> _pollfds;
    std::string _password;
    std::vector<User> _users;
    std::vector<Channel> _channels;

public:
    Server();

    void startServer();
    void addGuest();
    void recv_msg(int i);

    void ft_hundleCmd(int i, char *buffer);
    void ft_passCmd(int i, std::vector<std::string> cmds, char *buffer);
    void ft_nickCmd(int i, std::vector<std::string> cmds);
    void ft_userCmd(int i, std::vector<std::string> cmds, char *buffer);

    void ft_privmsgCmd(int i, std::vector<std::string> cmds, char *buffer);
    void ft_joinCmd(int i, std::vector<std::string> cmds, char *buffer);

    ~Server();
};

#endif
