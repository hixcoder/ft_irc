/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:02:02 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/03 10:09:44 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <string>
class Client
{
	std::string nick;
	std::string username;
	int fd;
	bool _pass;

public:
	void setNick(std::string value);
	void setFd(int value);
	int getFd();
	std::string getNick();
	void setPassStatus(bool status);
	bool passStatus();
};

#endif