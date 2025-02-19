#include "json.h"

namespace simple_json {

    json_value::json_value(bool v) : json_variant(v){}
    json_value::json_value(double v) : json_variant(v){}
    json_value::json_value(const long v) : json_variant(static_cast<double>(v)){}
    json_value::json_value(const std::string& v) : json_variant(v){}
    json_value::json_value(const json_array& v) : json_variant(v){}
    json_value::json_value(const json_object& v) : json_variant(v){}

    json_value& json_value::operator=(std::nullptr_t v) {
        emplace<nullptr_t>(v);
        return *this;
    }

    json_value& json_value::operator=(bool v){
        emplace<bool>(v);
        return *this;
    }

    json_value& json_value::operator=(double v){
        emplace<double>(v);
        return *this;
    }

    json_value& json_value::operator=(const long v){
        emplace<double>(static_cast<double>(v));
        return *this;
    }

    json_value& json_value::operator=(const char* v) {
        emplace<std::string>(std::string(v));
        return *this;

    }

    json_value& json_value::operator=(const std::string& v){
        emplace<std::string>(v);
        return *this;
    }

    json_value& json_value::operator=(const json_array& v){
        emplace<json_array>(v);
        return *this;
    }

    json_value& json_value::operator=(const json_object& v){
        emplace<json_object>(v);
        return *this;
    }

    bool json_value::isBool() const{
        return std::holds_alternative<bool>(*this);
    }

    bool json_value::isNumber() const{
        return std::holds_alternative<double>(*this);
    }

    bool json_value::isString() const{
        return std::holds_alternative<std::string>(*this);
    }

    bool json_value::isObject() const{
        return std::holds_alternative<json_object>(*this);
    }

    bool json_value::isArray() const{
        return std::holds_alternative<json_array>(*this);
    }

    bool json_value::isNull() const{
        return std::holds_alternative<nullptr_t>(*this);
    }

    bool json_value::getBoolOr(const bool def) const{
        return isBool() ? std::get<bool>(*this) : def;
    }

    double json_value::getNumberOr(const double def) const{
        return isNumber() ? std::get<double>(*this) : def;
    }

    std::string json_value::getStringOr(const std::string& def) const{
        return isString() ? std::get<std::string>(*this) : def;
    }

    json_object json_value::getObjectOr(const json_object& def) const{
        return isObject() ? std::get<json_object>(*this) : def;
    }

    json_array json_value::getArrayOr(const json_array& def) const{
        return isArray() ? std::get<json_array>(*this) : def;
    }

    std::optional<bool> json_value::getBool() const{
        return isBool() ? std::optional(std::get<bool>(*this)) : std::nullopt;
    }

    std::optional<double> json_value::getNumber() const{
        return isNumber() ? std::optional(std::get<double>(*this)) : std::nullopt;
    }

    std::optional<std::string> json_value::getString() const{
        return isString() ? std::optional(std::get<std::string>(*this)) : std::nullopt;
    }

    std::optional<json_object> json_value::getObject() const{
        return isObject() ? std::optional(std::get<json_object>(*this)) : std::nullopt;
    }

    std::optional<json_array> json_value::getArray() const{
        return isArray() ? std::optional(std::get<json_array>(*this)) : std::nullopt;
    }


}
