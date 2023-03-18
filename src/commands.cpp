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

#include <iomanip>
#include <sstream>

// :punch.wa.us.dal.net 451 * PRIVMSG :You must finish connecting with another nickname first.

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
    else if (!client.isRegistered())
    {
        if (isCmdExit(spl[0].c_str()))
        {
            if (client.isUserFinishRegistered() == 1)
                client.setMsgTemp(" (Please Enter Password) ");
            if (client.isUserFinishRegistered() == 2)
                client.setMsgTemp(" (Please Enter NICKNAME) ");
            if (client.isUserFinishRegistered() == 3)
                client.setMsgTemp(" (Please Enter USERNAME) ");
            ft_print_error(spl[0].c_str(), ERR_NOTREGISTERED, client);
            client.setMsgTemp("");
        }
    }
    else if (strcmp("PRIVMSG", spl[0].c_str()) == 0)
        handlePrivmsgCmd(client, spl, buffer);
    else if (strcmp("NOTICE", spl[0].c_str()) == 0)
        handleNoticeCmd(client, spl, buffer);
    else if (strcmp("QUIT", spl[0].c_str()) == 0)
        handleQuitCmd(client);
    else if (strcmp("OPER", spl[0].c_str()) == 0)
        handleOperCmd(client, spl);
    else if (strcmp("JOIN", spl[0].c_str()) == 0)
        ft_joinCmd(client, spl);
    else if (strcmp("PART", spl[0].c_str()) == 0)
        ft_partCmd(client, spl);
    else if (strcmp("MODE", spl[0].c_str()) == 0)
        modeCmd(spl, client);
    else if (strcmp("KILL", spl[0].c_str()) == 0)
        handleKillCmd(client, spl);
    else if (strcmp("LIST", spl[0].c_str()) == 0)
        handleListCmd(client, spl);
    else if (strcmp("NAMES", spl[0].c_str()) == 0)
        handleNamesCmd(client, spl);
    else if (strcmp("INVITE", spl[0].c_str()) == 0)
        ft_inviteCmd(client, spl);
    else if (strcmp("KICK", spl[0].c_str()) == 0)
        ft_kickCmd(client, spl, buffer);
    else if (strcmp("TOPIC", spl[0].c_str()) == 0)
        handleTopicCmd(client, spl);
    else if (strcmp("VERSION", spl[0].c_str()) == 0)
        handleVersionCmd(client, spl);
    else if (strcmp("HELP", spl[0].c_str()) == 0)
        handleHelpCmd(client);
    else if (strcmp("TIME", spl[0].c_str()) == 0)
        handleTimeCmd(client);
    else if (strcmp("LUSER", spl[0].c_str()) == 0)
        handleLusersCmd(client);
    else if (strcmp("LOGTIME", spl[0].c_str()) == 0)
        handleLogTime(client);
    else if (strcmp("DOWNLOAD", spl[0].c_str()) == 0)
        sendFile(client, spl);
    else if (strcmp("PONG", spl[0].c_str()) == 0)
        ;
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
        // pass.erase(pass.size() - 1, 1);
        if (strcmp(pass.c_str(), _passwd))
            ft_print_error("PASS", ERR_PASSWDMISMATCH, client);
        else if (client.getPass())
            ft_print_error("PASS", ERR_ALREADYREGISTRED, client);
        else
        {
            client.setPass(true);
            client.loginMessage();
        }
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
        if (client.getNickName() == "")
        {
            client.loginMessage();
        }
        if (ft_isregister(client))
        {
            std::string msg = ":" + client.getNickName() + "!~@localhost NICK :" + cmds[1] + "\n";
            send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
        }
        client.setNickName(cmds[1]);
        ft_updateNickInChanls(client);
    }
};

