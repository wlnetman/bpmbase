#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include <string>
#include <thread>
#include <chrono>

#include <boost/asio.hpp>
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost;

#include "rwhandler.h"

class Connector
{
public:
    Connector(io_service& ios,const std::string strIP, short port) :
        ios_(ios), socket_( ios ),
        server_addr_( tcp::endpoint( address::from_string(strIP), port)),
        is_connected_( false),
        chk_thread_(nullptr)
    {
        create_event_handler(ios);
    }

    ~Connector() {}

    bool start()
    {
        event_handler_->get_socket().async_connect( server_addr_,
                                                    [this] ( const boost::system::error_code& error)
        {
            if( error )
            {
                handle_connect_error(error);
                return;
            }

            std::cout<< "connect ok" << std::endl;

            is_connected_ = true;
            event_handler_->handle_read();
        });

        return is_connected_;
    }

    bool is_connected() const
    {
        return is_connected_;
    }

    void send(char* data, int len)
    {
        if( !is_connected_ )
            return;
        event_handler_->handle_write(data, len);
    }

private:
    void create_event_handler(io_service& ios)
    {
        event_handler_ = std::make_shared<RWHandler> (ios);
        event_handler_->set_callback_error( [this] (int connid)
                                            { HandleRWError(connid); });
    }

    void check_connect()
    {
        if( chk_thread_ != nullptr )
            return;

        chk_thread_ = std::make_shared<std::thread>( [this]
                        {
                            while (true)
                            {
                                if( is_connected() )
                                    start();

                                std::this_thread::sleep_for(std::chrono::seconds(1));
                            }
                        });
    }

    void handle_connect_error( const boost::system::error_code& error)
    {
        is_connected_ = false;
        std::cout << error.message() << std::endl;
        event_handler_->close_socket();
        check_connect();
    }

    void HandleRWError(int connid)
    {
        is_connected_ = false;
        check_connect();
    }

private:
    io_service& ios_;
    tcp::socket socket_;
    tcp::endpoint server_addr_;
    std::shared_ptr<RWHandler> event_handler_;
    bool is_connected_;
    std::shared_ptr<std::thread> chk_thread_;
};

#endif // CONNECTOR_HPP
