#ifndef RWHANDLER_H
#define RWHANDLER_H

#include <array>
#include <functional>
#include <iostream>
#include <memory>
using namespace std;

#include <boost/asio.hpp>
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost;

#include "message.hpp"

const int MAX_IP_PACK_SIZE = 65536;
const int HEAD_LEN = 4;

class RWHandler : public std::enable_shared_from_this<RWHandler>
{
public:
    RWHandler(io_service& ios) : sock_(ios)
    {
    }

    ~RWHandler(){}

    void handle_read()
    {
        auto self = shared_from_this();

        async_read(sock_, buffer( read_msg_.data(), HEAD_LEN),
                   [this] (const boost::system::error_code& ec, size_t size)
                   {
                       if(ec != nullptr)
                       {
                           handle_error(ec);
                           return;
                       }
                       std::cout<< buffer_.data() + HEAD_LEN << std::endl;

                       read_body();
                   });
    }

    void read_body()
    {
        auto self = shared_from_this();
        async_read(sock_, buffer(read_msg_.data(), read_msg_.body_length()),
                   [this, self] (const boost::system::error_code& ec, size_t size)
                   {
                       if(ec != nullptr)
                       {
                           handle_error(ec);
                           return;
                       }
                       //std::cout<< buffer_.data() + HEAD_LEN << std::endl;
                       callback(read_msg_.data(), read_msg_.length());

                       handle_read();
                   });
    }

    void handle_write(char* data, int len)
    {
        boost::system::error_code ec;
        write(sock_, buffer(data, len), ec);
        if(ec != nullptr)
            handle_error(ec);
    }

    tcp::socket& get_socket()
    {
        return sock_;
    }

    void close_socket()
    {
        boost::system::error_code ec;
        sock_.shutdown(tcp::socket::shutdown_send, ec);
        sock_.close();
    }

    void set_connId(int connId)
    {
        conn_id_ = connId;
    }

    int get_connId()
    {
        return conn_id_;
    }

    template <typename F>
    void set_callback_error(F f)
    {
        callback_error_ = f;
    }

    // 完成的包
    void callback(char* pData, int len)
    {
        std::cout<< pData + HEAD_LEN << std::endl;
    }

private:
    void handle_error(const boost::system::error_code ec)
    {
        close_socket();
        std::cout<< ec.message() << std::endl;
        if( callback_error_ )
            callback_error_(conn_id_);
    }

private:
    tcp::socket sock_;
    std::array<char, MAX_IP_PACK_SIZE> buffer_;
    int conn_id_;
    std::function<void(int)> callback_error_;
    Message read_msg_;
};

#endif // RWHANDLER_H
