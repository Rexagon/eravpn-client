// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <fstream>
#include <iostream>

#include <client/ovpncli.cpp>

class Client final : public openvpn::ClientAPI::OpenVPNClient
{
public:
    bool socket_protect(int socket, std::string remote, bool ipv6) override
    {
        std::cout << "Socket protect: " << std::endl
                  << "\tSocket:" << socket << std::endl
                  << "\tRemote: " << remote << std::endl
                  << "\tipv6: " << ipv6 << std::endl;

        return true;
    }

    void external_pki_cert_request(openvpn::ClientAPI::ExternalPKICertRequest &request) override
    {
        std::cout << "PKI cert request:" << std::endl
                  << "\tAlias: " << request.alias << std::endl
                  << "\tInvalid alias: " << request.invalidAlias << std::endl
                  << "\tCert: " << request.cert << std::endl
                  << "\tError: " << request.error << std::endl
                  << "\tError text: " << request.errorText << std::endl
                  << "\tSupporting chain: " << request.supportingChain << std::endl;
    }

    void external_pki_sign_request(openvpn::ClientAPI::ExternalPKISignRequest &request) override
    {
        std::cout << "PKI cert request:" << std::endl
                  << "\tAlias: " << request.alias << std::endl
                  << "\tInvalid alias: " << request.invalidAlias << std::endl
                  << "\tData: " << request.data << std::endl
                  << "\tError: " << request.error << std::endl
                  << "\tError text: " << request.errorText << std::endl
                  << "\tAlgorithm: " << request.algorithm << std::endl;
    }

    bool pause_on_connection_timeout() override
    {
        return true;
    }

    void event(const openvpn::ClientAPI::Event &event) override
    {
        std::cout << "Event: " << event.name << std::endl;
    }

    void log(const openvpn::ClientAPI::LogInfo &logInfo) override
    {
        std::cout << "Log: " << logInfo.text << std::endl;
    }
};

std::string readConfig(const std::string &path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Unable to open config file" << std::endl;
        exit(1);
    }

    // Read config file
    file.seekg(0, std::ios::end);
    const auto fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string config;
    config.resize(fileSize);

    file.read(&config[0], fileSize);

    file.close();

    return config;
}

int main(int argc, char **argv)
{
    if (argc < 1 + 3 /* /path/to/config.ovpn username password */)
    {
        return 1;
    }

    openvpn::ClientAPI::Config config;
    config.content = readConfig(argv[1]);

    Client client;
    openvpn::ClientAPI::EvalConfig eval = client.eval_config(config);

    if (eval.error)
    {
        std::cerr << "Evan error: " << eval.message << std::endl;
        return 1;
    }

    openvpn::ClientAPI::ProvideCreds credentials;
    credentials.username = argv[2];
    credentials.password = argv[3];

    client.provide_creds(credentials);
    client.connect();

    return 0;
}
