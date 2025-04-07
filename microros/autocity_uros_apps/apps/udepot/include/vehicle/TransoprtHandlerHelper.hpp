/*
 * @Author: hanson
 * @Date: 2024-08-27 11:48:47
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-02 16:53:25
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\TransoprtHandlerHelper.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_DATAHANDLERHELPER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_DATAHANDLERHELPER_HPP_

#include "vehicle/BaseTransportHandler.hpp"
#include "vehicle/water_depot/WaterDepotTransportHandler.hpp"
#include "vehicle/trash_depot/TrashDepotTransportHandler.hpp"
#include "common/Singleton.hpp"
#include "param/ParamHelper.hpp"

namespace auto_city
{
    namespace udepot
    {
        class TransoprtHandlerHelper
        {
        private:
            /* data */
        public:
            TransoprtHandlerHelper(/* args */) = default;
            virtual ~TransoprtHandlerHelper() = default;

            std::shared_ptr<BaseTransportHandler> CreateDataHandler()
            {
                if (GetParamWithDefault<std::string>("vehicle_name", "none") == "WaterDepot")
                {
                    return std::make_shared<water::WaterDepotTransportHandler>();
                }
                else if (GetParamWithDefault<std::string>("vehicle_name", "none") == "TrashDepot")
                {
                    return std::make_shared<trash::TrashDepotTransportHandler>();
                }
                else
                {
                    return nullptr;
                }
            }
        };
        using SingleTonTransportHandlerHelper = Singleton<TransoprtHandlerHelper>;

    }
}
#endif // APPS_UDEPOT_INCLUDE_VEHICLE_DATAHANDLERHELPER_HPP_
