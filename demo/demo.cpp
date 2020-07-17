#include <thread>
#include <iostream>
#include <vector>
#include "LogManager.h"


#define LOGGER JDLOG::Common::LogManager::GetLogger("log/logtest.log")

void writelog()
{
    auto logger = JDLOG::Common::LogManager::GetLogger("log/logtest.log");
    for (int i = 0; i< 10; i++)
    {       
        JDLOG_INFO(logger, "LOG INFO");
        JDLOG_WARN(logger, "LOG WARN");
        JDLOG_ERROR(logger, "LOG ERROR");        
    }

    logger->Flush();
}

int main()
{       
    // LOG CONFIG
    if (true)
    {
        string log_pattern_ = "%Y-%m-%d %H:%M:%S:%f,%P,%t,%l - %v";
        JDLOG::Common::LogManager::SetDefaultPattern(log_pattern_);
        JDLOG::Common::LogManager::SetDefaultLogFile("log/logtest.log");
    }
    
    JDLOG_INFO(LOGGER, "LOG INFO,{},{},", 666, "HELL WORLD");
    JDLOG_WARN(LOGGER, "LOG WARN{},{},", 666, "HELL WORLD");
    JDLOG_ERROR(LOGGER, "LOG ERROR{},{},", 666, "HELL WORLD");

    std::vector<std::thread> workers;
    for (int i = 0; i < 10; i++)
    {
        workers.push_back(std::thread([]()
        {
            writelog();
        }));
    }

    for (int i = 0; i < 10; i++)
    {
        workers[i].join();
    }

    getchar();
    
    return 0;
}


