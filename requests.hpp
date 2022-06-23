#pragma once
#include "socket.hpp"
static const uint16_t PORT = 80;
static const std::string LF = "\r\n";
static const std::string SP = " ";
static const std::string HEADER_SEP = ": ";
static const std::string PROTOCOL_SEP = "://";
static const std::string HTTP_1_1 = "http/1.1";
static const std::string GET = "get";
static const std::string POST = "post";

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

    void get(std::string url, const std::vector<std::pair<std::string, std::string>> &params = {}, const std::vector<std::pair<std::string, std::string>> &headers = {}, const std::vector<std::pair<std::string, std::string>> &data = {})
    {
        ParseUrl(url);
        ParseRequestLine(GET, params); // 构建请求行 eg: get / http/1.1
        ParseRequestHeader(headers);   // 构建请求报头
        ParseRequestBody(data);        // 构建请求体
        ParseRequest();                // 构建请求报文
        Send();
        Recv();
    }

    void post() {}

    const std::string &text()
    {
        return _text;
    }
    const std::string &raw()
    {
        return _response;
    }
    const std::string &status_code()
    {
        return _status_code;
    }
    const std::string &headers()
    {
        return _response_headers;
    }

private:
    void Recv()
    {
    }
    void Send()
    {
        // 解析ip
        std::string ip = Socket::ParseIpByDomain(_domain);
        if (Socket::Connect(_sock, ip, PORT) == true)
        {
            ssize_t size = send(_sock, _reuqest.c_str(), _reuqest.size(), 0);
            if (size < 0)
            {
                // error
            }
        }
        else
        {
        }
    }

    void ParseRequestLine(const std::string &method, const std::vector<std::pair<std::string, std::string>> &params)
    {
        _request_line += method;
        _request_line += SP;
        _request_line += _path;
        _request_line += SP;
        _request_line += HTTP_1_1;
        if (!params.empty())
        {
            // get / http/1.1
            // 请求行有参数
            _request_line += '?';
            for (const auto &kv : params)
            {
                std::string key = kv.first;
                std::string value = kv.second;
                std::string query;
                query += key;
                query += '=';
                query += value;
                query += '&';
                _request_line += query;
            }
            _request_line.pop_back();
            _request_line += LF;
        }
        else
        {
            // 请求行无参数
            _request_line += LF;
        }
        _params = std::move(params);
    }

    void ParseRequestHeader(const std::vector<std::pair<std::string, std::string>> &headers)
    {
        if (!headers.empty())
        {
            for (const auto &kv : headers)
            {
                std::string key = kv.first;
                std::string value = kv.second;
                _request_line += key;
                _request_line += HEADER_SEP;
                _request_line += value;
                _request_line += LF;
            }
        }
        _headers = std::move(headers);
    }

    void ParseRequestBody(const std::vector<std::pair<std::string, std::string>> &data)
    {
        if (!data.empty())
        {
        }
    }

    void ParseRequest()
    {
        _reuqest += _request_line;
        _reuqest += _request_header;
        _reuqest += _request_space_line;
        _reuqest += _request_body;
    }

    void ParseUrl(const std::string url)
    {
        // http://www.xxx.com
        // http://www.xxx.com/
        // www.xxx.com
        // www.xxx.com/a/b
        // 先找 ://
        size_t start = url.find(PROTOCOL_SEP);
        if (start == std::string::npos)
        {
            start = 0;
        }
        else
        {
            start += PROTOCOL_SEP.size();
        }
        size_t end = url.find('/');
        size_t len = 0;
        if (end == std::string::npos)
        {
            _domain = url.substr(start);
            _path = "/";
        }
        else
        {
            len = end - start;
            _domain = url.substr(start, len);
            _path = url.substr(end);
        }
        _url = std::move(url);
    }

private:
    int _sock;
    std::string _url;                                          // 请求url地址
    std::string _domain;                                       // 请求域名
    std::string _path;                                         // 请求路径
    std::string _reuqest;                                      // 请求
    std::vector<std::pair<std::string, std::string>> _params;  // 请求报头字典
    std::vector<std::pair<std::string, std::string>> _headers; // 请求报头字典
    std::vector<std::pair<std::string, std::string>> _data;    // 请求行参数字典
    std::string _request_line;                                 // 请求行
    std::string _request_header;                               // 请求报头
    std::string _request_space_line = LF;                      // 空行
    std::string _request_body;                                 // 请求体

    std::string _response;         // 响应报文
    std::string _response_line;    // 响应行
    std::string _status_code;      // 响应状态码
    std::string _response_headers; // 响应报头
    std::string _text;             // 响应体
};