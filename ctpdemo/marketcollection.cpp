#include "marketcollection.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "fmt/format.h"

MarketCollection::MarketCollection( std::string symbol )
{
    symbols_.push_back(symbol);
}

void MarketCollection::OnFrontConnected()
{
    std::cout<< "OnFrontConnected" << std::endl;

    do_login();
}

void MarketCollection::do_login()
{
    std::string broker = {"9999"};
    std::string userid = {"051031"};
    std::string password = {"zaq1xsw2"};

    CThostFtdcReqUserLoginField req;
    std::memset(&req, 0, sizeof(req));
    std::memcpy(&req.BrokerID, broker.c_str(), broker.length());
    std::memcpy(&req.UserID, userid.c_str(), userid.length());
    std::memcpy(&req.Password, password.c_str(), password.length());

    int nRequestId = 0;
    // TODO:异常处理
    if(api_)
        api_->ReqUserLogin( &req, nRequestId);
}

void MarketCollection::OnFrontDisconnected(int nReason)
{
    std::cout<< "OnFrontDisconnected:" << nReason << std::endl;
}

// 登录请求响应
void MarketCollection::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                    CThostFtdcRspInfoField *pRspInfo,
                    int nRequestId, bool bIsLast)
{
    std::cout<< "OnRspUserLogin:" << nRequestId << std::endl;
    //
    do_subscribe();
}

void MarketCollection::do_subscribe()
{
    if( api_ == nullptr || symbols_.empty()) {
        std::cout<< "Cannot subscribe" << std::endl;
        return;
    }

    // TODO : vector转字符串数组
    //        std::strcpy(instrument, item.c_str());
    // easyctp是每一个发送一次订阅请求
    for( auto &item : symbols_) {
        std::cout<< item << std::endl;
        std::string &symble = item;
        char *instrument[1] = {(char*)symble.c_str()};
        api_->SubscribeMarketData( instrument, 1);
    }
    //delete []instrument;
}

// 订阅行情应答
void MarketCollection::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                        CThostFtdcRspInfoField *pRspInfo,
                        int nRequestID, bool bIsLast)
{
    std::cout<< "OnRspSubMarketData:" << nRequestID << std::endl;
}

void MarketCollection::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                          CThostFtdcRspInfoField *pRspInfo,
                          int nRequestID, bool bIsLast)
{
    std::cout<< "OnRspUnSubMarketData : " << nRequestID << std::endl;
}

void MarketCollection::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestId, bool bIsLast)
{
    std::cout<< "OnRspError:" << nRequestId << std::endl;
}


void MarketCollection::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pData)
{
    //std::cout<< "OnRtnDepthMarketData: " << std::endl;

    // TODO: 缓存起来放到io线程写文件
    // TODO: 放到map查找
    for( auto item : symbols_){
        if( std::strcmp(pData->InstrumentID, item.c_str()) == 0 )
            do_collect_tick(pData);
    }
}

void MarketCollection::do_collect_tick(CThostFtdcDepthMarketDataField *pData)
{
    std::cout << fmt::format("{} {} {} {} {} {} {} {} {}\n",
                        pData->InstrumentID,
                        pData->ActionDay,
                        pData->UpdateTime,
                        pData->OpenPrice,
                        pData->HighestPrice,
                        pData->LowestPrice,
                        pData->PreClosePrice,
                        pData->OpenInterest,
                        pData->Volume);
}

// 废弃
void MarketCollection::OnHeartBeatWarning(int nTimeLapse)
{
}