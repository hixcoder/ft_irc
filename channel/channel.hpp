/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:21:49 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/03 10:28:35 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_irc.hpp"

class Channel
{
private:
    std::string chanlName;
    std::string chanlPass;
    std::vector<User> chanlUsers;

public:
    Channel();
    ~Channel();
};
