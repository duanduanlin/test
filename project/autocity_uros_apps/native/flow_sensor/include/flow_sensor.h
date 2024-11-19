#ifndef NATIVE_FLOW_SENSOR_INCLUDE_FLOW_SENSOR_H_
#define NATIVE_FLOW_SENSOR_INCLUDE_FLOW_SENSOR_H_

#ifdef __cplusplus
extern "C"
{
#endif
float flow_sensor_read_flow_value();

float flow_sensor_read_total_flow_value();

int flow_sensor_init(const char *dev, int bitrates);

int flow_sensor_deinit();

#ifdef __cplusplus
}
#endif
#endif // NATIVE_FLOW_SENSOR_INCLUDE_FLOW_SENSOR_H_
