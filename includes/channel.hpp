/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:21:49 by lahammam          #+#    #+#             */
/*   Updated: 2023/03/17 12:19:50 by lahammam         ###   ########.fr       */
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
    bool invitOnly;
} ChanelModes;

class Channel
{
private:
    std::string _chanlName;
    std::string _chanlTopic;
    std::string _chanlPass;
    int _fdCreator;
    int _limit;
    ChanelModes _modes;
    std::vector<Client> _chanlUsers;
    std::vector<Client> _chanOperator;

public:
    Channel();
    ~Channel();

    // setters and getters
    void set_chanlName(std::string name);
    void set_chanlPass(std::string pass);
    void setChannelTopic(std::string newTopic);
    void setModes(char mode, bool status);
    void setLimit(int limit);
    void setInvitOnly(bool invt);
    void setCreator(int ctr);

    std::string get_chanlName();
    std::string get_chanlPass() const;
    std::string getChannelTopic() const;
    std::vector<Client> get_chanlUsers();
    int getLimit() const;
    ChanelModes getModes() const;
    bool getInvitOnly();
    int getCreator();

    void add_Operator(Client clr);
    void remove_Operator();
    std::vector<Client> getOperChannel();
    bool ft_isOperator(Client clt);

    // other functions
    std::string getallUsers(std::string &existedUsers, std::vector<Client> serverClients);
    int getClientsNbr();
    void add_user(Client &user);
    int is_userInChannel(Client user);
    void printAllUser();
    void updateChanlUsers(std::vector<Client> serverClients);
    void eraseUser(int i);
    void updateNickUser(int i, std::string nk);
    void add_userbyInveted(Client &user, Client &geust);
};
