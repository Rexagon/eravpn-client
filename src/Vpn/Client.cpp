// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Client.hpp"

#include <openvpn/time/timestr.hpp>

using namespace openvpn;

namespace app::vpn
{
void Client::event(const ClientAPI::Event &event)
{
    std::cout << date_time() << " EVENT: " << event.name;

    if (!event.info.empty())
    {
        std::cout << ' ' << event.info;
    }

    if (event.fatal)
    {
        std::cout << " [FATAL-ERR]";
    }
    else if (event.error)
    {
        std::cout << " [ERR]";
    }

    std::cout << std::endl;
}


void Client::log(const ClientAPI::LogInfo &log)
{
    std::lock_guard<std::mutex> lock(m_loggerMutex);
    std::cout << date_time() << ' ' << log.text << std::flush;
}


void Client::external_pki_cert_request(ClientAPI::ExternalPKICertRequest &request)
{
    request.error = true;
    request.errorText = "external_pki_cert_request not implemented";
}


void Client::external_pki_sign_request(ClientAPI::ExternalPKISignRequest &request)
{
    request.error = true;
    request.errorText = "external_pki_sign_request not implemented";
}


bool Client::pause_on_connection_timeout()
{
    return false;
}

}  // namespace app::vpn
