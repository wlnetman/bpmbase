#ifndef MARKETCOLLECTION_H
#define MARKETCOLLECTION_H

#include "ctpsdk/ThostFtdcMdApi.h"
#include <string>
#include <vector>
#include <map>
#include <atomic>
#include "simplequeue.h"
#include "tickdatadefine.h"

class MarketCollection : public CThostFtdcMdSpi
{
    using TickVec  = std::vector<std::shared_ptr<TickData>>;
    using pTickVec = std::shared_ptr<TickVec>;

public:
    MarketCollection() : exit_(false), maxsize_tickvec_(10000) {}
    ~MarketCollection(){ exit_ = true; }

    void set_mdapi(CThostFtdcMdApi* p) { api_ = p; }
    void set_symbol(const std::string &symbols);
    void set_main_symbol(const std::string &symbol);
    void set_user(const std::string& broker,
                  const std::string& userid,
                  const std::string& password);

    void consumer_thread();

    double calc_index(TickVec& tick);
    void   calc_index(const char* symbol);

public:
    void OnFrontConnected();
    void OnFrontDisconnected(int nReason);

    // 登录请求响应
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                        CThostFtdcRspInfoField *pRspInfo,
                        int nRequestId, bool bIsLast);
    // 订阅行情应答
    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                            CThostFtdcRspInfoField *pRspInfo,
                            int nRequest, bool bIsLast);
    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                              CThostFtdcRspInfoField *pRspInfo,
                              int nRequest, bool bIsLast);
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestId, bool bIsLast);
    void OnHeartBeatWarning(int nTimeLapse); // 废弃
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

private:
    void do_login();
    void do_subscribe();
    void push_depthdata_to_tickquque(CThostFtdcDepthMarketDataField *pData);
    void write_tick_to_file();
    bool is_main_symbol(const char* s);
    bool is_subscribe_symbol(const char* symbol);

private:
    CThostFtdcMdApi *api_;
    std::vector<std::string> symbols_;
    std::string broker_;
    std::string userid_;
    std::string password_;
    std::string main_symbol_;

    int                                    maxsize_tickvec_;
    std::map<std::string, pTickVec>        tick_mgr_;       // 根据symbol保存tick
    SimpleQueue<std::shared_ptr<TickData>> producer_task_;  // 生产者队列
    std::atomic<bool> exit_;
};

#endif // MARKETCOLLECTION_H
