#ifndef MARKETCOLLECTION_H
#define MARKETCOLLECTION_H

#include "ctpsdk/ThostFtdcMdApi.h"
#include <string>
#include <vector>
#include <map>
#include <atomic>
#include "simplequeue.h"

// Tick信息
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
public:
    MarketCollection() : exit_(false) {}
    ~MarketCollection(){ exit_ = true; }

    void set_mdapi(CThostFtdcMdApi* p) { api_ = p; }
    void set_symbol(std::string &symbols);
    //void start_save_thread();
    void queue_save();
    void set_user(std::string& broker, std::string& userid, std::string &password);

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

private:
    CThostFtdcMdApi *api_;
    std::vector<std::string> symbols_;
    std::map<std::string, TickData> symbol_tick_;
    std::string broker_;
    std::string userid_;
    std::string password_;
    SimpleQueue<std::string> simple_queue_;
    std::atomic<bool> exit_;
};

#endif // MARKETCOLLECTION_H
