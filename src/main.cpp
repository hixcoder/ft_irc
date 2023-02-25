/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:46:07 by hboumahd          #+#    #+#             */
/*   Updated: 2023/02/25 11:17:06 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"


int main(int ac, char **av)
{
    if (ac == 3)
    {
        std::cout << "port: " << av[1] << "\npass: " << av[2] << "\n";
    }
    else
        std::cout << "=> please enter: ./ircserv: <port> <password>\n";
    return 0;
}