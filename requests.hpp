#pragma once
#include "socket.hpp"
static const std::string LF = "\r\n";
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
    void get(std::string url, const std::vector<std::pair<std::string, std::string>> &data = {}, const std::vector<std::pair<std::string, std::string>> &header = {})
    {
        ParseRequestLine(url);      // 构建请求行 eg: get / http/1.1
        ParseRequestHeader();       // 构建请求报头
        ParseRequest(data, header); // 构建请求报文
        Send();
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
    void Send()
    {
        // 解析ip
        std::string ip = Socket::ParseIpByDomain(_url);
    }
    void ParseRequestLine(std::string url)
    {
    }
    void ParseRequestHeader(const std::vector<std::pair<std::string, std::string>> &data, const std::vector<std::pair<std::string, std::string>> &header)
    {
    }
    ParseRequest(); // 构建请求报文

private:
    int _sock;
    std::string _url;         // 请求url地址
    std::string _data;        // 请求行
    std::string _header;      // 请求报头
    std::string _raw;         // 响应报文
    std::string _line;        // 响应行
    std::string _status_code; // 响应状态码
    std::string _headers;     // 响应报头
    std::string _text;        // 响应体
};