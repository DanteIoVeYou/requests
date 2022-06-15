#pragma once
#include "socket.hpp"

class requests
{
public:
    requests() {}
    ~requests() {}
    void get() {}
    void post() {}

private:
    std::string _url;                                     // url 地址
    std::unordered_map<std::string, std::string> _data;   // url参数
    std::unordered_map<std::string, std::string> _header; // 请求报头
};