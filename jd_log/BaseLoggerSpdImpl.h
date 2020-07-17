#ifndef JD_BASELOGGERSPDIMPL_H
#define JD_BASELOGGERSPDIMPL_H

#include "nsdef.h"
#include "IBaseLogger.h"
#include "spdlog/spdlog.h"

NS_JDLOG_COMMON_BEGIN

class BaseLoggerSpdImpl : public IBaseLogger
{
private:
    std::shared_ptr<spdlog::logger> spdlog_;
    std::string log_name_;
    std::string log_file_;
    std::string pattern_;
    level_enum level_;
    bool print_console_;
public:
    explicit BaseLoggerSpdImpl(const string &log_name, const string &log_file, level_enum level, const string &pattern, bool print_console);

    ~BaseLoggerSpdImpl() = default;

    void logImpl(level_enum lvl, const string &msg) override;

    void SetLevel(level_enum level) override;

    void SetPattern(const string &pattern) override;

    void Initialize() override;

    void Flush() override;

};

NS_JDLOG_COMMON_END
#endif //JD_BASELOGGERSPDIMPL_H
