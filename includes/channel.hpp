/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:21:49 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/16 08:38:58 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ircserv.hpp"

typedef struct chanelmodes
{
    bool limit;
    bool key;
    bool topic;
    bool noOutsideMsg;
    // bool    operator_;
    // bool    private_;
    // bool    secret;
    // bool    inviteOnly;
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
    int _limit;
    ChanelModes _modes;
    std::vector<Client> _chanlUsers;

public:
    Channel();
    ~Channel();

    // setters and getters
    void set_chanlName(std::string name);
    void set_chanlPass(std::string pass);
    void setChannelTopic(std::string newTopic);
    void setModes(char mode, bool status);
    void setLimit(int limit);

    std::string get_chanlName();
    std::string get_chanlPass() const;
    std::string getChannelTopic() const;
    std::vector<Client> get_chanlUsers();
    int getLimit() const;
    ChanelModes getModes() const;

    // other functions
    std::string getallUsers(std::string &existedUsers, std::vector<Client> serverClients);
    int getClientsNbr();
    void add_user(Client &user);
    int is_userInChannel(Client user);
    void printAllUser();
    void updateChanlUsers(std::vector<Client> serverClients);
    void eraseUser(int i);
    void updateNickUser(int i, std::string nk);
};
