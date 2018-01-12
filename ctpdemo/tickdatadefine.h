#ifndef TICKDATADEFINE_H
#define TICKDATADEFINE_H

#include <memory>

// Tick信息
#define STR_LEN_SMALL 16 // 小字符串长度
#define STR_LEN_BIG 64 // 大字符串长度
struct TickData {
    TickData() = default;
    TickData(TickData& t){
        std::memcpy(this, &t, sizeof(TickData));
    }
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

#endif // TICKDATADEFINE_H
