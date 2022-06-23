#pragma once
#include "common.hpp"

class Socket
{
public:
    static int Create()
    {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            // TODO
        }
        else
        {
            return sock;
        }
    }

    static bool Connect(int fd, std::string ip, uint16_t port)
    {
        struct sockaddr_in peer;
        bzero(&peer, sizeof(peer));
        peer.sin_family = AF_INET;
        peer.sin_port = htons(port);
        peer.sin_addr.s_addr = inet_addr(ip.c_str());
        int ret = connect(fd, (struct sockaddr *)&peer, sizeof(peer));
        if (ret < 0)
        {
            // TODO
            return false;
        }
        return true;
    }

    static std::string ParseIpByDomain(std::string url)
    {
        struct hostent *host = gethostbyname(url.c_str());
        if (!host)
        {
            // Error
        }
        else
        {
            if (!host->h_addr_list[0])
            {
                // Cannot get ip
            }
            else
            {
                return inet_ntoa(*(struct in_addr *)host->h_addr_list[0]);
            }
        }
    }
};