#ifndef MARKETCOLLECTION_H
#define MARKETCOLLECTION_H

#include "ctpsdk/ThostFtdcMdApi.h"
#include <string>
#include <vector>
#include <atomic>
#include "simplequeue.h"

class MarketCollection : public CThostFtdcMdSpi
{
public:
    MarketCollection() = default;
    MarketCollection(std::string symbol);
    ~MarketCollection(){ exit_ = true; }

    void set_mdapi(CThostFtdcMdApi* p) { api_ = p; }
    void start_save_thread();

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
    void do_collect_tick(CThostFtdcDepthMarketDataField *pData);
    void queue_save();

private:
    CThostFtdcMdApi *api_;
    std::vector<std::string> symbols_;
    SimpleQueue<std::string> simple_queue_;
    std::atomic<bool> exit_;
};

#endif // MARKETCOLLECTION_H
