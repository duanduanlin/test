/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.2.0.v202012010850.
* Used org.franca.core 0.13.1.201807231814.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_HELLO_WORLD_Hello_World_STUB_DEFAULT_HPP_
#define V1_HELLO_WORLD_Hello_World_STUB_DEFAULT_HPP_


#include <CommonAPI/Export.hpp>

#include <v1/hello_world/HelloWorldStub.hpp>
#include <cassert>
#include <sstream>

# if defined(_MSC_VER)
#  if _MSC_VER >= 1300
/*
 * Diamond inheritance is used for the CommonAPI::Proxy base class.
 * The Microsoft compiler put warning (C4250) using a desired c++ feature: "Delegating to a sister class"
 * A powerful technique that arises from using virtual inheritance is to delegate a method from a class in another class
 * by using a common abstract base class. This is also called cross delegation.
 */
#    pragma warning( disable : 4250 )
#  endif
# endif

namespace v1 {
namespace hello_world {

/**
 * Provides a default implementation for HelloWorldStubRemoteEvent and
 * HelloWorldStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 *
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class COMMONAPI_EXPORT_CLASS_EXPLICIT HelloWorldStubDefault
    : public virtual HelloWorldStub {
public:
    COMMONAPI_EXPORT HelloWorldStubDefault()
        : remoteEventHandler_(this),
          interfaceVersion_(HelloWorld::getInterfaceVersion()) {
    }

    COMMONAPI_EXPORT const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client) {
        (void)_client;
        return interfaceVersion_;
    }

    COMMONAPI_EXPORT HelloWorldStubRemoteEvent* initStubAdapter(const std::shared_ptr< HelloWorldStubAdapter> &_adapter) {
        CommonAPI::Stub<HelloWorldStubAdapter, HelloWorldStubRemoteEvent>::stubAdapter_ = _adapter;
        return &remoteEventHandler_;
    }

    COMMONAPI_EXPORT virtual void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _reply) {
        (void)_client;
        (void)_name;
        std::string message = "";
        _reply(message);
    }


protected:
    class COMMONAPI_EXPORT_CLASS_EXPLICIT RemoteEventHandler: public virtual HelloWorldStubRemoteEvent {
    public:
        COMMONAPI_EXPORT RemoteEventHandler(HelloWorldStubDefault *_defaultStub)
            : 
              defaultStub_(_defaultStub) {
        }


    private:
        HelloWorldStubDefault *defaultStub_;
    };
protected:
    HelloWorldStubDefault::RemoteEventHandler remoteEventHandler_;

private:


    CommonAPI::Version interfaceVersion_;
};

} // namespace hello_world
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_HELLO_WORLD_Hello_World_STUB_DEFAULT
