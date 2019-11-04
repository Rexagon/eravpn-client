// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#define OVPNCLI_HPP
#include <client/ovpncli.cpp>

#include "ClientBase.hpp"

using namespace openvpn;

namespace app::vpn
{
#ifdef USE_TUN_BUILDER

bool ClientBase::tun_builder_new()
{
    tbc.tun_builder_set_mtu(1500);
    return true;
}


int ClientBase::tun_builder_establish()
{
    if (!tun)
    {
        tun.reset(new TUN_CLASS_SETUP());
    }

    TUN_CLASS_SETUP::Config config;
    config.layer = Layer(Layer::Type::OSI_LAYER_3);
    // no need to add bypass routes on establish since we do it on socket_protect
    config.add_bypass_routes_on_establish = false;
    return tun->establish(tbc, &config, nullptr, std::cout);
}


bool ClientBase::tun_builder_add_address(const std::string &address,
                                         int prefix_length,
                                         const std::string &gateway,
                                         bool ipv6,
                                         bool net30)
{
    return tbc.tun_builder_add_address(address, prefix_length, gateway, ipv6, net30);
}


bool ClientBase::tun_builder_add_route(const std::string &address, int prefix_length, int metric, bool ipv6)
{
    return tbc.tun_builder_add_route(address, prefix_length, metric, ipv6);
}


bool ClientBase::tun_builder_reroute_gw(bool ipv4, bool ipv6, unsigned int flags)
{
    return tbc.tun_builder_reroute_gw(ipv4, ipv6, flags);
}


bool ClientBase::tun_builder_set_remote_address(const std::string &address, bool ipv6)
{
    return tbc.tun_builder_set_remote_address(address, ipv6);
}


bool ClientBase::tun_builder_set_session_name(const std::string &name)
{
    return tbc.tun_builder_set_session_name(name);
}


bool ClientBase::tun_builder_add_dns_server(const std::string &address, bool ipv6)
{
    return tbc.tun_builder_add_dns_server(address, ipv6);
}


void ClientBase::tun_builder_teardown(bool disconnect)
{
    std::ostringstream os;
    auto os_print = Cleanup([&os]() { OPENVPN_LOG_STRING(os.str()); });
    tun->destroy(os);
}


bool ClientBase::socket_protect(int socket, std::string remote, bool ipv6)
{
    (void)socket;
    std::ostringstream os;
    auto os_print = Cleanup([&os]() { OPENVPN_LOG_STRING(os.str()); });
    return tun->add_bypass_route(remote, ipv6, os);
}
#else

bool ClientBase::socket_protect(int socket, std::string remote, bool /*ipv6*/)
{
    std::cout << "NOT IMPLEMENTED: *** socket_protect " << socket << " " << remote << std::endl;
    return true;
}

#endif
}  // namespace app::vpn
