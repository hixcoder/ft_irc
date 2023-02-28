/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:03:06 by lahammam          #+#    #+#             */
/*   Updated: 2023/02/28 13:36:54 by lahammam         ###   ########.fr       */
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
    std::vector<User> guests;
    std::vector<User> users;

public:
    Server();

    void start_server();
    void add_guest();
    void recv_msg(int i);

    int verifie_pass(std::string _passU);

    ~Server();
};

#endif
