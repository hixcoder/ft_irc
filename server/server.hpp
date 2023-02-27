/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:03:06 by lahammam          #+#    #+#             */
/*   Updated: 2023/02/27 10:56:18 by lahammam         ###   ########.fr       */
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

public:
    Server();

    void handle_events();
    void add_user();
    void recv_msg(int i);

    ~Server();
};

#endif