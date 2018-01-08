#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <memory>

#include "fmt/format.h"
#include "utils/strutil.h"
#include "utils/timeutil.h"
#include "utils/logging.h"
#include "marketcollection.h"

void MarketCollection::set_symbol(const std::string &symbols)
{
    auto all = StrUtil::split( symbols, ";");
    for( auto item : all)
    {
        symbols_.push_back(item);
    }
    LOG(INFO)<< "set symbol: " << symbols << "\n";
}

void MarketCollection::set_main_symbol(const std::string &symbol)
{
    main_symbol_ = symbol;
    LOG(INFO)<< "set main symbol: " << main_symbol_ << "\n";
}

void MarketCollection::set_user(const std::string& broker,
                                const std::string& userid,
                                const std::string &password)
{
    broker_    = broker;
    userid_    = userid;
    password_  = password;

    LOG(INFO)<< "set user: " << broker << " userid: " << userid << "\n";
}

void MarketCollection::OnFrontConnected()
{
    LOG(INFO)<< "OnFrontConnected\n";

    do_login();
}

void MarketCollection::do_login()
{
    CThostFtdcReqUserLoginField req;
    std::memset(&req, 0, sizeof(req));
    std::memcpy(&req.BrokerID, broker_.c_str(), broker_.length());
    std::memcpy(&req.UserID, userid_.c_str(), userid_.length());
    std::memcpy(&req.Password, password_.c_str(), password_.length());

    int nRequestId = 0;
    // TODO:异常处理
    if( api_ )
        api_->ReqUserLogin( &req, nRequestId);
}

void MarketCollection::OnFrontDisconnected(int nReason)
{
    LOG(INFO)<< "OnFrontDisconnected\n";
}

// 登录请求响应
void MarketCollection::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                    CThostFtdcRspInfoField *pRspInfo,
                    int nRequestId, bool bIsLast)
{
    LOG(INFO)<< "OnRspUserLogin" << nRequestId << std::endl;

    do_subscribe();
}

void MarketCollection::do_subscribe()
{
    if( api_ == nullptr || symbols_.empty()) {
        std::cout<< "Cannot subscribe" << std::endl;
        return;
    }

    // easyctp是每一个发送一次订阅请求
    for( auto &item : symbols_) {
        std::cout<< item << std::endl;
        std::string &symble = item;
        char *instrument[1] = {(char*)symble.c_str()};
        api_->SubscribeMarketData( instrument, 1);
        LOG(INFO)<< "subscribe: " << item;
    }
    //delete []instrument;    
}

// 订阅行情应答
void MarketCollection::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                        CThostFtdcRspInfoField *pRspInfo,
                        int nRequestID, bool bIsLast)
{
    //LOG(INFO)<< "OnRspSubMarketData " << nRequestID << "\n";
}

void MarketCollection::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                          CThostFtdcRspInfoField *pRspInfo,
                          int nRequestID, bool bIsLast)
{
    LOG(INFO)<< "OnRspUnSubMarketData " << nRequestID << "\n";
}

void MarketCollection::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestId, bool bIsLast)
{
    LOG(INFO)<< "OnRspError: " << nRequestId << "\n";
}


void MarketCollection::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pData)
{
    //LOG(INFO)<< "OnRtnDepthMarketData: " << pData->InstrumentID;

    bool subscribe = false;
    // 1,第一条数据
    for( auto item : symbols_){
        if( std::strcmp(pData->InstrumentID, item.c_str()) == 0 ) {
            do_collect_tick(pData);
            subscribe = true;
        }
    }
    // 2,不在symbols中错误的数据
    if( !subscribe )
        LOG(ERROR) << " Error DepthMarketData\n";

    // 3, 收到主力合约后，通知可以计算指数
    if( std::strcmp(main_symbol_.c_str(), pData->InstrumentID) == 0){
        //LOG(INFO)<< "notify calc index";
        simple_queue_.notify_get();
    }
}

void MarketCollection::do_collect_tick(CThostFtdcDepthMarketDataField *pData)
{
    //std::shared_ptr<TickData> tick = std::make_shared<TickData>();
    TickData tick;

    //pData->UpdateMillisec;  // int
    std::string str_time = pData->ActionDay;
    str_time += pData->UpdateTime;
    tick.actionDatetime = bpm_str2ctime(str_time.c_str(), "%Y %m %d %HH:%MM:%ss");

    std::strcpy(tick.symbol, pData->InstrumentID);

    tick.lastPrice     = pData->LastPrice;
    tick.openPrice     = pData->OpenPrice;
    tick.highPrice     = pData->HighestPrice;
    tick.lowPrice      = pData->LowestPrice;
    tick.preClosePrice = pData->PreClosePrice;
    tick.openInterest  = pData->OpenInterest;
    tick.volume        = pData->Volume;

    // 调试信息
    std::string tick_line;
    tick_line = fmt::format("{} {} {} {}",
                            pData->ActionDay,
                            pData->UpdateTime,
                            tick.symbol,
                            tick.lastPrice);
                            //tick.openPrice,
                            //tick.highPrice,
                            //tick.lowPrice,
                            //tick.preClosePrice,
                            //tick.openInterest,
                            //tick.volume);
    //std::cout<< tick_line << std::endl;
    LOG(INFO)<< tick_line;

    simple_queue_.put(tick.symbol, tick);
}

double MarketCollection::calc_index(std::vector<TickData>& tick)
{
    double total_openInterest = 0.0;
    double prices_scale = 0.0;
    for( const auto& i : tick ){
        total_openInterest += i.openInterest;
        prices_scale += i.lastPrice * i.openInterest;
    }
    return  prices_scale / total_openInterest;
}

void MarketCollection::queue_save()
{
    LOG(INFO)<< "queue save thread : "
             << std::this_thread::get_id() << "\n";

    while ( !exit_ ) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        std::vector<TickData> tick;
        simple_queue_.get( tick );
        double rb8888 = calc_index(tick);
        LOG(INFO)<< "rb8888" << " ["<< static_cast<int>(rb8888) << "]";
    }
    LOG(INFO)<< "queue save exit \n";
}

// 废弃
void MarketCollection::OnHeartBeatWarning(int nTimeLapse)
{
}
