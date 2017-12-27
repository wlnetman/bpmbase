#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include <boost/asio.hpp>
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost;

#include "connector.hpp"

int main(int argc, char* argv[])
{
    io_service ios;
    io_service::work work(ios);
    //std::thread thd( [&ios] { ios.run(); });

    Connector conn(ios, "127.0.0.1", 9900);
    conn.start();

    //std::istringstream str;
    std::string str;
    if( !conn.is_connected() )
    {
        std::cin >> str;
        return -1;
    }

    const int len  = 512;
    char line[len] = "";

    while( std::cin >> str )
    {
        char header[HEAD_LEN] = {};
        int total_len = str.length() + 1, HEAD_LEN;
        std::sprintf(header, "%d", total_len);
        std::memcpy(line, header, HEAD_LEN);
        std::memcpy(line + HEAD_LEN, str.c_str(), str.length() + 1);
        conn.send(line, total_len);
    }

    return 0;
}
