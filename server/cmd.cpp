/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:10:25 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/01 10:08:26 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::ft_pass_cmd(int i, std::vector<std::string> cmds, char *buffer)
{
    std::string pass = "";

    if (cmds.size() == 1)
        ft_print_error("PASS", ERR_NEEDMOREPARAMS, users[i]);
    else
    {
        pass = strchr(buffer, ' ');
        pass.erase(0, 1);
        pass.erase(pass.size() - 1, 1);
        if (strcmp(pass.c_str(), password.c_str()))
            ft_print_error("PASS", ERR_PASSWDMISMATCH, users[i]);
        else if (users[i].get_pass())
            ft_print_error("PASS", ERR_ALREADYREGISTRED, users[i]);
        else
            users[i].set_pass(1);
    }
};