void Server::handleUserCmd(Client &client, std::vector<std::string> cmds, char *buffer)
{
    if (cmds.size() < 5)
        ft_print_error("USER", ERR_NEEDMOREPARAMS, client);
    else if (!client.getUserName().empty())
        ft_print_error("USER", ERR_ALREADYREGISTRED, client);
    else if (isNickUserDuplicate(cmds[1]))
        ft_print_error(cmds[1], ERR_NICKNAMEINUSE, client);
    else
    {

        client.setUserName(cmds[1]);
        if (strcmp("*", cmds[2].c_str()) == 0)
        {
            char hostname[256];
            gethostname(hostname, sizeof(hostname));
            client.setHostName(hostname);
        }
        else
            client.setHostName(cmds[2]);
        if (strcmp("*", cmds[3].c_str()) == 0)
            client.setServerName(inet_ntoa(client.getClientAddr().sin_addr));
        else
            client.setServerName(cmds[3]);
        if (cmds[4][0] == ':')
        {
            std::string realnm = buffer + std::strlen((cmds[1] + cmds[2] + cmds[3]).c_str()) + 9;
            client.setRealName(realnm);
        }
        else
            client.setRealName(cmds[4]);
        client.loginMessage();
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
            if (clts[k][0] != '#' && clts[k][0] != '&')
            {

                int fd = ft_isUserExist(clts[k], _clients);
                if (fd == -1)
                    ft_print_error(cmds[k], ERR_NOSUCHNICK, client);
                else if (_clients[fd].isRegistered() == false)
                    ft_print_error(cmds[k], ERR_NOSUCHNICK, client);
                else
                {
                    std::string msg;
                    msg = ":" + client.getNickName() + "!" + client.getUserName() + "@127.0.0.1 PRIVMSG " + _clients[fd].getNickName();
                    if (cmds[2][0] != ':')
                        msg = msg + " :" + cmds[2] + "\n";
                    else
                        msg = msg + " " + strchr(buffer, ':') + "\n";
                    send(_clients[fd].getFd(), msg.c_str(), strlen(msg.c_str()), 0);
                }
            }
            else
            {
                int fd = ft_isChannelExist(clts[k], _channels);
                if (fd == -1)
                    ft_print_error(cmds[k], ERR_NOSUCHNICK, client);
                else
                {
                    if (_channels[fd].getModes().noOutsideMsg == true && _channels[fd].is_userInChannel(client) == -1)
                        ft_print_error(_channels[fd].get_chanlName(), ERR_NOTONCHANNEL, client);
                    else
                    {
                        std::string msg;
                        msg = ":" + client.getNickName() + "!" + client.getUserName() + "@127.0.0.1 PRIVMSG " + _channels[fd].get_chanlName();
                        if (cmds[2][0] != ':')
                            msg = msg + " :" + cmds[2] + "\n";
                        else
                            msg = msg + " " + strchr(buffer, ':') + "\n";
                        for (size_t l = 0; l < _channels[fd].get_chanlUsers().size(); l++)
                        {
                            if (_channels[fd].get_chanlUsers()[l].getFd() != client.getFd())
                                send(_channels[fd].get_chanlUsers()[l].getFd(), msg.c_str(), strlen(msg.c_str()), 0);
                        }
                    }
                }
            }
        }
    }
};

// NOTICE
void Server::handleNoticeCmd(Client &client, std::vector<std::string> cmds, char *buffer)
{
    if (cmds.size() == 1)
        ;
    else if (cmds.size() == 2)
        ;
    else
    {
        std::vector<std::string> clts = ft_split(cmds[1], ',');
        for (size_t k = 0; k < clts.size(); k++)
        {
            if (clts[k][0] != '#' && clts[k][0] != '&')
            {

                int fd = ft_isUserExist(clts[k], _clients);
                if (fd == -1)
                    ;
                else if (_clients[fd].isRegistered() == false)
                    ;
                else
                {
                    std::string msg;
                    msg = ":" + client.getNickName() + "!" + client.getUserName() + "@127.0.0.1 NOTICE " + _clients[fd].getNickName();
                    if (cmds[2][0] != ':')
                        msg = msg + " :" + cmds[2] + "\n";
                    else
                        msg = msg + " " + strchr(buffer, ':') + "\n";
                    send(_clients[fd].getFd(), msg.c_str(), strlen(msg.c_str()), 0);
                }
            }
            else
            {
                int fd = ft_isChannelExist(clts[k], _channels);
                if (fd == -1)
                    ;
                else
                {
                    if (_channels[fd].getModes().noOutsideMsg == true && _channels[fd].is_userInChannel(client) == -1)
                        ;
                    else
                    {
                        std::string msg;
                        msg = ":" + client.getNickName() + "!" + client.getUserName() + "@127.0.0.1 NOTICE " + _channels[fd].get_chanlName();
                        if (cmds[2][0] != ':')
                            msg = msg + " :" + cmds[2] + "\n";
                        else
                            msg = msg + " " + strchr(buffer, ':') + "\n";
                        for (size_t l = 0; l < _channels[fd].get_chanlUsers().size(); l++)
                        {
                            if (_channels[fd].get_chanlUsers()[l].getFd() != client.getFd())
                                send(_channels[fd].get_chanlUsers()[l].getFd(), msg.c_str(), strlen(msg.c_str()), 0);
                        }
                    }
                }
            }
        }
    }
};
// ================================================
// Channel COMMANDS
// ================================================

