/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:15:43 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/15 11:34:22 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ircserv.hpp"

class Channel;
typedef struct modes
{
    bool away;
    bool invisible;
    bool wallops;
    bool restricted;
    bool operator_;
    bool localOperator;
    bool receiveServerNotices;
} Modes;

class Client
{
private:
    int _fd;
    int _is_auth;
    bool _pass;
    std::string _nickName;
    std::string _userName;
    std::string _hostName;
    std::string _serverName;
    std::string _realName;
    Modes _modes;
    long _startTime;
    struct sockaddr_in _client_addr;
    std::string _buff;

    std::string _msgTemp;

public:
    Client(int fd);
    ~Client();

    // client's functions
    bool isRegistered();
    int isUserFinishRegistered();
    bool operator==(Client &other) const;

    // seters and getters
    void setAuth(int auth);
    void setPass(bool pass);
    void setNickName(std::string nickName);
    void setUserName(std::string userName);
    void setHostName(std::string hostName);
    void setServerName(std::string serverName);
    void setRealName(std::string realName);
    void setModes(char mode, bool status);
    void setOper(bool status);
    void setBuff(std::string buffer);
    void setClientAddr(struct sockaddr_in client_addr);
    void setMsgTemp(std::string msg);

    int getFd() const;
    int getAuth() const;
    bool getPass() const;
    std::string getNickName() const;
    std::string getUserName() const;
    std::string getHostName() const;
    std::string getServerName() const;
    std::string getRealName() const;
    long getStartTime() const;
    bool getModes(char mode);
    std::string getBuff() const;
    std::string getMsgTemp() const;
    struct sockaddr_in getClientAddr() const;
    void exitChannles(std::vector<Channel> channles);
    void addBuff(std::string buffer);
};
