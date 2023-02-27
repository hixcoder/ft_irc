/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:38:58 by lahammam          #+#    #+#             */
/*   Updated: 2023/02/27 18:57:42 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include "../ft_irc.hpp"

class User
{
private:
    std::string nick;
    std::string username;

public:
    User(/* args */);
    User(std::string _nick, std::string _username);
    ~User();
};

#endif