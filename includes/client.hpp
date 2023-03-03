/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:15:43 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/03 11:10:25 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "ircserv.hpp"

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
    
    
public:
    Client(int fd);
    ~Client();

    int getFd() const;
    int getAuth() const;
    void setAuth(int auth);

    void setPass(bool pass);
    void setNickName(std::string nickName);
    void setUserName(std::string userName);
    void setHostName(std::string hostName);
    void setServerName(std::string serverName);
    void setRealName(std::string realName);

    bool getPass()const;
    std::string getNickName()const;
    std::string getUserName()const;
    std::string getHostName()const;
    std::string getServerName()const;
    std::string getRealName()const;
    
};

