#pragma once

#include <QString>

namespace app
{
class Logger
{
    explicit Logger() = default;

public:
    static Logger &instance();

    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
    Logger(Logger &&) = delete;
    Logger &operator=(Logger &&) = delete;

    void debug(const QString &text);
    void info(const QString &text);
    void error(const QString &text);
};

}  // namespace app
