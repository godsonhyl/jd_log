//#include <boost/filesystem.hpp>
#include <experimental/filesystem>
#include <iostream>
#include <mutex>
#include <map>

#include "spdlog/sinks/ansicolor_sink.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "BaseLoggerSpdImpl.h"



//typedef spdlog::sinks::daily_file_sink<std::mutex, spdlog::sinks::dateonly_daily_file_name_calculator> daily_file_sink_mt_dateonly;
typedef spdlog::sinks::daily_file_sink<std::mutex, spdlog::sinks::daily_filename_calculator> daily_file_sink_mt_dateonly;


NS_JDLOG_COMMON_BEGIN

std::shared_ptr<spdlog::sinks::ansicolor_stdout_sink_mt> stdout_sink_ptr_ = make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();

std::map<std::string, std::shared_ptr<daily_file_sink_mt_dateonly>> daily_file_sink_ptr_map_;

inline spdlog::level::level_enum GetSpdLevel(Common::level_enum lvl)
{
    switch (lvl)
    {
        case Common::trace:
            return spdlog::level::trace;
        case Common::debug:
            return spdlog::level::debug;
        case Common::info:
            return spdlog::level::info;
        case Common::warn:
            return spdlog::level::warn;
        case Common::error:
            return spdlog::level::err;
        case Common::critical:
            return spdlog::level::critical;
        case Common::off:
            return spdlog::level::off;
        default:
            return spdlog::level::info;
    }
}

const string &GetSpdPattern(const string &pattern)
{
    return pattern;
}

inline void BaseLoggerSpdImpl::logImpl(level_enum lvl, const string &msg)
{
    if (nullptr == spdlog_)
    {
        Initialize();
    }
    spdlog_->log(GetSpdLevel(lvl), msg);
}

void BaseLoggerSpdImpl::SetLevel(level_enum level)
{
    level_ = level;
    if (nullptr != spdlog_)
    {
        spdlog_->set_level(GetSpdLevel(level_));
    }
}

void BaseLoggerSpdImpl::SetPattern(const string &pattern)
{
    pattern_ = pattern;
    if (nullptr != spdlog_)
    {
        spdlog_->set_pattern(GetSpdPattern(pattern_));
    }
}

void BaseLoggerSpdImpl::Initialize()
{
    if (daily_file_sink_ptr_map_.find(log_file_) == daily_file_sink_ptr_map_.end())
    {      
        /*
        boost::filesystem::path pathfull = boost::filesystem::system_complete(log_file_);
        boost::filesystem::path dir = pathfull.parent_path();
        if (!boost::filesystem::exists(dir) && !boost::filesystem::create_directories(dir))
        {
            std::cerr << "Directory Create Failed: " << log_file_ << std::endl;
            exit(0);
        }*/
        
        
        auto pathfull = std::experimental::filesystem::system_complete(log_file_);
        std::experimental::filesystem::path dir = pathfull.parent_path();
        if (!std::experimental::filesystem::exists(dir) && !std::experimental::filesystem::create_directories(dir))
        {
            std::cerr << "Directory Create Failed: " << log_file_ << std::endl;
            exit(0);
        }
        
        daily_file_sink_ptr_map_[log_file_] = std::make_shared<daily_file_sink_mt_dateonly>(log_file_, 23, 59);
    }
    std::vector<spdlog::sink_ptr> sinks = std::vector<spdlog::sink_ptr> {daily_file_sink_ptr_map_[log_file_]};
    if (print_console_)
    {
        sinks.push_back(stdout_sink_ptr_);
    }
            
    //spdlog_ = spdlog::create_async(log_name_, begin(sinks), end(sinks), 1024 * 4, spdlog::async_overflow_policy::discard_log_msg, nullptr, std::chrono::milliseconds(200));
    spdlog_ = spdlog::create<daily_file_sink_mt_dateonly>("logger", log_name_, 0, 0);
    spdlog_->set_level(GetSpdLevel(level_));
    spdlog_->set_pattern(GetSpdPattern(pattern_));    
}

BaseLoggerSpdImpl::BaseLoggerSpdImpl(const string &log_name, const string &log_file, level_enum level, const string &pattern, bool print_console)
{
    log_name_ = log_name;
    log_file_ = log_file;
    pattern_ = pattern;
    level_ = level;
    print_console_ = print_console;
}

void BaseLoggerSpdImpl::Flush()
{
    spdlog_->flush();
}

std::shared_ptr<IBaseLogger> IBaseLogger::CreateInstance(const string &log_name, const string &log_file, level_enum level, const string &pattern, bool print_console)
{
    return std::make_shared<BaseLoggerSpdImpl>(log_name, log_file, level, pattern, print_console);
}


NS_JDLOG_COMMON_END

