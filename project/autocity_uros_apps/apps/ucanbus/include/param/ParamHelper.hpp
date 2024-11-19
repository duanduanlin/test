#ifndef INCLUDE_PARAM_PARAMHELPER_HPP_
#define INCLUDE_PARAM_PARAMHELPER_HPP_

#include <map>
#include <memory>
#include "common/Singleton.hpp"
#include "trace/LogTrace.hpp"
#include "nlohmann/json.hpp"
#include "ufile.h"

using json = nlohmann::json;

#define CONFIG_FILE_LEN (1024)
class ParamHelper
{
    class Param
    {
    private:
        /* data */
        std::string _name;
        std::string _value_str;
        bool _value_bool;
        int _value_int;
        double _value_double;

    public:
        Param(std::string name, bool value) : _name(name), _value_bool(value) {};
        Param(std::string name, std::string value) : _name(name), _value_str(value) {};
        Param(std::string name, int value) : _name(name), _value_int(value) {};
        Param(std::string name, double value) : _name(name), _value_double(value) {};
        Param(std::string name) : _name(name) {};
        virtual ~Param() = default;

        void SetValue(bool value)
        {
            LOG_INFO("value:%d\r\n", value);
            _value_bool = value;
        }

        void SetValue(std::string value)
        {
            LOG_INFO("value:%s\r\n", value.c_str());
            _value_str = value;
        }

        void SetValue(int value)
        {
            LOG_INFO("value:%d\r\n", value);
            _value_int = value;
        }

        void SetValue(double value)
        {
            LOG_INFO("value:%f\r\n", value);
            _value_double = value;
        }

        void GetValue(std::string &value)
        {
            value = _value_str;
        }

        void GetValue(bool &value)
        {
            value = _value_bool;
        }

        void GetValue(int &value)
        {
            value = _value_int;
        }

        void GetValue(double &value)
        {
            value = _value_int;
        }
    };

private:
    /* data */
    std::map<std::string, std::shared_ptr<Param>> _param_map;

public:
    ParamHelper(/* args */) = default;
    ~ParamHelper() = default;

    template <typename ValueT>
    void SetParam(std::string name, ValueT value)
    {
        static_assert(std::is_same<typename std::decay<ValueT>::type, bool>::value ||
                          std::is_same<typename std::decay<ValueT>::type, std::string>::value ||
                          std::is_same<typename std::decay<ValueT>::type, int>::value ||
                          std::is_same<typename std::decay<ValueT>::type, double>::value,
                      "template params MUST be one of [Bool,string int double]!");

        LOG_INFO("set param:%s\r\n", name.c_str());
        auto param = _search_map(name, true);
        param->SetValue(value);
    }

    template <typename ValueT>
    int GetParam(std::string name, ValueT &value)
    {
        static_assert(std::is_same<typename std::decay<ValueT>::type, bool>::value ||
                          std::is_same<typename std::decay<ValueT>::type, std::string>::value ||
                          std::is_same<typename std::decay<ValueT>::type, int>::value ||
                          std::is_same<typename std::decay<ValueT>::type, double>::value,
                      "template params MUST be one of [Bool,string int double]!");

        auto param = _search_map(name, false);
        if (param != nullptr)
        {
            param->GetValue(value);
            return 0;
        }

        return -1;
    }

    template <typename ValueT>
    ValueT GetParamWithDefault(std::string name, ValueT default_value)
    {
        ValueT ret = default_value;

        GetParam(name, ret);

        return ret;
    }

    int LoadConfig()
    {
        char buffer[CONFIG_FILE_LEN] = {0};
        std::string config_file;
        if (std::getenv("UCANBUS_CON_FILE") == NULL)
        {
            config_file = std::string("/autocity/rdcu/ucanbus/config/ecar3_conf.json");
        }
        else
        {
            config_file = std::string(std::getenv("UCANBUS_CON_FILE"));
        }

        FILE *fp = ufile_open(config_file.c_str(), "r");
        if (fp == nullptr)
        {
            LOG_ERRO("open file failed: %s\r\n", config_file.c_str());
            return -1;
        }
        LOG_INFO("open file:%s success.\r\n", config_file.c_str());

        if (ufile_read(fp, buffer, CONFIG_FILE_LEN) <= 0)
        {
            LOG_ERRO("read file failed: %s\r\n", config_file.c_str());
            ufile_close(fp);
            return -1;
        }

        ufile_close(fp);

        LOG_INFO("config:%s\r\n", buffer);

        // std::string s = "{\"save_can_data\":true,\"save_publish_data\":true,\"can_interfaces\":\"can1\",\"vehicle_name\":\"EcarThreeWheel\",\"dump_time_threshold_s\":10.0}";
        auto json_obj = json::parse(buffer);

        LOG_INFO("save_can_data:%d\r\n", json_obj["save_can_data"].get<bool>());
        LOG_INFO("save_publish_data:%d\r\n", json_obj["save_publish_data"].get<bool>());
        LOG_INFO("can_interfaces:%s\r\n", json_obj["can_interfaces"].get<std::string>().c_str());
        LOG_INFO("vehicle_name:%s\r\n", json_obj["vehicle_name"].get<std::string>().c_str());
        LOG_INFO("dump_time_threshold_s:%f\r\n", json_obj["dump_time_threshold_s"].get<double>());

        SetParam<bool>("save_can_data", json_obj["save_can_data"].get<bool>());
        SetParam<bool>("save_publish_data", json_obj["save_publish_data"].get<bool>());
        SetParam<std::string>("can_interfaces", json_obj["can_interfaces"].get<std::string>());
        SetParam<double>("dump_time_threshold_s", json_obj["dump_time_threshold_s"].get<double>());
        SetParam<std::string>("vehicle_name", json_obj["vehicle_name"].get<std::string>());

        return 0;
    }

private:
    std::shared_ptr<Param> _search_map(std::string name, bool create_when_needed = false)
    {
        auto it = _param_map.find(name);
        if (it != _param_map.end())
        {
            return it->second;
        }
        else
        {
            if (create_when_needed)
            {
                auto new_param = std::make_shared<Param>(name);
                _param_map[name] = new_param;
                return new_param;
            }
            return nullptr;
        }
    }
};

using SingleTonParamHelper = Singleton<ParamHelper>;

#define GetParam SingleTonParamHelper::Instance().GetParam
#define GetParamWithDefault SingleTonParamHelper::Instance().GetParamWithDefault
#define SetParam SingleTonParamHelper::Instance().SetParam
#endif // INCLUDE_PARAM_PARAMHELPER_HPP_
