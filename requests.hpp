#pragma once
#include "socket.hpp"

class requests
{
public:
    requests()
    {
        _sock = Socket::Create();
    }
    ~requests()
    {
        close(_sock);
    }
    void get(std::string url, std::vector<std::pair<std::string, std::string>> data = {}, std::vector<std::pair<std::string, std::string>> header = {})
    {
        _data = std::move(data);
        _header = std::move(header);
        
    }
    void post() {}

private:
    int _sock;
    std::string _url;                                         // url 地址
    std::vector<std::pair<std::string, std::string>> _data;   // url参数
    std::vector<std::pair<std::string, std::string>> _header; // 请求报头
};