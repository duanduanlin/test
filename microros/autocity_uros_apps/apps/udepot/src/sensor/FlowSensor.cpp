#include "sensor/FlowSensor.hpp"
#include "trace/LogTrace.hpp"
namespace auto_city
{
    namespace udepot
    {
        int FlowSensor::SetUp(const std::string &dev_name, int bitrates)
        {

            if (_is_setup)
            {
                LOG_ERRO("FlowSensor is already setup\r\n");
                return -1;
            }

            if (flow_sensor_init(dev_name.c_str(), bitrates) < 0)
            {
                LOG_ERRO("FlowSensor setup failed\r\n");
                return -1;
            }
            _is_setup = true;
            return 0;
        }

        float FlowSensor::ReadInsFlowValue()
        {
            if (!_is_setup)
            {
                return 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            return flow_sensor_read_flow_value();
        }

        float FlowSensor::ReadTotalFlowValue()
        {
            if (!_is_setup)
            {
                return 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            return flow_sensor_read_total_flow_value();
        }
    }
}
