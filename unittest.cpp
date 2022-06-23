// #include "requests.hpp"
#include "socket.hpp"
int main()
{
    std::cout << Socket::ParseIpByDomain("www.baidu.com") << std::endl;
    return 0;
}