void Server::ft_joinCmd(Client &client, std::vector<std::string> cmds)
{
    if (cmds.size() == 1)
        ft_print_error("JOIN", ERR_NEEDMOREPARAMS, client);
    else if (cmds[1][0] == '0' && atoi(cmds[1].c_str()) == 0)
        eraseUserFromChannels(client);
    else
    {
        std::vector<std::string> chanls;
        std::vector<std::string> chanlsPass;
        chanls = ft_split(cmds[1], ',');
        if (cmds.size() >= 3)
            chanlsPass = ft_split(cmds[2], ',');
        for (size_t l = 0; l < chanls.size(); l++)
        {
            if (!is_validChannel(chanls[l]))
            {
                ft_print_error(chanls[l], ERR_NOSUCHCHANNEL, client);
                continue;
            }
            int indx = is_channel_Exit(_channels, chanls[l]);
            std::string key;
            if (!cmds[2].empty() && l < chanlsPass.size())
                key = chanlsPass[l];
            if (indx == -1)
            {
                Channel channel;
                channel.set_chanlName(chanls[l]);
                if (!cmds[2].empty() && l < chanlsPass.size())
                {
                    channel.setModes('k', true);
                    channel.set_chanlPass(key);
                }
                if (cmds[2][0] == '&')
                    channel.setInvitOnly(true);
                channel.add_user(client);
                channel.add_Operator(client);
                channel.setCreator(client.getFd());
                _channels.push_back(channel);
                std::vector<std::string> temp;
                temp.push_back("NAMES");
                temp.push_back(chanls[l]);
                handleNamesCmd(client, temp);
            }
            else
            {
                if (_channels[indx].getInvitOnly() == true)
                    ft_print_error(_channels[indx].get_chanlName(), ERR_INVITEONLYCHAN, client);
                else
                {
                    std::cout << _channels[indx].getLimit() << " - " << (int)_channels[indx].get_chanlUsers().size() << "\n";
                    if (_channels[indx].getModes().limit && _channels[indx].getLimit() <= (int)_channels[indx].get_chanlUsers().size())
                        ft_print_error(_channels[indx].get_chanlName(), ERR_CHANNELISFULL, client);
                    else if (_channels[indx].is_userInChannel(client) == -1)
                    {
                        if (_channels[indx].get_chanlPass().empty() || _channels[indx].get_chanlPass() == key)
                        {
                            _channels[indx].add_user(client);
                            std::vector<std::string> temp;
                            temp.push_back("NAMES");
                            temp.push_back(_channels[indx].get_chanlName());
                            handleNamesCmd(client, temp);
                        }
                        else
                            ft_print_error(_channels[indx].get_chanlName(), ERR_BADCHANNELKEY, client);
                    }
                }
            }
        }
    }
};

void Server::handleListCmd(Client &client, std::vector<std::string> cmds)
{
    ft_print_error("LIST", RPL_LISTSTART, client);
    if (cmds.size() == 1)
    {
        for (size_t i = 0; i < _channels.size(); i++)
        {
            std::string msg = ":@localhost " + std::to_string(RPL_LIST) + " " +
                              client.getNickName() + " " + _channels[i].get_chanlName() + " " +
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
                    std::string msg = ":@localhost " + std::to_string(RPL_LIST) + " " +
                                      client.getNickName() + " " + _channels[i].get_chanlName() + " " +
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

            allUsers += _channels[i].getallUsers(allUsers, _clients);
        std::string msg = ":@localhost " + std::to_string(RPL_NAMREPLY) + " " +
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
                    std::string tmp = "";
                    std::string msg = ":@localhost " + std::to_string(RPL_NAMREPLY) + " " +
                                      client.getNickName() + " = " + _channels[i].get_chanlName() + " :" + _channels[i].getallUsers(tmp, _clients) + "\n";

                    send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
                }
            }
        }
        ft_print_error(" " + allChanls, RPL_ENDOFNAMES, client);
    }
}

void Server::handleTopicCmd(Client &client, std::vector<std::string> cmds)
{
    if (cmds.size() < 2)
        ft_print_error("TOPIC", ERR_NEEDMOREPARAMS, client);
    else
    {
        for (size_t i = 0; i < _channels.size(); i++)
        {
            if (_channels[i].get_chanlName() == cmds[1] && cmds.size() == 2)
            {
                if (_channels[i].getChannelTopic() == "")
                    ft_print_error(_channels[i].get_chanlName(), RPL_NOTOPIC, client);
                else
                {
                    std::string msg = ":@localhost " + std::to_string(RPL_TOPIC) + " " +
                                      client.getNickName() + " " + _channels[i].get_chanlName() + " :" + _channels[i].getChannelTopic() + "\n";
                    send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
                }
                return;
            }
            if (_channels[i].get_chanlName() == cmds[1] && cmds.size() > 2)
            {
                // check if user in channel
                if (_channels[i].is_userInChannel(client) == -1)
                {
                    ft_print_error(_channels[i].get_chanlName(), ERR_NOTONCHANNEL, client);
                    return;
                }

                // check if user is a channel operator
                if (_channels[i].getModes().topic && (_channels[i].ft_isOperator(client) == false))
                {
                    ft_print_error(_channels[i].get_chanlName(), ERR_CHANOPRIVSNEEDED, client);
                    return;
                }

                // change channel topic
                std::string chnlTopic = "";
                if (cmds.size() == 2 || (cmds.size() > 2 && cmds[2][0] != ':'))
                {
                    chnlTopic = cmds[2];
                }
                else if (cmds.size() > 2 && cmds[2][0] == ':')
                {
                    for (size_t i = 2; i < cmds.size(); i++)
                    {
                        if (i == 2 && cmds[2][0] == ':')
                            cmds[2].erase(0, 1);
                        if (i > 2)
                            chnlTopic += " ";
                        chnlTopic += cmds[i];
                    }
                }
                if (cmds.size() > 2 && chnlTopic[0] == ':')
                    chnlTopic.erase(0, 1);
                _channels[i].setChannelTopic(chnlTopic);
                std::string msg = ":@localhost " + std::to_string(RPL_TOPIC) + " TOPIC " +
                                  _channels[i].get_chanlName() + " :" + _channels[i].getChannelTopic() + "\n";
                send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
                return;
            }
        }
        ft_print_error(cmds[1], ERR_NOSUCHCHANNEL, client);
    }
}

