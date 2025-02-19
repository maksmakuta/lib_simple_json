#include "json.h"

namespace simple_json {

    json_array::json_array(const std::initializer_list<bool>& v){
        assign(v.begin(), v.end());
    }

    json_array::json_array(const std::initializer_list<double>& v){
        assign(v.begin(), v.end());
    }

    json_array::json_array(const std::initializer_list<std::string>& v){
        assign(v.begin(), v.end());
    }

    json_array::json_array(const std::initializer_list<json_object>& v){
        assign(v.begin(), v.end());
    }

    json_array::json_array(const std::initializer_list<json_array>& v){
        assign(v.begin(), v.end());
    }

}
