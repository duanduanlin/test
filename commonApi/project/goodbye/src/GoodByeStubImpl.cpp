/*
 * @Author: dding3
 * @Date: 2023-07-27 16:59:57
 * @LastEditors: dding3
 * @LastEditTime: 2023-07-28 10:31:17
 * @Description:
 * @FilePath: \test\commonApi\project\goodbye\src\GoodByeStubImpl.cpp
 */
#include "GoodByeStubImpl.hpp"

GoodByeStubImpl::GoodByeStubImpl() {}
GoodByeStubImpl::~GoodByeStubImpl() {}

 void GoodByeStubImpl::sayGoodBye(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayGoodByeReply_t _reply)
{
    std::stringstream messageStream;
    messageStream << "GoodBye " << _name << "!";
    std::cout << "sayGoodBye('" << _name << "'): '" << messageStream.str() << "'\n";

    _reply(messageStream.str());
};
