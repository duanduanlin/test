/*
 * @Author: hanson
 * @Date: 2024-08-27 16:42:52
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:14:38
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\msg_manager\BaseMsgManager.hpp
 */
#ifndef INCLUDE_MSG_MANAGER_BASEMSGMANAGER_HPP_
#define INCLUDE_MSG_MANAGER_BASEMSGMANAGER_HPP_

#include <memory>
#include <unordered_map>
#include <vector>

#include "protocol/BaseProtocol.hpp"
#include "trace/LogTrace.hpp"

namespace auto_city
{
    namespace udepot
    {
        class BaseMsgManager
        {
        private:
            /* data */
        protected:
            std::vector<std::unique_ptr<BaseProtocol>> _protocol;
            std::unordered_map<uint32_t, BaseProtocol *> _protocol_map;

        public:
            BaseMsgManager(/* args */) = default;
            virtual ~BaseMsgManager() = default;

            BaseProtocol *GetProtocolById(const uint32_t message_id)
            {
                if (_protocol_map.find(message_id) == _protocol_map.end())
                {
                    // LOG_WARN("can not find message_id:0x%04X\r\n", message_id);
                    return nullptr;
                }
                return _protocol_map[message_id];
            }
            template <class T, bool need_send = true>
            void AddProtocol()
            {
                static_assert(std::is_base_of<BaseProtocol, T>::value, "template params MUST be BaseProtocol!");
                _protocol.emplace_back(new T());
                if (need_send)
                {
                    auto *dt = _protocol.back().get();
                    if (dt == nullptr)
                    {
                        return;
                    }
                    LOG_WARN("add procotol id:0x%04X\r\n", dt->GetId());
                    _protocol_map[dt->GetId()] = dt;
                }
            }

            std::unordered_map<uint32_t, BaseProtocol *> &GetProtocolMap()
            {
                return _protocol_map;
            }

            std::vector<uint32_t> GetIDs()
            {
                std::vector<uint32_t> ids;
                for (auto i : _protocol_map)
                {
                    BaseProtocol *protocol = i.second;
                    ids.push_back(protocol->GetId());
                }

                return ids;
            }
        };
    }
}
#endif // INCLUDE_MSG_MANAGER_BASEMSGMANAGER_HPP_
