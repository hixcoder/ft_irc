/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:20:38 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/02 12:32:27 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.hpp"

int main(int ac, char **av)
{
	// if (ac  != 3)
	// {
	// 	std::cerr<<"invalide arg\n";
	// 	return(1);
	// }
	Server Server(1111);
	Server.createSocket();
	Server.bindSocket();
	Server.listenSocket();
	Server.pollSocket();
	Server.closeSocket();
}