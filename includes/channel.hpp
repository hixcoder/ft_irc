/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:21:49 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/09 18:40:53 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "ircserv.hpp"

typedef struct chanelmodes
{
    bool         limit;
    bool         key;
    bool         topic;
    // bool    operator_;
    // bool    private_;
    // bool    secret;
    // bool    inviteOnly;
    // bool    noOutsideMsg;
    // bool    moderated;
    // bool    setLimit;
    // bool    ban;
    // bool    key;    
    // bool    speakToOp;
} ChanelModes;

class Channel
{
private:
    std::string _chanlName;
    std::string _chanlTopic;
    std::string _chanlPass;
    // int         _limit;
    // ChanelModes _modes;
    std::vector <Client> _chanlUsers;
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
