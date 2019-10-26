#pragma once

#include <string>

namespace app::vpn
{
struct Event
{
    enum class Type
    {
        Unknown,
        Resolve,
        Wait,
        Connecting,
        GetConfig,
        AssignIp,
        Connected,
        Disconnected
    };

    std::string name;
    std::string info;
    bool error;
    bool fatal;
};

Event::Type parse(const std::string &name);

}  // namespace app::vpn
