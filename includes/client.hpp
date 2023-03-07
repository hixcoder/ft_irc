/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:15:43 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/07 15:43:59 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "ircserv.hpp"

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
    
public:
    Client(int fd);
    ~Client();
    
    // client's functions
    bool isRegistered();
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
    
    int getFd() const;
    int getAuth() const;
    bool getPass()const;
    std::string getNickName()const;
    std::string getUserName()const;
    std::string getHostName()const;
    std::string getServerName()const;
    std::string getRealName()const;
    bool getModes(char mode);
};



