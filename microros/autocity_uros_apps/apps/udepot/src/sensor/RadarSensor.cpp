/*
 * @Author: hanson
 * @Date: 2024-12-05 16:16:03
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-16 15:24:41
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\sensor\RadarSensor.cpp
 */
#include "sensor/RadarSensor.hpp"
#include "trace/LogTrace.hpp"

#define GABAGE_SENSOR_ID (0x11)
#define TRASHCAN_SENSOR_ID (0x10)
namespace auto_city
{
    namespace udepot
    {
        RadarSensor::RadarSensor() : _is_setup(false)
        {
        }

        RadarSensor::~RadarSensor()
        {
        }

        int RadarSensor::SetUp(const std::string &dev_name, int bitrates)
        {
            if (_is_setup)
            {
                LOG_ERRO("RadarSensor is already setup\r\n");
                return -1;
            }

            _dev_name = dev_name;
            _bitrates = bitrates;

            // if (modbus_dev_init(_dev_name.c_str(), _bitrates, TRASHCAN_SENSOR_ID) != 0)
            // {
            //     LOG_ERRO("modbus init failed\r\n");
            //     return -1;
            // }

            LOG_INFO("RadarSensor setup done %s-%d\r\n", _dev_name.c_str(), _bitrates);
            _is_setup = true;
            return 0;
        }

        int RadarSensor::ReadGabageValue()
        {
            int ret = -1;

            uint16_t tab_reg[1] = {0};

            if (modbus_dev_init(_dev_name.c_str(), _bitrates, GABAGE_SENSOR_ID) != 0)
            {
                LOG_ERRO("modbus init failed\r\n");
                return ret;
            }

            if (modbus_dev_read_registers(0x02, 1, (uint16_t *)&tab_reg) > 0)
            {

                ret = tab_reg[0];
            }
            else
            {
                LOG_ERRO("RadarSensor read failed\r\n");
            }

            LOG_INFO("ReadGabageValue ret:%d\r\n", ret);

            modbus_dev_deinit();

            return ret;
        }

        int RadarSensor::ReadTrashCanValue()
        {
            int ret = -1;

            uint16_t tab_reg[1] = {0};

            if (modbus_dev_init(_dev_name.c_str(), _bitrates, TRASHCAN_SENSOR_ID) != 0)
            {
                LOG_ERRO("modbus init failed\r\n");
                return ret;
            }

            if (modbus_dev_read_registers(0x02, 1, (uint16_t *)&tab_reg) > 0)
            {
                // printf("tab_reg[0]:%d\r\n",tab_reg[0]);
                ret = tab_reg[0];
            }
            else
            {
                LOG_ERRO("RadarSensor read failed\r\n");
            }

            LOG_INFO("ReadTrashCanValue ret:%d\r\n", ret);

            modbus_dev_deinit();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            return ret;
        }
    }
}
