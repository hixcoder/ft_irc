/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:30:14 by alouzizi          #+#    #+#             */
/*   Updated: 2023/03/04 08:49:10 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.hpp"

void exitPerror(const char *message)
{
	perror(message);
	exit(1);
}

std::vector<std::string> ft_split(std::string str, char separator)
{
    std::vector<std::string> result;
    size_t i = 0;
    std::string s;
    while (i < str.size())
    {
        if (str[i] == separator || str[i] == '\n')
        {
            if (!s.empty())
            {
                result.push_back(s);
                s.clear();
            }
            if (str[i] == '\n')
                break;
        }
        else
            s += str[i];
        i++;
    }
    if (!s.empty())
        result.push_back(s);
    return (result);
}

int Server::connectionRegistration(char *message, Client user)
{
	
	std::vector<std::string> cmd = ft_split(message, ' ');
	if (strcmp(cmd[0].c_str(), "PASS") == 0)
		passCmd(cmd, user, message);
	else if (strcmp(cmd[0].c_str(), "NICK") == 0)
		nickCmd(cmd, user, message);
	else if ((strcmp(cmd[0].c_str(), "USER") == 0))
        userMsg(cmd, user, message);
	else
		std::cout<<"Cmd cannot found\n";
	return(0);
}