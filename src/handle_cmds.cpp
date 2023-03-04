/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:01:08 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/04 15:37:08 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/ircserv.hpp"

void Server::ft_hundle_cmd(Client &client, char *buffer)
{
    std::vector<std::string> spl = ft_split(buffer, ' ');
    if (strcmp("PASS", spl[0].c_str()) == 0)
        Server::handlePassCmd(client, spl, buffer);
    else if (strcmp("USER", spl[0].c_str()) == 0)
        Server::handleUserCmd(client, spl);
    else if (strcmp("NICK", spl[0].c_str()) == 0)
        Server::handleNickCmd(client, spl);
    else if (strcmp("PRIVMSG", spl[0].c_str()) == 0)
        Server::handlePrivmsgCmd(client, spl);
    else if (strcmp("QUIT", spl[0].c_str()) == 0)
        Server::handleQuitCmd(client);
    else if (strcmp("OPER", spl[0].c_str()) == 0)
        Server::handleOperCmd(client, spl);
    else
        ft_print_error(spl[0].c_str(), ERR_UNKNOWNCOMMAND, client);
        
}

// ================================================
// AUTHENTIFICATION COMMANDS
// ================================================

void Server::handlePassCmd(Client &client, std::vector<std::string> cmds, char *buffer)
{
    std::string pass = "";

    if (cmds.size() == 1)
        ft_print_error("PASS", ERR_NEEDMOREPARAMS, client);
    else
    {
        pass = strchr(buffer, ' ');
        pass.erase(0, 1);
        pass.erase(pass.size() - 1, 1);
        if (strcmp(pass.c_str(), _passwd))
            ft_print_error("PASS", ERR_PASSWDMISMATCH, client);
        else if (client.getPass())
            ft_print_error("PASS", ERR_ALREADYREGISTRED, client);
        else
            client.setPass(1);
    }
};

void Server::handleNickCmd(Client &client, std::vector<std::string> cmds)
{
    if (cmds.size() == 1)
        ft_print_error("", ERR_NONICKNAMEGIVEN, client);
    else if (ft_isvalid_nickname(cmds[1]) == 0)
        ft_print_error(cmds[1], ERR_ERRONEUSNICKNAME, client);
    else if (ft_isalreadyused(cmds[1], client, _clients) == 1)
        ft_print_error(cmds[1], ERR_NICKNAMEINUSE, client);
    else
    {
        if (ft_isregister(client))
        {
            // std::string msg = "::punch.wa.us.dal.net NICK : " + cmds[1] + "\n";
            std::string msg = "> " + client.getNickName() + "!~" + (std::string)LOCAL_IP + " NICK :" + cmds[1] + "\n";
            send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
        }
        client.setNickName(cmds[1]);
    }
};

void Server::handleUserCmd(Client &client, std::vector<std::string> cmds)
{

    if (cmds.size() < 5)
        ft_print_error("USER", ERR_NEEDMOREPARAMS, client);
    else
    {
        client.setUserName(cmds[1]);
        client.setHostName(cmds[2]);
        client.setServerName(cmds[3]);
        client.setRealName(cmds[4]);
    }
};


// ================================================
// USER COMMANDS
// ================================================

// handle PRIVMSG command
void Server::handlePrivmsgCmd(Client &client, std::vector<std::string> cmds)
{
    if (cmds.size() == 1)
        ft_print_error(cmds[0], ERR_NORECIPIENT, client);
    else if (cmds.size() == 2)
        ft_print_error("", ERR_NOTEXTTOSEND, client);
    // else if (ft_isregister(client))
    //     ft_print_error(cmds[1], ERR_NOSUCHNICK, client);
    else
    {
        std::cout << "-----> " << cmds[1] << std::endl;
        std::vector<std::string> clts = ft_split(cmds[1], ',');
        for (size_t k = 0; k < clts.size(); k++)
        {
            std::cout << clts[k] << std::endl;
        }

        size_t j = 0;
        for (; j < _clients.size(); j++)
        {

            if (strcmp(cmds[1].c_str(), _clients[j].getNickName().c_str()) == 0)
            {
                // :LKK!~WERWE@d2a6-9017-cfb7-6374-1329.iam.net.ma PRIVMSG HAMZ :FA:FAS:
                std::string msg = ":" + client.getNickName() + " PRIVMSG " + _clients[j].getNickName() + " " + cmds[2];
                send(_clients[j].getFd(), msg.c_str(), strlen(msg.c_str()), 0);
                break;
            }
        }
        if (j == _clients.size())
            ft_print_error(cmds[1], ERR_NOSUCHNICK, client);
    }
};


// handle QUIT command
void Server::handleQuitCmd(Client &client)
{
    for (size_t i = 0; i < _clients.size(); i++)
    {
        if (_clients[i].getFd() == client.getFd())
        {
            std::string msg = "> " + client.getNickName() + "~" + (std::string)LOCAL_IP + " QUIT :" + "user "+ client.getNickName() + " disconnected\n";
            send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
            close(client.getFd());
            break;
        }
    }
};

// handle OPER command
void Server::handleOperCmd(Client &client, std::vector<std::string> cmds)
{
    if (cmds.size() != 3)
        ft_print_error("OPER", ERR_NEEDMOREPARAMS, client);
    else
    {
        if (cmds[1] != client.getUserName() || cmds[2] != _passwd)
            ft_print_error("OPER", ERR_PASSWDMISMATCH, client);
        else
        {
            if (client.getHostName() == (std::string)LOCAL_IP)
                ft_print_error("OPER", RPL_YOUREOPER, client);
            else
                ft_print_error("OPER", ERR_NOOPERHOST, client);
        }
            
    }
};


// ================================================
// OPERATOR COMMANDS
// ================================================

// handle INVITE command
// handle KICK  command
// handle WALLOPS command
// handle GLOBOPS command
// handle KILL command
// handle RESTART command
// handle OPER command
