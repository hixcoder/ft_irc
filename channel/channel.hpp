/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:21:49 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/05 11:52:43 by ahammam          ###   ########.fr       */
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
    void set_chanlName(std::string name);
    void set_chanlPass(std::string pass);
    std::string get_chanlName();
    std::string get_chanlPass();

    void add_user(User user);
    bool is_userInChannel(User user);
    void printAllUser();
    ~Channel();
};
