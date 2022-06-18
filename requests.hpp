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

    const std::string &text()
    {
        return _text;
    }
    const std::string &raw()
    {
        return _raw;
    }
    const std::string &status_code()
    {
        return _status_code;
    }
    const std::string &headers()
    {
        return _headers;
    }

private:
    int _sock;
    std::string _url;                                         // 请求url地址
    std::vector<std::pair<std::string, std::string>> _data;   // 请求url参数
    std::vector<std::pair<std::string, std::string>> _header; // 请求报头
    std::string _raw;                                         // 响应报文
    std::string _line;                                        // 响应行
    std::string _status_code;                                 // 响应状态码
    std::string _headers;                                     // 响应报头
    std::string _text;                                        // 响应体
};