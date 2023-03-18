/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:46:07 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/18 13:52:37 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

int main(int ac, char **av)
{
    if (ac == 3)
    {
        int port = atoi(av[1]);
        if (port >= 5550 && port <= 5565)
        {
            Server serv(port, av[2]);
            serv.runServer();
            return 0;
        }
    }
    std::cout << "=> Please enter: ./ircserv: <port[5550-5565]> <password>\n";
    return 0;
}