/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:10:25 by lahammam          #+#    #+#             */
/*   Updated: 2023/02/28 18:35:33 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::ft_pass_cmd(int i, std::vector<std::string> cmds)
{

    if (cmds.size() == 1)
        ft_print_error("PASS", ERR_NEEDMOREPARAMS, users[i]);
    else if (cmds.size() == 2)
    {
        if (strcmp(cmds[1].c_str(), password.c_str()))
            ft_print_error("PASS", ERR_PASSWDMISMATCH, users[i]);
        else if (users[i].get_pass())
        {
            ft_print_error("PASS", ERR_ALREADYREGISTRED, users[i]);
        }
        else
        {
            users[i].set_pass(1);
        }
    }
};
