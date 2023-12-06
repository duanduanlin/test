/*
 * @Author: dding3
 * @Date: 2023-07-27 16:55:41
 * @LastEditors: dding3
 * @LastEditTime: 2023-07-28 09:56:04
 * @Description:
 * @FilePath: \test\commonApi\project\goodbye\include\GoodByeStubImpl.hpp
 */
#ifndef GOODBYESTUBIMPL_H_
#define GOODBYESTUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/good_bye/GoodByeStubDefault.hpp>

class GoodByeStubImpl : public v1_0::good_bye::GoodByeStubDefault
{
public:
    GoodByeStubImpl();
    virtual ~GoodByeStubImpl();
    virtual void sayGoodBye(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayGoodByeReply_t _reply);
};
#endif /* GOODBYESTUBIMPL_H_ */
