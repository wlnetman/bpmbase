#ifndef MARKETCOLLECTION_H
#define MARKETCOLLECTION_H

#include "ctpsdk/ThostFtdcMdApi.h"
#include <string>
#include <vector>
#include <map>
#include <atomic>
#include "simplequeue.h"

// Tick信息
#define STR_LEN_SMALL 16 // 小字符串长度
#define STR_LEN_BIG 64 // 大字符串长度
struct TickData {
    char symbol[STR_LEN_SMALL]; // 合约代码
    long long actionDatetime; // 时间,time_t
    int updateMs; // 时间的毫秒 or 当天唯一编号
    int res1; // 占位对齐
    double lastPrice; // 最新价
    int volume; // 本tick的成交量,需要自己计算
    int totalVolume; // 总成交量
    double openInterest; // 持仓量
    double askPrice; // 买一价
    double bidPrice; // 卖一价
    int askVolume; // 买一量
    int bidVolume; // 卖一量
    double openPrice; // 今日开盘价
    double highPrice; // 今日最高价
    double lowPrice; // 今日最低价
    double preClosePrice; // 昨日收盘价
    double upperLimit; // 涨停价
    double lowerLimit; // 跌停价

    double averagePrice; // 当日平均价
    double settlementPrice; // 当前结算价
    double preSettlementPrice; // 昨日结算价
};

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
