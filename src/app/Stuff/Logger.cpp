// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Logger.hpp"

#include <iostream>

namespace app
{
Logger &Logger::instance()
{
    static Logger logger{};
    return logger;
}


void Logger::debug(const QString &text)
{
#ifndef DISABLE_LOGGING
    std::cout << "Debug: " << text.toStdString() << std::endl;
#endif
}


void Logger::info(const QString &text)
{
    std::cout << "Info: " << text.toStdString() << std::endl;
}


void Logger::error(const QString &text)
{
    // TODO: print trace
    std::cout << "Error" << text.toStdString() << std::endl;
}

}  // namespace app
