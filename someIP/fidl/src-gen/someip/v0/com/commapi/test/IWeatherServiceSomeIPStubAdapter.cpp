/*
 * This file was generated by the CommonAPI Generators.
 * Used org.genivi.commonapi.someip 3.2.0.v202012010944.
 * Used org.franca.core 0.13.1.201807231814.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 */
#include <v0/com/commapi/test/IWeatherServiceSomeIPStubAdapter.hpp>
#include <v0/com/commapi/test/IWeatherService.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#define HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#if defined (HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE)
#undef COMMONAPI_INTERNAL_COMPILATION
#undef HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

namespace v0 {
namespace com {
namespace commapi {
namespace test {

std::shared_ptr<CommonAPI::SomeIP::StubAdapter> createIWeatherServiceSomeIPStubAdapter(
                   const CommonAPI::SomeIP::Address &_address,
                   const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared< IWeatherServiceSomeIPStubAdapter<::v0::com::commapi::test::IWeatherServiceStub>>(_address, _connection, _stub);
}

void initializeIWeatherServiceSomeIPStubAdapter() {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:com.commapi.test.IWeatherService:v0_1:com.commapi.test.IWeatherService",
         0x1001, 0x1, 0, 1);
    CommonAPI::SomeIP::Factory::get()->registerStubAdapterCreateMethod(
        "com.commapi.test.IWeatherService:v0_1",
        &createIWeatherServiceSomeIPStubAdapter);
}

INITIALIZER(registerIWeatherServiceSomeIPStubAdapter) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializeIWeatherServiceSomeIPStubAdapter);
}

} // namespace test
} // namespace commapi
} // namespace com
} // namespace v0
