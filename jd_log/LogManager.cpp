#include <mutex>
#include <iostream>
#include "spdlog/spdlog.h"
#include "LogManager.h"

NS_JDLOG_COMMON_BEGIN

std::map<string, std::shared_ptr<Common::IBaseLogger>> logger_map_;

Common::level_enum defaut_level_ = Common::info;

string default_pattern_ = "%Y-%m-%d %H:%M:%S.%e,%n,%l,%t - %v";

std::string default_logger_name_ = "Default";

string default_log_file_ = "default.log";

std::recursive_mutex mutex_;

bool default_print_console_ = true;

void LogManager::SetDefaultLevel(const Common::level_enum &level)
{
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    defaut_level_ = level;
}

void LogManager::SetDefaultPattern(const std::string &pattern)
{
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    default_pattern_ = pattern;
}

void LogManager::SetDefaultLoggerName(const std::string &name)
{
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    default_logger_name_ = name;
}

void LogManager::SetDefaultConsole(bool print_console)
{
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    default_print_console_ = print_console;
}

void LogManager::SetDefaultLogFile(const std::string &log_file)
{
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    default_log_file_ = log_file;
}

std::shared_ptr<Common::IBaseLogger> LogManager::GetLogger()
{
    return GetLogger(default_logger_name_, default_log_file_, defaut_level_, default_pattern_, default_print_console_);
}

std::shared_ptr<Common::IBaseLogger> LogManager::GetLogger(const std::string &name)
{
    return GetLogger(name, default_log_file_, defaut_level_, default_pattern_, default_print_console_);
}

std::shared_ptr<Common::IBaseLogger>
LogManager::GetLogger(const std::string &name, const std::string &log_file)
{
    return GetLogger(name, log_file, defaut_level_, default_pattern_, default_print_console_);
}

std::shared_ptr<Common::IBaseLogger>
LogManager::GetLogger(const std::string &name, const std::string &log_file, level_enum level)
{
    return GetLogger(name, log_file, level, default_pattern_, default_print_console_);
}

std::shared_ptr<Common::IBaseLogger>
LogManager::GetLogger(const std::string &name, const std::string &log_file, level_enum level, const std::string &pattern)
{
    return GetLogger(name, log_file, level, pattern, default_print_console_);
}

std::shared_ptr<Common::IBaseLogger>
LogManager::GetLogger(const std::string &name, const std::string &log_file, level_enum level, const std::string &pattern, bool print_console)
{
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    if (logger_map_.find(name) == logger_map_.end())
    {
        std::shared_ptr<Common::IBaseLogger> logger = IBaseLogger::CreateInstance(name, log_file, level, pattern, print_console);
        logger->Initialize();
        logger_map_[name] = logger;
    }
    return logger_map_[name];
}

void LogManager::DropAll()
{
    logger_map_.clear();
}

LogManager &LogManager::instance()
{
    static LogManager s_instance;
    return s_instance;
}

LogManager::~LogManager()
{
    spdlog::drop_all();
}

NS_JDLOG_COMMON_END