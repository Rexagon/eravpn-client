#pragma once

#include <functional>
#include <mutex>
#include <optional>

#include "ClientBase.hpp"
#include "Event.hpp"

namespace app::vpn
{
class Client : public ClientBase
{
public:
    using EventCallback = std::function<void(const Event &)>;

    explicit Client(const EventCallback &eventHandler);

private:
    void event(const openvpn::ClientAPI::Event &event) override;

    void log(const openvpn::ClientAPI::LogInfo &log) override;

    void external_pki_cert_request(openvpn::ClientAPI::ExternalPKICertRequest &request) override;

    void external_pki_sign_request(openvpn::ClientAPI::ExternalPKISignRequest &request) override;

    bool pause_on_connection_timeout() override;

    EventCallback m_eventHandler;
    std::mutex m_loggerMutex;
};

}  // namespace app::vpn
