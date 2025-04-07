/*
 * @Author: hanson
 * @Date: 2024-08-22 13:44:58
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:24:01
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\transport\Transport.hpp
 */
#ifndef __UCANBUS_INCLUDE_TRANSPORT__H_
#define __UCANBUS_INCLUDE_TRANSPORT__H_

#include "common/Singleton.hpp"
#include "vehicle/BaseTransportHandler.hpp"

namespace auto_city
{
    namespace udepot
    {
        class Transport
        {
        private:
            std::shared_ptr<BaseTransportHandler> _handler;

        public:
            Transport();
            virtual ~Transport();

            int Setup(std::shared_ptr<BaseTransportHandler> handler);

            std::shared_ptr<BaseTransportHandler> GetTransportHandler()
            {
                return _handler;
            }
        };

        using SingleTonTransport = Singleton<Transport>;

    }
}
#endif //__UCANBUS_INCLUDE_TRANSPORT__H_
