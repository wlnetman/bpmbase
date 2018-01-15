#ifndef MARKETCOLLECTION_H
#define MARKETCOLLECTION_H

#include "ctpsdk/ThostFtdcMdApi.h"
#include <string>
#include <vector>
#include <map>
#include <atomic>
#include "simplequeue.h"
#include "tickdatadefine.h"
#include "config.h"

class MarketCollection : public CThostFtdcMdSpi
{
    using TickVec  = std::vector<std::shared_ptr<TickData>>;
    using pTickVec = std::shared_ptr<TickVec>;

public:
    MarketCollection() : exit_(false), maxsize_tickvec_(6*60*60*2), config_(nullptr) {}
    ~MarketCollection(){ exit_ = true; }

    void set_mdapi(CThostFtdcMdApi* p) { api_ = p; }
    void set_config(Config* cfg) { config_ = cfg; }
    void consumer_thread();

    double   calc_index(TickVec& );
    void     calc_index(TickVec& , TickData& );
    void     calc_index(const char* symbol);

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
    void save_tick_to_file_txt();
    void save_tick_to_file_bin();
    void load_tick_to_file_txt();
    void load_tick_to_file_bin();
    bool is_main_symbol(const char* s);
    std::string get_index_symbol(const char* s);
    bool is_subscribe_symbol(const char* symbol);
    std::string tick2str(std::shared_ptr<TickData> tick);
    std::string tick2str(TickData& tick);

private:
    Config* config_;
    CThostFtdcMdApi *api_;
    std::vector<std::string> symbols_;
    std::string tradingday_;

    int                                    maxsize_tickvec_; // 螺纹6*3600秒，每秒2个tick
    std::map<std::string, pTickVec>        tick_mgr_;       // 根据symbol保存tick
    std::map<std::string, pTickVec>        index_tick_;     // 指数的tick
    SimpleQueue<std::shared_ptr<TickData>> producer_task_;  // 生产者队列
    std::atomic<bool> exit_;
};

#endif // MARKETCOLLECTION_H
