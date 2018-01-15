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
#include <cctype>

#include "fmt/format.h"
#include "utils/strutil.h"
#include "utils/timeutil.h"
#include "utils/logging.h"
#include "marketcollection.h"
#include "tickdatadefine.h"

void MarketCollection::OnFrontConnected()
{
    LOG(INFO)<< "OnFrontConnected\n";

    do_login();
}

void MarketCollection::do_login()
{
    CThostFtdcReqUserLoginField req;
    std::memset(&req, 0, sizeof(req));
    std::memcpy(&req.BrokerID, config_->mdBrokerId.c_str(), config_->mdBrokerId.length());
    std::memcpy(&req.UserID, config_->mdUserId.c_str(), config_->mdUserId.length());
    std::memcpy(&req.Password, config_->mdPassword.c_str(), config_->mdPassword.length());

    LOG(INFO)<< "do login: " << req.BrokerID << ", userid:" << req.UserID;

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
    symbols_ = config_->symbols_list;

    if( api_ == nullptr || symbols_.empty()) {
        std::cout<< "Cannot subscribe" << std::endl;
        return;
    }

    const char * tday = api_->GetTradingDay();
    tradingday_ = tday;

    // 读取保存的tick数据
    load_tick_to_file_bin();

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
    tick->updateMs        = pData->UpdateMillisec;
    tick->actionDatetime  = bpm_str2ctime(str_time.c_str(), "%Y%m%d %H:%M:%S");
    tick->lastPrice       = pData->LastPrice;
    tick->openPrice       = pData->OpenPrice;
    tick->highPrice       = pData->HighestPrice;
    tick->lowPrice        = pData->LowestPrice;
    tick->preClosePrice   = pData->PreClosePrice;
    tick->openInterest    = pData->OpenInterest;
    //tick->volume        = ; // TODO: 本次Volume-上个Volume
    tick->totalVolume     = pData->Volume;
    tick->askPrice        = pData->AskPrice1;
    tick->bidPrice        = pData->BidPrice1;
    tick->askVolume       = pData->AskVolume1;
    tick->bidVolume       = pData->BidVolume1;
    tick->upperLimit      = pData->UpperLimitPrice;
    tick->lowerLimit      = pData->LowerLimitPrice;
    tick->averagePrice    = pData->AveragePrice;
    tick->settlementPrice = pData->SettlementPrice;
    tick->preSettlementPrice = pData->PreSettlementPrice;

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

void MarketCollection::calc_index(TickVec& tick, TickData& ret)
{
    ret.lastPrice = calc_index(tick);
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
        std::string index_name = get_index_symbol(symbol);
        TickVec tmp_vec;
        for( const auto & item : tick_mgr_ ){
            // 取每个合约的最后一条记录
            tmp_vec.push_back( item.second->back() );
        }
        TickData index_8888;
        std::memset(&index_8888, 0, sizeof(TickData));
        calc_index( tmp_vec, index_8888);
        auto& v = index_tick_.find( index_name ) ;
        if( v != index_tick_.end() ){
            std::shared_ptr<TickData> pTick = std::make_shared<TickData>(index_8888);
            v->second->push_back( pTick );
        } else {
            pTickVec pVec = std::make_shared<TickVec>();
            pVec->reserve( maxsize_tickvec_);
            std::shared_ptr<TickData> pTick = std::make_shared<TickData>(index_8888);
            pVec->push_back( pTick );
            index_tick_[index_name] = pVec;
        }
        LOG(INFO)<< index_name << ":" << index_8888.lastPrice;
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
            vec->reserve( maxsize_tickvec_ );
            vec->push_back(tick);
            tick_mgr_[ std::string(tick->symbol) ] = vec;
        }

        // 保存tick到文件
        save_tick_to_file_txt();

        // 计算指数
        calc_index(tick->symbol);
    }
    LOG(INFO)<< "queue save exit \n";
}

std::chrono::system_clock::time_point last_write = std::chrono::system_clock::now();
void MarketCollection::save_tick_to_file_txt()
{
    // 隔段时间刷新一次到文件
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    if( std::chrono::duration_cast<std::chrono::seconds>( now - last_write).count() < 5 )
        return;

    last_write = now;

    for( const auto& v : tick_mgr_){

        DLOG_ASSERT( !v.second->empty() );

        std::string fname;
        fname = fmt::format("C:\\temp\\tick\\{}_{}.txt", v.first, tradingday_);

        std::ofstream f( fname.c_str(), std::ofstream::out | std::ofstream::trunc ); // 隐含输出截断

        for( std::shared_ptr<TickData> tick : *(v.second) ){

            std::string s = tick2str(tick);

            //LOG(INFO)<< s;
            f << s;
        }
        f.close();
     }

    save_tick_to_file_bin();
}

void MarketCollection::save_tick_to_file_bin()
{
    for( const auto& v : tick_mgr_){

        DLOG_ASSERT( !v.second->empty());

        std::string fname;
        fname = fmt::format("C:\\temp\\tick\\{}_{}.dat", v.first, tradingday_);

        // 隐含输出截断,所以需要app
        std::ofstream f( fname.c_str(), std::ofstream::app | std::ofstream::binary );

        for( auto& item : *(v.second) )
            f.write( reinterpret_cast<char*>(&(*item)), sizeof(TickData) );

        f.close();
     }
}

//   TODO，画蛇添足
void MarketCollection::load_tick_to_file_txt()
{
}

void MarketCollection::load_tick_to_file_bin()
{
    for(auto symbol : symbols_){
        std::string fname;
        fname = fmt::format("c:\\temp\\tick\\{}_{}.dat", symbol, tradingday_);
        std::ifstream f;
        f.open(fname, std::ifstream::binary );
        if(f.is_open()){
            pTickVec pVec = std::make_shared<TickVec>();
            tick_mgr_[symbol] = pVec;
            while ( !f.eof() ){
                TickData tick;
                std::memset(&tick, 0, sizeof(TickData));
                f.read( reinterpret_cast<char*>(&tick), sizeof(TickData));
                std::shared_ptr<TickData> pData = std::make_shared<TickData>(tick);
                pVec->push_back(pData);
            }
        }
    }
}

bool MarketCollection::is_main_symbol(const char* s)
{
    auto ret = config_->main_symbols.find(s);
    return ret != config_->main_symbols.end();
}

std::string MarketCollection::get_index_symbol(const char* s)
{
    std::string str = s;
    std::string ret;
    std::for_each( std::begin(str), end(str), [&ret](char c){if(std::isalpha(c)) ret += c;} );
    return ret + "8888";
}

// 废弃
void MarketCollection::OnHeartBeatWarning(int nTimeLapse)
{
}

std::string MarketCollection::tick2str(std::shared_ptr<TickData> tick)
{
    TickData& refTick = *tick;
    return tick2str( refTick );
}

std::string MarketCollection::tick2str(TickData& tick)
{
    std::string s;
    s = fmt::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}\n",
                    bpm_ctime2str(tick.actionDatetime, "%Y%m%d %H:%M:%S"),
                    tick.symbol,
                    tick.lastPrice,
                    tick.openPrice,
                    tick.highPrice,
                    tick.lowPrice,
                    tick.preClosePrice,
                    tick.averagePrice,
                    tick.settlementPrice,
                    tick.preSettlementPrice,
                    tick.totalVolume,
                    tick.openInterest,
                    tick.askPrice,
                    tick.askVolume,
                    tick.bidPrice,
                    tick.bidVolume,
                    tick.upperLimit,
                    tick.lowerLimit);
    return s;
}

