#include "WelcomeStubImpl.hpp"

WelcomeStubImpl::WelcomeStubImpl() {}
WelcomeStubImpl::~WelcomeStubImpl() {}

void WelcomeStubImpl::sayHi(const std::shared_ptr<CommonAPI::ClientId> _client,
                                  std::string _name, sayHiReply_t _reply)
{
    std::stringstream messageStream;
    messageStream << "Hi " << _name << "!";
    std::cout << "sayHi('" << _name << "'): '" << messageStream.str() << "'\n";

    _reply(messageStream.str());
};
