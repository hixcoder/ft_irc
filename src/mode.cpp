/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:39:04 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/16 11:41:26 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

void Server::modeCmd(std::vector<std::string> cmd, Client &user)
{
	std::string msg;
	int index;

	if (cmd.size() < 2)
		return (ft_print_error("MODE", ERR_NEEDMOREPARAMS, user));
	index = is_channel_Exit(_channels, cmd[1]);
	if (cmd[1] != user.getNickName() && index == -1)
	{
		msg = "> " + (std::string)LOCAL_IP + " " + std::to_string(401) + ", " + std::to_string(403) + " MODE: can't find " + cmd[1] + " in channels or users\n";
		send(user.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
		return;
	}
	if (index != -1)
		return (handlechanlModeCmd(user, cmd, index));
	if (!validMode(cmd[2]))
		return (ft_print_error("MODE", ERR_UMODEUNKNOWNFLAG, user));
	if (cmd[2][0] == '+')
		user.setModes(cmd[2][1], true);
	else if (cmd[2][0] == '-')
		user.setModes(cmd[2][1], false);
	msg = "> " + (std::string)LOCAL_IP + " " + std::to_string(221) + " MODE: " + user.getNickName() + " " + cmd[2] + "\n";
	send(user.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}

bool validchanelMode(std::string mode)
{
	if (mode.length() != 2 && (mode[0] != '+' && mode[0] != '-'))
		return (false);
	if (mode[1] == 'o' || mode[1] == 'v' || mode[1] == 'l' || mode[1] == 't')
		return (true);
	return (false);
}

void Server::handlechanlModeCmd(Client &user, std::vector<std::string> cmds, int i)
{
	if (_channels[i].is_userInChannel(user) == -1)
		return (ft_print_error(cmds[1], ERR_NOTONCHANNEL, user));
	if (!validchanelMode(cmds[2]))
		return (ft_print_error("MODE", ERR_UMODEUNKNOWNFLAG, user));
	if ((cmds[2][1] == 'l' || cmds[2][1] == 'k') && cmds.size() < 4)
		return (ft_print_error("MODE", ERR_NEEDMOREPARAMS, user));
	else
	{
		if (cmds[2][1] == 'l' && cmds[2][0] == '+')
			_channels[i].setLimit(atoi(cmds[3].c_str()));
		else if (cmds[2][1] == 'k' && cmds[2][0] == '+')
		{
			if (_channels[i].getModes().key)
				return (ft_print_error("MODE", ERR_KEYSET, user));
			_channels[i].set_chanlPass(cmds[3]);
		}
	}
	if (cmds[2][0] == '+')
		_channels[i].setModes(cmds[2][1], true);
	else if (cmds[2][0] == '-')
		_channels[i].setModes(cmds[2][1], false);
	std::string msg = "> " + (std::string)LOCAL_IP + " " + std::to_string(221) + " MODE: " + cmds[1] + " " + cmds[2] + "\n";
	send(user.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}

bool validMode(std::string mode)
{
	if (mode.length() != 2 && (mode[0] != '+' && mode[0] != '-'))
		return (false);
	if (mode[1] == 'i' || mode[1] == 'w' || mode[1] == 's' || mode[1] == 'o' || mode[1] == 'O' || mode[1] == 'r' || mode[1] == 'a')
		return (true);
	return (false);
}