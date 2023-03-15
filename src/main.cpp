/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:46:07 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/15 11:17:24 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

int main(int ac, char **av)
{
    if (ac == 3)   
    {
        Server serv(av[1], av[2]);
        serv.runServer();
    }
    else
        std::cout << "=> please enter: ./ircserv: <port> <password>\n";
    return 0;
}