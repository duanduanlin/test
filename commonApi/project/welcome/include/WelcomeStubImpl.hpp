/*
 * @Author: dding3
 * @Date: 2023-07-27 16:56:02
 * @LastEditors: dding3
 * @LastEditTime: 2023-07-28 11:35:35
 * @Description:
 * @FilePath: \test\commonApi\project\welcome\include\WelcomeStubImpl.hpp
 */
#ifndef WelcomeSTUBIMPL_H_
#define WelcomeSTUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/welcome/WelcomeStubDefault.hpp>

class WelcomeStubImpl : public v1_0::welcome::WelcomeStubDefault
{
public:
    WelcomeStubImpl();
    virtual ~WelcomeStubImpl();
    virtual void sayHi(const std::shared_ptr<CommonAPI::ClientId> _client,
                          std::string _name, sayHiReply_t _return);
};
#endif /* WelcomeSTUBIMPL_H_ */