// ================================================
// OPERATOR COMMANDS
// ================================================

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
            if (client.getHostName() != "")
            {
                client.setOper(true);
                ft_print_error("OPER", RPL_YOUREOPER, client);
            }
            else
                ft_print_error("OPER", ERR_NOOPERHOST, client);
        }
    }
};

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
                    std::string reason = "";
                    for (size_t i = 2; i < cmds.size(); i++)
                    {
                        if (i > 2)
                            reason += " ";
                        reason += cmds[i];
                    }
                    std::string msg = ":@localhost " + std::to_string(001) + " KILL :you have been killed by @" + client.getNickName() + " because: " + reason + "\n";
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

void Server::handleVersionCmd(Client &client, std::vector<std::string> cmds)
{
    if (cmds.size() == 1)
    {
        ft_print_error(_serverName, RPL_VERSION, client);
    }
    else if (cmds.size() > 1)
    {
        std::string servName = "";
        for (size_t i = 1; i < cmds.size(); i++)
        {
            servName += cmds[i];
            if (i != cmds.size() - 1)
                servName += " ";
        }
        if (servName == _serverName)
            ft_print_error(servName, RPL_VERSION, client);
        else
            ft_print_error(servName, ERR_NOSUCHSERVER, client);
    }
}

void Server::handleHelpCmd(Client &client)
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
    helpmsg.append("-Send message Commands:\n");
    helpmsg.append(RESET);
    helpmsg.append("\tPRIVMSG <receiver>{,<receiver>} <text to be sent> : send a message to a user or a channel\n");
    helpmsg.append("\tNOTICE <nickname> <text> : send a notice to a user\n");

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

    helpmsg.append(YELLOW);
    helpmsg.append("-Server Informations Commands:\n");
    helpmsg.append(RESET);
    helpmsg.append("\tLUSERS [<mask> [<target>]] : get the number of users\n");
    helpmsg.append("\tHELP : to get infos about commands used in the server.\n");
    helpmsg.append("\tVERSION [<server>]: is used  to  query  the  version  of  the  server program.\n");
    helpmsg.append("\tTIME : is used to query local time from the specified server.\n");

    helpmsg.append(YELLOW);
    helpmsg.append("-Other commands:\n");
    helpmsg.append(RESET);
    helpmsg.append("\tQUIT [<Quit message>] : A client session is ended with a quit message.\n");

    send(client.getFd(), helpmsg.c_str(), helpmsg.size(), 0);
}

void Server::handleTimeCmd(Client &client)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    struct tm *tm = localtime(&t.tv_sec);
    std::string msg = ":@localhost " + std::to_string(RPL_TIME) + " Time is :";
    msg.append(asctime(tm));
    send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}

void Server::handleLusersCmd(Client &client)
{
    std::string msg = ":@localhost " + std::to_string(001) + client.getNickName() + " LUSER :server contain " + std::to_string(_clients.size()) + " users.\n";
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
            std::string msg = ":@localhost " + std::to_string(001) + " " + client.getNickName() + " :you quit the server.\n";
            send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
            close(client.getFd());
            break;
        }
    }
}

void Server::handleLogTime(Client &client)
{
    long currentTime;

    currentTime = get_time();
    double minutes = (double)((currentTime - client.getStartTime())) / 60000.0;

    // Set precision to 3
    std::ostringstream oss;
    oss << std::setprecision(2) << minutes;
    std::string x_str = oss.str();

    std::string msg = ":@localhost " + std::to_string(001) + " " + client.getNickName() + " LOGTIME :" + x_str + " minutes\n";
    send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}
