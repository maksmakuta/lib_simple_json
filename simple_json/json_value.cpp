#include "json.h"

namespace simple_json {

    json_value::json_value() = default;
    json_value::json_value(bool b) : value(b) {}
    json_value::json_value(const int i) : value(static_cast<double>(i)) {}
    json_value::json_value(double d) : value(d) {}
    json_value::json_value(const std::string& s) : value(s) {}
    json_value::json_value(const char* s) : value(std::string(s)) {}
    json_value::json_value(const json_array& arr) : value(arr) {}
    json_value::json_value(const json_object& obj) : value(obj) {}
    json_value::json_value(const json_value& obj) = default;

    json_value& json_value::operator=(const std::nullptr_t& new_value) {
        value = new_value;
        return *this;
    }

    json_value& json_value::operator=(bool new_value) {
        value = new_value;
        return *this;
    }

    json_value& json_value::operator=(const int new_value) {
        value = static_cast<double>(new_value);
        return *this;
    }

    json_value& json_value::operator=(double new_value)  {
        value = new_value;
        return *this;
    }

    json_value& json_value::operator=(const std::string& new_value) {
        value = new_value;
        return *this;
    }

    json_value& json_value::operator=(const char* new_value) {
        value = new_value;
        return *this;
    }

    json_value& json_value::operator=(const json_array& new_value) {
        value = new_value;
        return *this;
    }

    json_value& json_value::operator=(const json_object& new_value) {
        value = new_value;
        return *this;
    }

    json_value& json_value::operator=(const std::initializer_list<bool>& v){
        value = json_array(v);
        return *this;
    }

    json_value& json_value::operator=(const std::initializer_list<double>& v){
        value = json_array(v);
        return *this;
    }

    json_value& json_value::operator=(const std::initializer_list<std::string>& v){
        value = json_array(v);
        return *this;
    }

    json_value& json_value::operator=(const std::initializer_list<json_object>& v){
        value = json_array(v);
        return *this;
    }

    json_value& json_value::operator=(const std::initializer_list<json_array>& v){
        value = json_array(v);
        return *this;
    }

    bool json_value::operator==(const json_value &obj) const {
        return value == obj.value;
    }

}
