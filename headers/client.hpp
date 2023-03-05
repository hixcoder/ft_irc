/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:02:02 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/05 11:30:38 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <string>

struct modes
{
	bool away;
	bool invisible;
	bool wallops;
	bool restricted;
	bool operator_;
	bool localOperator;
	bool receiveServerNotices;
};

class Client
{
	std::string _nick;
	std::string _username;
	int			_fd;
	bool		_pass;
	struct		modes _modes;

public:
	void		setNick(std::string value);
	void		setFd(int value);
	int			getFd();
	std::string getNick();
	void		setPassStatus(bool status);
	bool		passStatus();
	void		setModes(char mode, bool status);
	bool		isRegistered();
	std::string getModes(char mode);
};

#endif