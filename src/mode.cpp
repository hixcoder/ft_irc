/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:39:04 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/18 14:30:26 by lahammam         ###   ########.fr       */
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
		msg = ":@localhos " + std::to_string(401) + " " + " MODE: can't find " + cmd[1] + " in channels or users\n";
		send(user.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
		return;
	}
	if (index != -1)
		return (handlechanlModeCmd(user, cmd, index));
	if (!validMode(cmd[2]))
		return (ft_print_error("MODE", ERR_UMODEUNKNOWNFLAG, user));
	size_t l = 1;
	while (l < cmd[1].length())
	{
		if (cmd[2][0] == '+')
			user.setModes(cmd[2][l], true);
		else if (cmd[2][0] == '-')
			user.setModes(cmd[2][l], false);
		l++;
	}
	msg = ":@localhost MODE " + cmd[1] + " " + cmd[2] + "\n";
	send(user.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}

bool validMode(std::string mode)
{
	size_t i = 1;

	if ((mode[0] != '+' && mode[0] != '-'))
		return (false);
	while (i < mode.length())
	{
		if (mode[i] != 'i' && mode[i] != 'w' && mode[i] != 's' && mode[i] != 'o' && mode[i] != 'O' && mode[i] != 'r' && mode[i] != 'a')
			return (false);
		i++;
	}
	return (true);
}

bool validchanelMode(std::string mode)
{
	size_t i = 1;
	if ((mode[0] != '+' && mode[0] != '-'))
		return (false);
	while (i < mode.length())
	{

		if (mode[i] != 'o' && mode[i] != 'n' && mode[i] != 'l' && mode[i] != 't' && mode[i] != 'k' && mode[i] != 'i' && mode[i] != 's')
			return (false);
		i++;
	}
	return (true);
}

void Server::handlechanlModeCmd(Client &user, std::vector<std::string> cmds, int i)
{
	std::string msg;
	if (_channels[i].is_userInChannel(user) == -1)
		return (ft_print_error(cmds[1], ERR_NOTONCHANNEL, user));
	if (cmds.size() <= 2)
	{
		msg = ":@localhost MODE " + cmds[1] + " +\n";
		send(user.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
		return;
	}
	if (_channels[i].ft_isOperator(user) == false)
		return (ft_print_error(_channels[i].get_chanlName(), ERR_CHANOPRIVSNEEDED, user));
	if (!validchanelMode(cmds[2]))
		return (ft_print_error("MODE", ERR_UMODEUNKNOWNFLAG, user));
	size_t l = 1;
	size_t index = 2;
	while (l < cmds[2].length())
	{
		if ((cmds[2][l] == 'l' || cmds[2][l] == 'k'))
		{
			if (index + 1 < cmds.size())
			{
				index++;
				if (cmds[2][l] == 'l' && cmds[2][0] == '+')
				{
					if (atoi(cmds[index].c_str()) <= 0 || _channels[i].get_chanlUsers().size() > (size_t)atoi(cmds[index].c_str()))
						return (ft_print_error(_channels[i].get_chanlName(), ERR_CHANNELISFULL, user));
					_channels[i].setLimit(atoi(cmds[index].c_str()));
				}
				else if (cmds[2][l] == 'k' && cmds[2][0] == '+')
				{
					if (_channels[i].getModes().key)
						return (ft_print_error("MODE", ERR_KEYSET, user));
					_channels[i].set_chanlPass(cmds[index]);
				}
			}
			else
				return (ft_print_error("MODE", ERR_NEEDMOREPARAMS, user));
		}
		if (cmds[2][0] == '+')
			_channels[i].setModes(cmds[2][l], true);
		else if (cmds[2][0] == '-')
			_channels[i].setModes(cmds[2][l], false);
		l++;
	}
	msg = ":@localhost MODE " + cmds[1] + " " + cmds[2] + "\n";
	send(user.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}
