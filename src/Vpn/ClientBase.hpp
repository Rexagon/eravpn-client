#pragma once

#include <iostream>
#include <string>

// FUCK OPENVPN LIBRARY

#include <openvpn/common/platform.hpp>

#ifdef OPENVPN_EXTERN
#undef OPENVPN_EXTERN
#endif

#define OPENVPN_EXTERN extern

#ifdef OPENVPN_PLATFORM_MAC
#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CFBundle.h>
#endif  // OPENVPN_PLATFORM_MAC

#ifndef OVPNCLI_HPP
#include <client/ovpncli.hpp>
#endif  // OVPNCLI_HPP

#ifndef OPENVPN_LOG
// log thread settings
#define OPENVPN_LOG_CLASS openvpn::ClientAPI::LogReceiver
#define OPENVPN_LOG_INFO openvpn::ClientAPI::LogInfo
#include <openvpn/log/logthread.hpp>  // should be included early
#endif

// on Android and iOS, use TunBuilderBase abstraction
#if (defined(OPENVPN_PLATFORM_ANDROID) || defined(OPENVPN_PLATFORM_IPHONE)) && !defined(OPENVPN_FORCE_TUN_NULL) && \
    !defined(OPENVPN_EXTERNAL_TUN_FACTORY)
#define USE_TUN_BUILDER
#endif

#ifdef OPENVPN_REMOTE_OVERRIDE
#include <openvpn/common/process.hpp>
#endif  // OPENVPN_REMOTE_OVERRIDE

#ifdef USE_TUN_BUILDER
#ifdef OPENVPN_PLATFORM_WIN
#include <openvpn/tun/win/client/tuncli.hpp>
#define TUN_CLASS_SETUP TunWin::Setup
#endif

#ifdef OPENVPN_PLATFORM_MAC
#include <openvpn/tun/mac/client/tuncli.hpp>
#define TUN_CLASS_SETUP TunMac::Setup
#endif
#endif  // USE_TUN_BUILDER

namespace app::vpn
{
#ifdef USE_TUN_BUILDER

class ClientBase : public openvpn::ClientAPI::OpenVPNClient
{
public:
    bool tun_builder_new() override;

    int tun_builder_establish() override;

    bool tun_builder_add_address(const std::string &address,
                                 int prefix_length,
                                 const std::string &gateway,  // optional
                                 bool ipv6,
                                 bool net30) override;

    bool tun_builder_add_route(const std::string &address, int prefix_length, int metric, bool ipv6) override;

    bool tun_builder_reroute_gw(bool ipv4, bool ipv6, unsigned int flags) override;

    bool tun_builder_set_remote_address(const std::string &address, bool ipv6) override;

    bool tun_builder_set_session_name(const std::string &name) override;

    bool tun_builder_add_dns_server(const std::string &address, bool ipv6) override;

    void tun_builder_teardown(bool disconnect) override;

    bool socket_protect(int socket, std::string remote, bool ipv6) override;

private:
    openvpn::TUN_CLASS_SETUP::Ptr tun{new openvpn::TUN_CLASS_SETUP()};
    openvpn::TunBuilderCapture tbc;
};

#else  // USE_TUN_BUILDER

class ClientBase : public openvpn::ClientAPI::OpenVPNClient
{
public:
    bool socket_protect(int socket, std::string remote, bool ipv6) override;
};

#endif  // USE_TUN_BUILDER

}  // namespace app::vpn
