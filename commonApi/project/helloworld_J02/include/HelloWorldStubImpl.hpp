/*
 * @Author: dding3
 * @Date: 2023-07-27 16:56:02
 * @LastEditors: dding3
 * @LastEditTime: 2023-07-27 16:56:03
 * @Description:
 * @FilePath: \test\commonApi\project\helloworld\include\HelloWorldStubImpl.hpp
 */
#ifndef HELLOWORLDSTUBIMPL_H_
#define HELLOWORLDSTUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/hello_world/HelloWorldStubDefault.hpp>

class HelloWorldStubImpl : public v1_0::hello_world::HelloWorldStubDefault
{
public:
    HelloWorldStubImpl();
    virtual ~HelloWorldStubImpl();
    virtual void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client,
                          std::string _name, sayHelloReply_t _return);
};
#endif /* HELLOWORLDSTUBIMPL_H_ */
