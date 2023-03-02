/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:03:06 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/02 10:14:37 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../ft_irc.hpp"

class Server
{
private:
    int mainsocked;
    std::vector<pollfd> pollfds;
    std::string password;
    std::vector<User> users;

public:
    Server();

    void start_server();
    void add_guest();
    void recv_msg(int i);

    void ft_hundle_cmd(int i, char *buffer);
    void ft_pass_cmd(int i, std::vector<std::string> cmds, char *buffer);
    void ft_nick_cmd(int i, std::vector<std::string> cmds);
    void ft_user_cmd(int i, std::vector<std::string> cmds);

    ~Server();
};

#endif
