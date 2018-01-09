#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <memory>
#include <iostream>

#include "fmt/format.h"
#include "utils/strutil.h"
#include "utils/timeutil.h"
#include "utils/logging.h"
#include "marketcollection.h"
#include "tickdatadefine.h"

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
    LOG(INFO)<< "OnRspUserLogin";

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

static int g_rtn_batch = 0;

void MarketCollection::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pData)
{
    //LOG(INFO)<< "OnRtnDepthMarketData: " << pData->InstrumentID;

    // TODO: 检查数据有效性，1，交易时间，持仓量为0 ，错误数据
    push_depthdata_to_tickquque( pData );

    g_rtn_batch++;
    //LOG(INFO)<< g_rtn_batch;
}

//   DepthMarketDataField 转换为 TickData 后存入生产者队列
void MarketCollection::push_depthdata_to_tickquque(CThostFtdcDepthMarketDataField *pData)
{
    std::shared_ptr<TickData> tick = std::make_shared<TickData>();

    std::strcpy(tick->symbol, pData->InstrumentID);

    std::string str_time  = pData->ActionDay;
    str_time             += " ";
    str_time             += pData->UpdateTime;
    tick->actionDatetime  = bpm_str2ctime(str_time.c_str(), "%Y%m%d %H:%M:%S");
    tick->lastPrice       = pData->LastPrice;
    tick->openPrice       = pData->OpenPrice;
    tick->highPrice       = pData->HighestPrice;
    tick->lowPrice        = pData->LowestPrice;
    tick->preClosePrice   = pData->PreClosePrice;
    tick->openInterest    = pData->OpenInterest;
    tick->volume          = pData->Volume;

    producer_task_.put( tick );
}

bool MarketCollection::is_subscribe_symbol(const char* symbol)
{
    bool subscribe = false;
    for( auto item : symbols_) {
        if( std::strcmp( symbol, item.c_str()) == 0 ) {
            subscribe = true;
            break;
        }
    }

    if( !subscribe )
        LOG(ERROR) << "Error Tick" << symbol;

    return subscribe;
}

double MarketCollection::calc_index(TickVec& tick)
{
    double total_openInterest = 0.0;
    double prices_scale = 0.0;
    for( const auto& i : tick ){
        if(i->openInterest == 0 )
            continue; // 除0崩溃
        total_openInterest += i->openInterest;
        prices_scale += i->lastPrice * i->openInterest;
    }
    return  prices_scale / total_openInterest;
}

void MarketCollection::calc_index(const char* symbol)
{
    if( tick_mgr_.size() < symbols_.size() )
        return;

    // 是指定的主力合约
    if( is_main_symbol(symbol) ) {
        TickVec tmp_vec;
        for( const auto & item : tick_mgr_ ){
            // 取每个合约的最后一条记录
            tmp_vec.push_back( item.second->back() );
        }
        double rb8888 = calc_index( tmp_vec );
        LOG(INFO)<< "rb8888" << " ["<< static_cast<int>(std::ceil(rb8888)) << "]";
    }
}

void MarketCollection::consumer_thread()
{
    LOG(INFO)<< "consumer_thread : "
             << std::this_thread::get_id() << "\n";

    while ( !exit_ ) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::shared_ptr<TickData> tick = nullptr;
        producer_task_.get( tick );

        auto item = tick_mgr_.find(tick->symbol);
        if( item!= tick_mgr_.end() ){

            item->second->push_back( tick );
            //LOG(INFO)<< "push_back [" << tick->symbol << "] [count:" << item->second->size() << "]";

        } else {

            // 1, 检查是不是自己订阅的合约Tick
            if( !is_subscribe_symbol( tick->symbol ) )
                continue;

            // 2, 来了一个订阅的新合约，保存在对应的数组里面
            pTickVec vec = std::make_shared<TickVec>();
            //vec->resize( maxsize_tickvec_ );
            vec->push_back(tick);
            tick_mgr_[ std::string(tick->symbol) ] = vec;
        }

        // 保存tick到文件
        write_tick_to_file();

        // 计算指数
        calc_index(tick->symbol);
    }
    LOG(INFO)<< "queue save exit \n";
}

std::chrono::system_clock::time_point last_write = std::chrono::system_clock::now();
void MarketCollection::write_tick_to_file()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    if( std::chrono::duration_cast<std::chrono::seconds>( now - last_write).count() < 60 )
        return;

    last_write = now;

    // 隔段时间刷新一次到文件
    for( const auto& v : tick_mgr_){

        std::string fname;
        fname = fmt::format("C:\\temp\\tick\\{}-{}.txt",
                            v.first,
                            bpm_ctime2str( v.second->front()->actionDatetime,"%Y%m%d"));

        std::ofstream f( fname.c_str(), std::ofstream::out | std::ofstream::trunc ); // 隐含输出截断

        for( std::shared_ptr<TickData> tick : (*v.second) ){
            std::string s;
            s = fmt::format("{} {}.{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}\n",
                            tick->symbol,
                            bpm_ctime2str(tick->actionDatetime,"%H:%M:%S"),
                            tick->updateMs,
                            tick->lastPrice,
                            tick->volume,
                            tick->totalVolume,
                            tick->openInterest,
                            tick->askPrice,
                            tick->bidPrice,
                            tick->askVolume,
                            tick->bidVolume,
                            tick->openPrice,
                            tick->highPrice,
                            tick->lowPrice,
                            tick->preClosePrice,
                            tick->upperLimit,
                            tick->lowerLimit,
                            tick->averagePrice,
                            tick->settlementPrice,
                            tick->preSettlementPrice);
            //LOG(INFO)<< s;

            if( is_main_symbol(tick->symbol) )
                LOG(INFO)<< s;

            f << s;
        }
        f.flush();
     }
}

bool MarketCollection::is_main_symbol(const char* s)
{
    return strcmp( main_symbol_.c_str(), s) == 0;
}

// 废弃
void MarketCollection::OnHeartBeatWarning(int nTimeLapse)
{
}
