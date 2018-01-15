#include "config.h"
#include <chrono>
#include <ctime>
#include "utils/logging.h"
#include "utils/ini.h"
#include "utils/strutil.h"

Config::Config(std::string &file)
{
    load(file);
}

// 读取配置文件
void Config::load(std::string &file)
{
/*
[root]
    brokerid=9999
    userid=051257
    password=zaq1xsw2
    frontTrading=tcp://180.168.146.187:10031
    frontNotTrading=tcp://180.168.146.187:10010
    indexList=rb;jm;BlackChain
[rb]
    index=rb8888
    main=rb1805
    symbolList=rb1801;rb1802;rb1803;rb1804;rb1805;rb1806;rb1807;rb1807;rb1808;rb1809;rb1810;rb1811;rb1812
*/
    using int_t = INI<std::string,std::string,std::string>;
    int_t ini(file, true);
    ini.select("root");
    mdBrokerId = ini.get("brokerid", "9999");
    mdUserId   = ini.get("userid", "051257");
    mdPassword = ini.get("userid", "zaq1xsw2");

    // 交易时段:10010 非交易时段(16:00-09:00):10031
    std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm now;
    localtime_s(&now, &t);
    if(now.tm_hour >=8 && now.tm_hour <= 16 )
        mdFront = ini.get("frontNotTrading", "tcp://180.168.146.187:10031");
    else
        mdFront = ini.get("frontTrading", "tcp://180.168.146.187:10010");
    LOG(INFO)<< "front:" << mdFront;

    std::string index_list = ini.get("indexList", "rb;jm");
    auto all = StrUtil::split(index_list, ";");
    for( auto i : all ){
        // rb; j; jm
        ini.select(i);
        auto symbol_list = ini.get("symbolList");
        auto symbol_array = StrUtil::split(symbol_list, ";");
        for( auto j : symbol_array ){
            // 主力合约 rb1805
            // 指数名称 rb8888
            symbols_list.push_back(j);
        }
        std::string main = ini.get("main","");
        main_symbols[main] = true;
        //LOG(INFO)<< main;
    }
}
