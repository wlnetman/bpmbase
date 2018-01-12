#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "marketcollection.h"
#include "ctpsdk/ThostFtdcMdApi.h"
#include "utils/fileutil.h"
#include "utils/logging.h"
#include "utils/crashdump.h"

int main(int argc, char* argv[])
{
    bpm_CrashDumpInitialize();

    // log 文件 ,crash
    //bpm_CrashDumpInitialize();
    FLAGS_log_dir = "c:\\temp\\log";
    bpm_createDir(FLAGS_log_dir.c_str());
    FLAGS_alsologtostderr = true;
    google::InitGoogleLogging(argv[0]);

    // 本地流文件生成的目录
    //std::string flow_path = "";
    CThostFtdcMdApi *api = CThostFtdcMdApi::CreateFtdcMdApi("", false, false);
    MarketCollection collector;
    collector.set_mdapi(api);

//    const std::string symbols = "rb1801;rb1802;rb1803;rb1804;rb1805;rb1806;"
//                          "rb1807;rb1808;rb1809;rb1810;rb1811;rb1812";
    //const std::string symbols = "jm1801;jm1802;jm1803;jm1804;jm1805;jm1806;"
                          "jm1807;jm1808;jm1809;jm1810;jm1811;jm1812";
    const std::string symbols = "jm1805;";
    collector.set_symbol(symbols);
    collector.set_main_symbol("jm1805");

    //collector.set_user("9999", "051024", "88888888");
    //collector.set_user("9999", "051257", "zaq1xsw2");
    collector.set_user("9999", "051031", "zaq1xsw2");
    api->RegisterSpi(&collector);

    // 交易时段
    //char front[] = {"tcp://180.168.146.187:10010"};
    // 非交易时段
    char front[] = {"tcp://180.168.146.187:10031"};
    LOG(INFO)<< "front:" << front;
    api->RegisterFront(front);

    // 开始写文件线程
    std::thread t( [&collector]{ collector.consumer_thread(); });
    t.detach();

    api->Init();
    api->Join();

    getchar();
    return 0;
}
