#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "marketcollection.h"
#include "ctpsdk/ThostFtdcMdApi.h"
#include "utils/fileutil.h"
#include "utils/logging.h"

int main(int argc, char* argv[])
{
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

    std::string symbols = "rb1805;i1805;j1805;jm1805;";
    collector.set_symbol(symbols);

    collector.set_user("9999", "051031", "zaq1xsw2");
    api->RegisterSpi(&collector);

    char front[] = {"tcp://180.168.146.187:10031"};
    api->RegisterFront(front);

    // 开始写文件线程
    std::thread t( [&collector]{ collector.queue_save(); });
    t.detach();

    api->Init();
    api->Join();

    getchar();
    return 0;
}
