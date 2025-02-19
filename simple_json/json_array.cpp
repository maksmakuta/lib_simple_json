#include "json.h"

namespace simple_json {

    json_array::json_array(const std::initializer_list<bool>& v){
        for(const auto& item : v){
            push_back(json_value(item));
        }
    }

    json_array::json_array(const std::initializer_list<double>& v){
        for(const auto& item : v){
            push_back(json_value(item));
        }
    }

    json_array::json_array(const std::initializer_list<std::string>& v){
        for(const auto& item : v){
            push_back(json_value(item));
        }
    }

    json_array::json_array(const std::initializer_list<json_object>& v){
        for(const auto& item : v){
            push_back(json_value(item));
        }
    }

    json_array::json_array(const std::initializer_list<json_array>& v){
        for(const auto& item : v){
            push_back(json_value(item));
        }
    }

}
