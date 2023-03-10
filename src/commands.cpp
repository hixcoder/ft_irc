/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:01:08 by hboumahd          #+#    #+#             */
/*   Updated: 2023/03/05 18:53:36 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

void Server::ft_hundle_cmd(Client &client, char *buffer)
{
    std::vector<std::string> spl = ft_split(buffer, ' ');
    if (spl.size() < 1)
        return;
    if (strcmp("PASS", spl[0].c_str()) == 0)
        handlePassCmd(client, spl, buffer);
    else if (strcmp("USER", spl[0].c_str()) == 0)
        handleUserCmd(client, spl, buffer);
    else if (strcmp("NICK", spl[0].c_str()) == 0)
        handleNickCmd(client, spl);
    else if (strcmp("PRIVMSG", spl[0].c_str()) == 0)
        handlePrivmsgCmd(client, spl, buffer);
    else if (strcmp("QUIT", spl[0].c_str()) == 0)
        handleQuitCmd(client);
    else if (strcmp("OPER", spl[0].c_str()) == 0)
        handleOperCmd(client, spl);
    else if (strcmp("JOIN", spl[0].c_str()) == 0)
        ft_joinCmd(client, spl, buffer);
    else if (strcmp("MODE", spl[0].c_str()) == 0)
        modeCmd(spl, client);
    else if (strcmp("KILL", spl[0].c_str()) == 0)
        handleKillCmd(client, spl);
    else if (strcmp("LIST", spl[0].c_str()) == 0)
        handleListCmd(client, spl);
    else if (strcmp("NAMES", spl[0].c_str()) == 0)
        handleNamesCmd(client, spl);
    else if (strcmp("HELP", spl[0].c_str()) == 0)
        handleHelpCmd(client);
    else if (strcmp("TIME", spl[0].c_str()) == 0)
        handleTimeCmd(client);
    else if (strcmp("LUSER", spl[0].c_str()) == 0)
        handleLusersCmd(client);
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
            client.setPass(true);
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

void Server::handleUserCmd(Client &client, std::vector<std::string> cmds, char *buffer)
{
    if (cmds.size() < 5)
        ft_print_error("USER", ERR_NEEDMOREPARAMS, client);
    else if (!client.getUserName().empty())
        ft_print_error("USER", ERR_ALREADYREGISTRED, client);
    else
    {
        client.setUserName(cmds[1]);
        client.setHostName(cmds[2]);
        client.setServerName(cmds[3]);
        if (cmds[4][0] == ':')
        {
            std::string realnm = buffer + std::strlen((cmds[1] + cmds[2] + cmds[3]).c_str()) + 9;
            std::cout << "realname" << realnm << "\n";
            client.setRealName(realnm);
        }
        else
            client.setRealName(cmds[4]);
    }
};

// ================================================
// MSG COMMANDS
// ================================================

// handle PRIVMSG command

void Server::handlePrivmsgCmd(Client &client, std::vector<std::string> cmds, char *buffer)
{
    if (cmds.size() == 1)
        ft_print_error(cmds[0], ERR_NORECIPIENT, client);
    else if (cmds.size() == 2)
        ft_print_error("", ERR_NOTEXTTOSEND, client);
    else
    {
        std::vector<std::string> clts = ft_split(cmds[1], ',');
        for (size_t k = 0; k < clts.size(); k++)
        {
            int fd = ft_isUserExist(clts[k], _clients);
            if (fd) // ft_isRegister(users[i])
            {
                std::string msg;
                if (cmds[2][0] != ':')
                    msg = ":" + client.getNickName() + " PRIVMSG " + _clients[fd].getNickName() + " :" + cmds[2] + "\n";
                else
                    msg = ":" + client.getNickName() + " PRIVMSG " + _clients[fd].getNickName() + " " + strchr(buffer, ':');
                send(_clients[fd].getFd(), msg.c_str(), strlen(msg.c_str()), 0);
            }
            else
                ft_print_error(cmds[k], ERR_NOSUCHNICK, client);
        }
    }
};

// ================================================
// Channel COMMANDS
// ================================================

void Server::ft_joinCmd(Client &client, std::vector<std::string> cmds, char *buffer)
{
    if (cmds.size() == 1)
        ft_print_error("JOIN", ERR_NEEDMOREPARAMS, client);
    else if (!is_validChannel(cmds[1]))
        ft_print_error("JOIN", ERR_NOSUCHCHANNEL, client);
    else
    {
        std::vector<std::string> chanls;
        std::vector<std::string> chanlsPass;
        chanls = ft_split(cmds[1], ',');
        if (!cmds[2].empty())
            chanlsPass = ft_split(cmds[2], ',');
        for (size_t l = 0; l < chanls.size(); l++)
        {
            int indx = is_channel_Exit(_channels, chanls[l]);
            std::string key;
            if (!cmds[2].empty() && l < chanlsPass.size())
                key = chanlsPass[l];
            if (indx == -1)
            {
                Channel channel;
                channel.set_chanlName(chanls[l]);
                if (!cmds[2].empty() && l < chanlsPass.size())
                    channel.set_chanlPass(key);
                channel.add_user(client);
                _channels.push_back(channel);
            }
            else
            {
                if (_channels[indx].get_chanlPass().empty() || _channels[indx].get_chanlPass() == key)
                    _channels[indx].add_user(client);
                else
                    ft_print_error(_channels[indx].get_chanlName(), ERR_BADCHANNELKEY, client);
                if (!_channels[indx].is_userInChannel(client))
                    _channels[indx].add_user(client);
                _channels[indx].printAllUser();
            }
        }

        // for (size_t k = 0; k < chanls.size(); k++)
        // {
        //     // std::cout << "------> " << chanls[k] << std::endl;
        //     // if (!chanlsPass.empty() && k < chanlsPass.size())
        //     //     std::cout << "-> " << chanlsPass[k] << std::endl;
        // }
    }
    buffer++;
};

void Server::handleListCmd(Client &client, std::vector<std::string> cmds)
{
    ft_print_error("LIST", RPL_LISTSTART, client);
    if (cmds.size() == 1)
    {
        for (size_t i = 0; i < _channels.size(); i++)
        {
            std::string msg = "> " + (std::string)LOCAL_IP + " " + std::to_string(RPL_LIST) + " " + \
            client.getNickName() + " " +  _channels[i].get_chanlName() + " " + \
            std::to_string(_channels[i].getClientsNbr()) + " :" + _channels[i].getChannelTopic() + "\n";
            send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
        }
    }
    else if (cmds.size() > 1)
    {
        std::string allChanls = cmds[1];
        for (size_t i = 2; i < cmds.size(); i++)
            allChanls += " " + cmds[i];
        std::vector<std::string> splChanls = ft_split(allChanls, ',');
        for (size_t i = 0; i < _channels.size(); i++)
        {
            for (size_t j = 0; j < splChanls.size(); j++)
            {
                if (splChanls[j] == _channels[i].get_chanlName())
                {
                    std::string msg = "> " + (std::string)LOCAL_IP + " " + std::to_string(RPL_LIST) + " " + \
                    client.getNickName() + " " +  _channels[i].get_chanlName() + " " + \
                    std::to_string(_channels[i].getClientsNbr()) + " :" + _channels[i].getChannelTopic() + "\n";
                    send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
                }
            }
        }
    }
    ft_print_error("LIST", RPL_LISTEND, client);
}


void Server::handleNamesCmd(Client &client, std::vector<std::string> cmds)
{
    if (cmds.size() == 1)
    {
        std::string allUsers = "";
        for (size_t i = 0; i < _channels.size(); i++)
            allUsers += " " + _channels[i].getallUsers();
        std::string msg = "> " + (std::string)LOCAL_IP + " " + std::to_string(RPL_NAMREPLY) + " " + \
        client.getNickName() + " = * :" + allUsers + "\n";
        send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
        ft_print_error(" *", RPL_ENDOFNAMES, client);
    }
    else if (cmds.size() > 1)
    {
        std::string allChanls = "";
        std::string allChanlsTmp = cmds[1];
        for (size_t i = 2; i < cmds.size(); i++)
            allChanlsTmp += " " + cmds[i];
        std::vector<std::string> splChanls = ft_split(allChanlsTmp, ',');
        for (size_t i = 0; i < _channels.size(); i++)
        {
            for (size_t j = 0; j < splChanls.size(); j++)
            {
                if (splChanls[j] == _channels[i].get_chanlName())
                {
                    allChanls += splChanls[j];
                    std::string msg = "> " + (std::string)LOCAL_IP + " " + std::to_string(RPL_NAMREPLY) + " " + \
                    client.getNickName() + " = " + _channels[i].get_chanlName() + " :" + _channels[i].getallUsers() + "\n";
                    send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
                }
            }
        }
        ft_print_error(allChanls, RPL_ENDOFNAMES, client);
    }
}

// ================================================
// OPERATOR COMMANDS
// ================================================

// handle INVITE command
// handle KICK  command
// handle KILL command [OK]
// handle OPER command [OK]
// handle RESTART command
// handle WALLOPS

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
            {
                client.setOper(true);
                ft_print_error("OPER", RPL_YOUREOPER, client);
            }
            else
                ft_print_error("OPER", ERR_NOOPERHOST, client);
        }
    }
};

// handle KILL command
void Server::handleKillCmd(Client &client, std::vector<std::string> cmds)
{
    if (cmds.size() < 3)
        ft_print_error("KILL", ERR_NEEDMOREPARAMS, client);
    else
    {
        if (client.getModes('O') || client.getModes('o'))
        {
            if (cmds[1] == _serverName)
            {
                ft_print_error("KILL", ERR_CANTKILLSERVER, client);
                return;
            }
            for (size_t i = 0; i < _clients.size(); i++)
            {
                if (_clients[i].getNickName() == cmds[1])
                {
                    std::string reason = cmds[2];
                    for (size_t i = 2; i < cmds.size(); i++)
                        reason += " " + cmds[i];
                    std::string msg = "> " + client.getNickName() + "~" + (std::string)LOCAL_IP + " KILL " + cmds[1] + ": " + reason + "\n";
                    send(_clients[i].getFd(), msg.c_str(), strlen(msg.c_str()), 0);
                    close(_clients[i].getFd());
                    return;
                }
            }
            ft_print_error("KILL", ERR_NOSUCHNICK, client);
        }
        else
            ft_print_error("KILL", ERR_NOPRIVILEGES, client);
    }
};

// ================================================
// Server Informations COMMANDS
// ================================================

void    Server::handleHelpCmd(Client &client)
{

    std::string helpmsg;
    helpmsg.append(GREEN);
    helpmsg.append("IRC Server Help: \n");
    helpmsg.append(RESET);
    helpmsg.append(YELLOW);
    helpmsg.append("-Registration Commands:\n");
    helpmsg.append(RESET);
    helpmsg.append("\tPASS <password> : set your password\n");
    helpmsg.append("\tNICK <nickname> : set your nickname\n");
    helpmsg.append("\tUSER <username> <hostname> <servername> <realname> : set your username\n");
    helpmsg.append(YELLOW);
    helpmsg.append("-Channel Commands:\n");
    helpmsg.append(RESET);
    helpmsg.append("\tJOIN <channel>{,<channel>} [<key>{,<key>}]: join a channel\n");
    helpmsg.append("\tPART <channel>{,<channel>} : leave a channel\n");
    helpmsg.append("\tList [<channel>{,<channel>}]: list all channels\n");
    helpmsg.append("\tNAMES <channel> : list all users in a channel\n");
    helpmsg.append("\tMODE <channel> <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>] : set channel modes\n");
    helpmsg.append("\tTOPIC <channel> [<topic>] : set or get channel topic\n");
    helpmsg.append("\tINVITE <nickname> <channel> : invite a user to a channel\n");
    helpmsg.append("\tKICK <channel> <user> [<comment>] : kick a user from a channel\n");
    helpmsg.append(YELLOW);
    helpmsg.append("-Operator Commands:\n");
    helpmsg.append(RESET);
    helpmsg.append("\tKILL <nickname> <comment> : kill a user\n");
    helpmsg.append("\tOPER <username> <password> : become an IRC operator\n");
    helpmsg.append("\tServer Informations Commands:\n");
    helpmsg.append("\tLUSERS [<mask> [<target>]] : get the number of users\n");
    helpmsg.append(YELLOW);
    helpmsg.append("-Send message Commands:\n");
    helpmsg.append(RESET);
    helpmsg.append("\tPRIVMSG <receiver>{,<receiver>} <text to be sent> : send a message to a user or a channel\n");
    helpmsg.append("\tNOTICE <nickname> <text> : send a notice to a user\n");

    send(client.getFd(), helpmsg.c_str(), helpmsg.size(), 0);
}
void Server::handleTimeCmd(Client &client)
{
    //add RPL_TIME
    time_t time;
    struct timeval t;
    gettimeofday(&t, NULL);
    time = t.tv_sec;
    struct tm *tm = localtime(&time);
    std::string msg = "> " + client.getNickName() + " " + (std::string)LOCAL_IP + " Time is :";
    msg.append(asctime(tm));
    send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}

void Server::handleLusersCmd(Client &client)
{
    std::string msg = "> " + client.getNickName() + " " + (std::string)LOCAL_IP + " LUSER :" + std::to_string(_clients.size()) + "\n";
    send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}

// ================================================
// Other COMMANDS
// ================================================

// handle QUIT command
void Server::handleQuitCmd(Client &client)
{
    for (size_t i = 0; i < _clients.size(); i++)
    {
        if (_clients[i].getFd() == client.getFd())
        {
            std::string msg = "> " + client.getNickName() + "~" + (std::string)LOCAL_IP + " QUIT :" + "client " + client.getNickName() + " disconnected\n";
            send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
            close(client.getFd());
            break;
        }
    }
};