/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:23:01 by lahammam          #+#    #+#             */
/*   Updated: 2023/02/27 19:35:45 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::vector<std::string> ft_split(std::string str, char separator)
{
    std::vector<std::string> result;
    int i = 0;
    std::string s;
    while (str[i] != '\0')
    {
        if (str[i] != separator)
            s += str[i];
        else
        {
            result.push_back(s);
            s.clear();
        }
        i++;
    }
    if (str[i - 1] != separator)
        result.push_back(s);

    return (result);
}