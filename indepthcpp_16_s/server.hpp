#ifndef SERVER
#define SERVER

#include <boost/asio/buffer.hpp>
#include <unordered_map>
#include <numeric>
#include <list>
#include "Message.hpp"
#include "rwhandler.h"

const int MaxConnectionNum = 65536;
const int MaxRecvSize = 65536;

class Server
{
public:
    Server(io_service& ios, short port) : ios_(ios),
        acceptor_(ios, tcp::endpoint(tcp::v4(), port)),
        cnnid_pool_(MaxConnectionNum)
    {
        cnnid_pool_.resize(MaxConnectionNum);
        std::iota(cnnid_pool_.begin(), cnnid_pool_.end(), 1);
    }

    ~Server()
    {
    }

    void accept()
    {
        std::cout<< "Start Listening... " << std::endl;
        std::shared_ptr<RWHandler> handler = create_handler();

        acceptor_.async_accept(handler->get_socket(),
                               [this, handler](const boost::system::error_code& error)
        {
            if( error )
            {
                std::cout<< error.value() << " " << error.message() << std::endl;
                handle_acp_error(handler, error);
                return;
            }

            handlers_.insert(std::make_pair(handler->get_connId(), handler));
            std::cout<< "current connect count: " << handlers_.size() << std::endl;

            handler->handle_read();
            accept();
        });
    }

private:
    void handle_acp_error(std::shared_ptr<RWHandler> eventHandler,
                          const boost::system::error_code error)
    {
        std::cout << "Error, erros reason: " << error.value()
                  << error.message() << std::endl;
        eventHandler->close_socket();
        stop_accept();
    }

    void stop_accept()
    {
        boost::system::error_code ec;
        acceptor_.cancel(ec);
        acceptor_.close(ec);
        ios_.stop();
    }

    std::shared_ptr<RWHandler> create_handler()
    {
        int connId = cnnid_pool_.front();
        cnnid_pool_.pop_front();
        std::shared_ptr<RWHandler> handler = std::make_shared<RWHandler> (ios_);

        handler->set_connId(connId);

        handler->set_callback_error( [this] (int connId)
                                        {
                                           recycl_connid(connId);
                                        });

        return handler;
    }

    void recycl_connid(int connId)
    {
        auto it = handlers_.find(connId);
        if( it != handlers_.end() )
            handlers_.erase(it);
        std::cout<< "current connect count " << handlers_.size() << std::endl;
        cnnid_pool_.push_back(connId);
    }

private:
    io_service& ios_;
    tcp::acceptor acceptor_;
    std::unordered_map<int, std::shared_ptr<RWHandler>> handlers_;
    std::list<int> cnnid_pool_;
};


#endif // SERVER
