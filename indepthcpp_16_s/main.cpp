#include <iostream>
#include <string>
#include "server.hpp"

void TestServer()
{
    boost::asio::io_service ios;

    //boost::system::io_service::work work(ios);
    //std::thread thd( [&ios] { ios.run(); })

    Server server(ios, 9900);
    server.accept();
    ios.run();

    // thd.join();
}

int main(int argc, char* argv[])
{
    TestServer();
    return 0;
}
