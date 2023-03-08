/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:21:49 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/07 16:06:46 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "ircserv.hpp"
class Channel
{
private:
    std::string _chanlName;
    std::string _chanlTopic;
    std::string _chanlPass;
    std::vector<Client> _chanlUsers;

public:
    Channel();
    ~Channel();

    // setters and getters
    void set_chanlName(std::string name);
    void set_chanlPass(std::string pass);
    void setChannelTopic(std::string newTopic);

    
    std::string get_chanlName();
    std::string get_chanlPass() const;
    std::string getChannelTopic() const;

    // other functions
    std::string getallUsers();
    int getClientsNbr();
    void add_user(Client user);
    bool is_userInChannel(Client user);
    void printAllUser();
};
