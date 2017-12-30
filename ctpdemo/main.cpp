#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "marketcollection.h"
#include "ctpsdk/ThostFtdcMdApi.h"

int main(int argc, char* argv[])
{

    // 本地流文件生成的目录
    std::string flow_path = "";
    char front[] = {"tcp://180.168.146.187:10031"};
    MarketCollection collector("rb1805");

    CThostFtdcMdApi *api = CThostFtdcMdApi::CreateFtdcMdApi(flow_path.c_str(), false, false);
    collector.set_mdapi(api);
    api->RegisterSpi(&collector);
    api->RegisterFront(front);
    api->Init();
    api->Join();

    getchar();
    return 0;
}
