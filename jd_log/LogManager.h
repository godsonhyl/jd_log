#ifndef JD_LOGMANAGER_H
#define JD_LOGMANAGER_H

#include <string>
#include <memory>
#include <map>
#include "nsdef.h"
#include "IBaseLogger.h"

using namespace std;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#ifdef JD_LOG_EXPORT
#define DllLogExportOrImport __declspec(dllexport)
#else
#define DllLogExportOrImport __declspec(dllimport)
#endif
#else
#define DllLogExportOrImport
#endif

NS_JDLOG_COMMON_BEGIN

class DllLogExportOrImport LogManager
{
private:
    ~LogManager();

    LogManager() = default;

public:
    LogManager(LogManager const &) = delete;

    void operator=(LogManager const &)= delete;

public:
    static LogManager &instance();

    static void SetDefaultLevel(const Common::level_enum &level);

    static void SetDefaultPattern(const std::string &pattern);

    static void SetDefaultLoggerName(const std::string &name);

    static void SetDefaultLogFile(const std::string &log_file);

    static void SetDefaultConsole(bool print_to_console);

    static shared_ptr<IBaseLogger> GetLogger(const std::string &name);

    static shared_ptr<IBaseLogger> GetLogger(const std::string &name, const std::string &log_file);

    static shared_ptr<IBaseLogger> GetLogger(const std::string &name, const std::string &log_file, level_enum level);

    static shared_ptr<IBaseLogger> GetLogger(const std::string &name, const std::string &log_file, level_enum level, const std::string &pattern);

    static shared_ptr<IBaseLogger> GetLogger(const std::string &name, const std::string &log_file, level_enum level, const std::string &pattern, bool print_to_console);

    static shared_ptr<IBaseLogger> GetLogger();

    static void DropAll();
};
NS_JDLOG_COMMON_END

#endif //JD_LOGMANAGER_H
