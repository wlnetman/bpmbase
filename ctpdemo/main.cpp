#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "marketcollection.h"
#include "ctpsdk/ThostFtdcMdApi.h"
#include "utils/fileutil.h"
#include "utils/logging.h"
#include "utils/crashdump.h"
#include "utils/ini.h"
#include "config.h"

int main(int argc, char* argv[])
{
    // log 文件 ,crash
    bpm_CrashDumpInitialize();
    FLAGS_log_dir = "c:\\temp\\log";
    bpm_createDir(FLAGS_log_dir.c_str());
    FLAGS_alsologtostderr = true;
    google::InitGoogleLogging(argv[0]);

    MarketCollection collector;

    // 读配置文件
    Config *g_cfg = new Config(std::string("C:\\temp\\ctpdemo.ini"));
    collector.set_config(g_cfg);

    // 本地流文件生成的目录
    CThostFtdcMdApi *api = CThostFtdcMdApi::CreateFtdcMdApi(g_cfg->mdFlowPath.c_str(), false, false);
    api->RegisterSpi(&collector);
    collector.set_mdapi(api);

    char front[100];
    std::strcpy(front, g_cfg->mdFront.c_str());
    api->RegisterFront( front );

    // 开始写文件线程
    std::thread t( [&collector]{ collector.consumer_thread(); });
    t.detach();

    api->Init();
    api->Join();

    getchar();
    return 0;
}
