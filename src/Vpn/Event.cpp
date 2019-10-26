// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Event.hpp"

#include <unordered_map>

namespace app::vpn
{
Event::Type parse(const std::string &name)
{
    static std::unordered_map<std::string, Event::Type> events = {
        {"RESOLVE", Event::Type::Resolve},           //
        {"WAIT", Event::Type::Wait},                 //
        {"CONNECTING", Event::Type::Connecting},     //
        {"GET_CONFIG", Event::Type::GetConfig},      //
        {"ASSIGN_IP", Event::Type::AssignIp},        //
        {"CONNECTED", Event::Type::Connected},       //
        {"DISCONNECTED", Event::Type::Disconnected}  //
    };

    const auto it = events.find(name);
    if (it == events.end())
    {
        return Event::Type::Unknown;
    }

    return it->second;
}


}  // namespace app::vpn
