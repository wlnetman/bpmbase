#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "marketcollection.h"
#include "ctpsdk/ThostFtdcMdApi.h"

int main(int argc, char* argv[])
{
    // 本地流文件生成的目录
    //std::string flow_path = "";
    std::string symbols = "rb1805;i1805;j1805;jm1805;";

    CThostFtdcMdApi *api = CThostFtdcMdApi::CreateFtdcMdApi("", false, false);
    MarketCollection collector;
    collector.set_mdapi(api);
    collector.set_symbol(symbols);
    api->RegisterSpi(&collector);

    // 开始写文件线程
    std::thread t( [&collector]{ collector.queue_save(); });
    t.detach();

    char front[] = {"tcp://180.168.146.187:10031"};
    api->RegisterFront(front);
    api->Init();
    api->Join();

    getchar();
    return 0;
}
